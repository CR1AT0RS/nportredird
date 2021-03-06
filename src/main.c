/*
    nportredird - TCP/IP networks port forwarder daemon.

    Copyright (C) 1999-2001  Ayman Akt
    Original Author: Ayman Akt (ayman@pobox.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <main.h>
#include <sockets.h>
#include <list.h>
#include <session.h>
#include <misc.h>
#include <redirection.h>
#include <nportredird.h>
#include <firingsquad.h>


 static int ReadFromSocket (Session *, Socket *);
 static int DispatchSocketBuffer (Session *, Socket *, Socket *);
#ifdef __GNUC__
 static void Banner (void) __attribute__ ((unused));
 static void GoDaemon (void) __attribute__ ((unused));
#else
 static void Banner (void);
 static void GoDaemon (void);
#endif
 const char *c_version="0.6";

 extern msredird *const masterptr;


 int main (int argc, char *argv[])

  {
   pthread_t firingsquad;
   extern int ProcessConfigfile (const char *);

    openlog("nportredird", LOG_NDELAY, LOG_DAEMON);

    SetConfigurationDefaults ();
    CheckCommandLine (argc, argv);

    ProcessConfigfile (NULL);
 
    InitNportredird ();

    InitSignals ();

    LaunchRedirectors (&masterptr->redir_def);

     if (masterptr->running_mode==RUNNING_MODE_DAEMON)  GoDaemon ();

    pthread_create (&firingsquad, NULL, FiringSquad, NULL);
    
    {
     int x;
     fd_set fd,
            xfd;

      again:
      dummy ();
      FD_ZERO(&fd);
      FD_ZERO(&xfd);

      /*FD_SET(STDIN_FILENO, &fd);*/

      {
       register ListEntry *eptr;

        for (eptr=masterptr->redir_def.head; eptr; eptr=eptr->next)
         {
           if (((RedirectionRegistry *)eptr->whatever)->sptr)
            {
             say ("setting %d\n", ((RedirectionRegistry *)eptr->whatever)->sptr->sock);
             FD_SET(((RedirectionRegistry *)eptr->whatever)->sptr->sock, &fd);
            }
         }
      }
      

       while (1!=2)
        {
         x=select(FD_SETSIZE, &fd, NULL, NULL, NULL);

          if (x>0)  /* readable input */
           {
             /*if (FD_ISSET(STDIN_FILENO, &fd))
              {
              }
             else*/
            {
               register ListEntry *eptr;

                 for (eptr=masterptr->redir_def.head; eptr; eptr=eptr->next)
			   {
				if (((RedirectionRegistry *)eptr->whatever)->sptr)
				 {
                   if (FD_ISSET(((RedirectionRegistry *)eptr->whatever)->sptr->sock, 
                            &fd))
				    {
                     say ("answering con on %d\n", 
                          ((RedirectionRegistry *)eptr->whatever)->sptr->sock);
                     AnswerTelnetRequest (((RedirectionRegistry *)eptr->whatever)); 
                    }
				 }
			   }
            }
           }
          else
          if (x==0)  /* timeout */
           {
           }
          else
          if ((x==-1)&&(errno!=EINTR))  /* select error */
           {
            /*CheckListeningRedirectors (&masterptr->redir_def);*/
            say ("### select error: %s\n", strerror(errno));

            goto again;
           }

         goto again;

        }  /* while (1==1) */

    } /* END OF BLOCK */


   return 0; /*should never return*/

 }  /*EOM*/


 void *Thread (void *ptr)

 {
  int x,
      max;
  fd_set rfd,
         wfd,
         xfd;
  Session *sesnptr=(Session *)ptr;
  Socket *ssptr, *dsptr;

    if (!sesnptr)
     {
      syslog (LOG_INFO, "OOPSZ thread was passed sesnptr==NULL");

      /*FIXME clean up work required */
      pthread_exit (NULL);      
     }

   sesnptr->pid=getpid();

   ssptr=sesnptr->ssptr;
   dsptr=sesnptr->dsptr;

   (sesnptr->ssptr->sock>sesnptr->dsptr->sock)?
    (max=sesnptr->ssptr->sock):(max=sesnptr->dsptr->sock);
 
   FD_ZERO (&rfd);
   FD_ZERO (&wfd);
   FD_ZERO (&xfd);

   FD_SET(ssptr->sock, &rfd);
    if (dsptr->hport)  FD_SET(dsptr->sock, &rfd); /*hack for /dev/null*/


   {
     while (1!=2)
      {
       x=select(max+1, &rfd, &wfd, &xfd, NULL);

	  if (x>0)  /* readable input */
	   {
		 if (FD_ISSET(ssptr->sock, &rfd)) /* socket... */
		  {
		   ReadFromSocket (sesnptr, ssptr);
		   DispatchSocketBuffer (sesnptr, ssptr, dsptr);
		  }
		 else
		 if (FD_ISSET(dsptr->sock, &rfd))  /* device... */
		  {
		   ReadFromSocket (sesnptr, dsptr);
		   DispatchSocketBuffer (sesnptr, dsptr, ssptr);
		  }

			/* check for exception errors */

	   }
	  else
	  if (x==0)  /* timeout */
	   {

	   }
	  else
	  if (x==-1)  /* select error */
	   {
  #ifdef PER_SESSION_LOG
		logf (sesnptr, "### select error: %s\n", strerror(errno));
  #endif
        syslog (LOG_INFO, "Closing connection (select error [%s]).\n",
                          strerror(errno));
        sesnptr->stat|=FIRING_SQUAD;
        RedirectionSignalFiringSquad ((RedirectionRegistry *)sesnptr->user_data);
        pthread_exit (NULL);
	   }

       {   /* FALL-THROUGH BLOCK */


       }   /* END-OF FALL-THROUGH BLOCK */

       FD_SET(ssptr->sock, &rfd);
        if (dsptr->hport)  FD_SET(dsptr->sock, &rfd); /*hack for /dev/null*/
      }  /* while (1!=2) */

   }  /* END OF BLOCK */

 }  /**/


 static int ReadFromSocket (Session *sesnptr, Socket *sptr)

 {

    if (!sesnptr)  return -1;

    /* sanity check? FIXME */
    if ((sptr->msglen=read(sptr->sock, sptr->msg, XLARGBUF))>0)
     {
      return 1;
     }
    else
     {
      syslog (LOG_INFO, "Remote end closed connection (%s)"
                        " (read attempt (%d) <- [%s:%d])."
                        "\n",
                        strerror(errno),
                        sptr->msglen, sptr->haddress, sptr->hport);

      sesnptr->stat|=FIRING_SQUAD;
      RedirectionSignalFiringSquad ((RedirectionRegistry *)sesnptr->user_data);
      pthread_exit (NULL);
     }

 }  /**/


  static int 
 DispatchSocketBuffer (Session *sesnptr, Socket *ssptr, Socket *dsptr)

 {
    if (ssptr->msglen>0)
     {
      size_t  nleft;
      ssize_t nwritten;
      const char *ptr;

       ptr=ssptr->msg;
       nleft=ssptr->msglen;

        while (nleft>0)
         {
           if ((nwritten=write(dsptr->sock, ptr, nleft))<=0)
            {
             syslog (LOG_INFO, "Remote end closed connection (%s)"
                               " (write attempt (%d) -> [%s:%d]\n", 
                               strerror(errno),
                               nwritten, dsptr->haddress, dsptr->hport);

             sesnptr->stat|=FIRING_SQUAD;
             RedirectionSignalFiringSquad (
              (RedirectionRegistry *)sesnptr->user_data);
             pthread_exit (NULL);
            }

          nleft-=nwritten;
          ptr+=nwritten;
         }
       *ssptr->msg=0;
       ssptr->msglen=0;
     }
  
   return 1;

 }  /**/


 static void GoDaemon (void)

 {
    if (fork())
     {
      fflush (stdin);
      fflush (stdout);
      fflush (stderr);

      _exit (1);
     }

   setsid ();

   freopen ("/dev/null", "r", stdin);  /* Yes! */
   freopen ("/dev/null", "w", stdout);
   freopen ("/dev/null", "w", stderr);

 }  /**/


 static void Banner (void)

 {
   say ("*** nportredird %s.\n", c_version);

 }  /**/


 void SetConfigurationDefaults (void)

 {
    if (!masterptr->log_mode)  masterptr->log_mode=LOG_MODE_SYSLOG;
    if (!masterptr->running_mode)  masterptr->running_mode=RUNNING_MODE_DAEMON;
    if (!*masterptr->config_dir)
     mstrncpy(masterptr->config_dir, CONFIG_DIR, _POSIX_PATH_MAX);
    if (!*masterptr->config_file)
     mstrncpy(masterptr->config_file, CONFIG_FILE_NAME, _POSIX_PATH_MAX);

 }  /**/


 void Help (void)

 {
   printf (" nportredird [-h]\n"
           "             [-v]\n"
           "             [-f config_file]\n"
           "             [-c config_dir]\n"
           "             [-d 1|0]\n"
           " Default invocation parameters: -f nportredird.conf -c /etc/nportredird -d 1\n" 
          );

   _exit (1);

 }  /**/



 void CheckCommandLine (int argc, char *argv[])
 
 {
  int i, 
      j=1,
      cnt=0;
  extern char *u_compiled,
              *t_compiled;

    if (argc==1)
     {
      /*SetConfigurationDefaults ();*/

      return;
     }
    
    for (i=1; i<argc; i++)
     { 
      switch (argv[i][0])
       { 
        case '-':
          while ((j)&&(argv[i][j]))
	   { 
	    switch (argv[i][j])
	     { 
	      case 'h':
	      case 'H':
	      case '?':
	      Help ();

	      case 'v':
	      case 'V':
	       fprintf (stdout, 
"nportredird %s (%s %s)\n"
"Copyright (C) 1999-2001  Ayman Akt <ayman@pobox.com>\n\n"
"nportredird is free software, covered by the GNU General Public License,\n"
"and you are welcome to change it and/or distribute copies of it under\n"
"certain conditions.\n"
"There is absolutely no warranty for nportredird.\n\n",
			c_version, u_compiled, t_compiled);

	       _exit (1);

	      case 'd': /* -d 1|0 */
	       i++;
	       j--;
		if (argv[i])
		 {
           if (atoi(argv[i]))  masterptr->running_mode=RUNNING_MODE_DAEMON;
           else  masterptr->running_mode=RUNNING_MODE_TERM;
		 }
	       break;

	      case 'c':
	       i++;
	       j--;
		if (argv[i])
		 {
		  mstrncpy (masterptr->config_dir, argv[i], _POSIX_PATH_MAX);
          syslog (LOG_INFO, "Configuration dir set to '%s'", 
                  masterptr->config_dir);
		 } 
	       break;
				 
	      case 'f':
	       i++;
	       j--;
            if (argv[i])
             {
              mstrncpy (masterptr->config_file, argv[i], _POSIX_PATH_MAX);
              syslog (LOG_INFO, "Configuration file set to '%s'",
                  masterptr->config_dir);
             }
	       break;

	      default:
	       j--; 
	       break;
	     } 
	    j++;  
	    break; 
	   }  
         break;  

        default:
	 cnt++;
	 j=1;
	 switch (cnt)
	  {
	   case 1:
	    break;

	   case 2:
	    break;
		    
	   default:
	    break;
	  }
       }  
     }  

 }  /**/   

