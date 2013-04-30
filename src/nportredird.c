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
#include <net.h>
#include <accesslist.h>
#include <session.h>
#include <nportredird.h>


 /* encapsulates all global variables */
 static msredird master;
 msredird *const masterptr=&master;
#ifdef __GNUC__
 static RedirectionRegistry *GetRedirectionRegistry (Redirection *) 
  __attribute__ ((unused));
#else
 static RedirectionRegistry *GetRedirectionRegistry (Redirection *);
#endif
 static Socket *ConnectToDestinationHost (const char *, unsigned long);



 /*Return the 'RedirectionRegistry' that encapsulates this 'Redirection'.
   'Redirection' have no back-pointers to their 'RedirectionRegistry'
 */
 static RedirectionRegistry *GetRedirectionRegistry (Redirection *rptr)

 {
    if (rptr)
     {
      register ListEntry *eptr;
      register RedirectionRegistry *rrptr;

        for (eptr=master.redir_def.head; eptr; eptr=eptr->next)
		 {
		  rrptr=(RedirectionRegistry *)eptr->whatever;

		   if (rrptr->redir==rptr)  return rrptr;
		 }
     }

   return NULL;

 }  /**/


 void InitNportredird (void)

 {
  pthread_mutex_t auxmutex=PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t auxcond=PTHREAD_COND_INITIALIZER;

   masterptr->when=time(NULL);

   masterptr->nready=0;
   
   masterptr->nready_mutex=auxmutex;
   masterptr->nready_cond=auxcond;

   BuildLocalHostsNetworksACL ();
   
   /*PrintAccessList (lhacl_ptr);
   PrintAccessList (lnacl_ptr);*/
#if 0
   {
    struct in_addr addr;
    int i;

     inet_aton("192.168.1.2", &addr);
     printf ("%d\n", AccessListMatch(lnacl_ptr, addr));     
   }
#endif
 }  /**/


 /*
 ** Complete redirection definition probably built from config file
 */
 Redirection *RegisterRedirection (Redirection *rptr)

 {
  RedirectionRegistry *rrptr;

    if (rptr)
     {
      xmalloc(rrptr, (sizeof(RedirectionRegistry)));
      memset (rrptr, 0, sizeof(RedirectionRegistry));

      rrptr->redir=rptr;
      pthread_mutex_init(&rrptr->current_connections_count_mutex, NULL);


      AddThisToList (&master.redir_def, (void *)rrptr);

      return rptr;
     }

   return NULL;

 }  /**/


 /*struct msredird.redir_def*/
 /* expects a list of RedirectionRegistry */
 void LaunchRedirectors (List *lst)

 {
    if (lst)
     {
      int socket;
      register ListEntry *eptr;
      register RedirectionRegistry *rrptr;

       syslog (LOG_INFO,"Launching redirectors (%d).", lst->nEntries);

        for (eptr=lst->head; eptr; eptr=eptr->next)
		 {
		  rrptr=(RedirectionRegistry *)eptr->whatever;

           if (rrptr->status==REDIRECTION_DISABLED) 
            {
             syslog (LOG_INFO,"Skipping disabled redirection '%s'",
                               rrptr->redir->redir_id);
             continue;
            } 

           if (rrptr->redir->redir_mode==REDIR_MODE_PASSIVE)
            {
             syslog (LOG_INFO,"Answering intra-redirections -> %s:%u", 
                               rrptr->redir->dst_host,
                               rrptr->redir->dst_port);

             /*rrptr->sptr gets NULL*/
            }
           else
           if (rrptr->redir->redir_mode==REDIR_MODE_ACTIVE)
            { 
			  if ((socket=SetupListeningSocket((rrptr->redir->local_host[0]?
                                                rrptr->redir->local_host:
                                                NULL),
                                               rrptr->redir->listen_on_port, 
                                               0))>0)
			   {
				Socket *sptr;
		
				 xmalloc(sptr, (sizeof(Socket)));
				 memset (sptr, 0, sizeof(Socket));

				 sptr->sock=socket;
				 sptr->when=time(NULL);
				 sptr->port=rrptr->redir->listen_on_port;
				 strcpy (sptr->address, "localhost");

				 rrptr->sptr=sptr;

				 syslog (LOG_INFO, 
						 "Answering inter-redirections on %s:%u -> %s:%u\n",
                         ((*rrptr->redir->local_host)?
                          (rrptr->redir->local_host):("*")), 
						 sptr->port,
						 rrptr->redir->dst_host,
						 rrptr->redir->dst_port); 
				}
               else
             {
              fprintf (stderr, "Cannot setup listening socket on %u. %s.\n",
                       rrptr->redir->listen_on_port, strerror(errno));

               syslog (LOG_INFO, "Cannot setup listening socket on %u. %s.\n",
                       rrptr->redir->listen_on_port, strerror(errno));

              continue;
             }
            }/*ACTIVE*/
		  }
     }
 
 }  /**/


/*Make sure no calling function in the chain is locking
   rptr->current_connections_count_mutex or we end up with race cond
*/
 unsigned long GetCurrentConnectionsCount (RedirectionRegistry *rptr)

 {
  unsigned long count;

   /*It does make sense to lock the mutex here even if we only reading
     as the firing_squad thread could be in the middle of updating it.
   */ 
   pthread_mutex_lock (&rptr->current_connections_count_mutex);
   count=rptr->current_connections_count;
   pthread_mutex_unlock (&rptr->current_connections_count_mutex);
   
   return count; /*well, thats kind of defeats the purpose...*/
 
 }  /**/


 /*Make sure no calling function in the chain is locking 
   rptr->current_connections_count_mutex or we end up with race cond*/
 void IncrementCurrentConnectionsCount (RedirectionRegistry *rptr)

 {
   pthread_mutex_lock (&rptr->current_connections_count_mutex);
   rptr->current_connections_count++;
   pthread_mutex_unlock (&rptr->current_connections_count_mutex);

 }  /**/


 void DecrementCurrentConnectionsCount (RedirectionRegistry *rptr)

 {
   pthread_mutex_lock (&rptr->current_connections_count_mutex);
   syslog (LOG_INFO, "Current connections count: %d. Decrementing by 1...", 
           rptr->current_connections_count);
   rptr->current_connections_count--;
    if (rptr->current_connections_count<0) /*problema*/
     {
      syslog (LOG_INFO, "OOPSZ current_connections_count out of sync. "
                        "Resetting to 0");

      rptr->current_connections_count=0;
     }
   pthread_mutex_unlock (&rptr->current_connections_count_mutex);

 }  /**/


 void  RedirectionSignalFiringSquad (RedirectionRegistry *rptr)

 {
   pthread_mutex_lock (&masterptr->nready_mutex);
   masterptr->nready++;
   syslog (LOG_INFO, "%d connection(s) awaiting clean up.", masterptr->nready);
   pthread_mutex_unlock (&masterptr->nready_mutex);

   pthread_cond_signal (&masterptr->nready_cond);
   //pthread_mutex_unlock (&masterptr->nready_mutex);

   DecrementCurrentConnectionsCount (rptr);

 } /**/


 /*This called in the context of the main thread, and there're no 
   concurrency issues execpt when it comes to incrementing the current
   connections counter as the firing_squad thread could be in the middle 
   of decrementing it.
 */
 int AnswerTelnetRequest (RedirectionRegistry *rptr)
 
 {
  int 
      nsocket,
      sin_size,
      opt=1;
  char *host,
       *intra_redir;
  Socket *ssptr,
         *dsptr; /* dest host */
  Session *sesnptr;
  struct sockaddr_in hisaddr;

   sin_size=sizeof(struct sockaddr_in);
   nsocket=accept(rptr->sptr->sock, (struct sockaddr *)&hisaddr, 
                  &sin_size); 

    if ((nsocket<0)&&(errno!=EWOULDBLOCK))
     {
      syslog (LOG_INFO, "Unable to accept connection on port %u-%s",
              rptr->redir->listen_on_port, strerror(errno));

      return 0;
     }

   { /* we don't increment hits/misses */
     if (rptr->redir->max_connections)
      {
        if ((GetCurrentConnectionsCount(rptr))+1>rptr->redir->max_connections)
        /*if (rptr->current_connections_count+1>rptr->redir->max_connections)*/
         {
          syslog (LOG_INFO, "Max connections count exceeded on %u."
                            " Originator %s",
                  rptr->redir->listen_on_port, inet_ntoa(hisaddr.sin_addr));

          close (nsocket);

          return 0;
         }
      }
   }

   {
    int in;

      in=AccessListMatch(&rptr->redir->redir_access_list.access_list, 
                         hisaddr.sin_addr);
    
       if (in==0)
        {
           if ((rptr->redir->redir_access_list.redir_access_mode==
                REDIR_ACCESS_MODE_DENY))
            {
             syslog (LOG_INFO, "Rejecting connection from %s:%d on %u--"
                               "not in allow list.",
                               inet_ntoa(hisaddr.sin_addr), hisaddr.sin_port,
                               rptr->redir->listen_on_port);

             rptr->misses++;

             close (nsocket);

             return 0;
            }
           else
            {
             syslog (LOG_INFO, "Allowing connection from %s:%d on %u--"
                               "not in deny list.",
                               inet_ntoa(hisaddr.sin_addr), hisaddr.sin_port,
                               rptr->redir->listen_on_port);

             rptr->hits++;
            }
        }
       else
        {
           if ((rptr->redir->redir_access_list.redir_access_mode==
                REDIR_ACCESS_MODE_DENY))
            {
             syslog (LOG_INFO, "Allowing connection from %s:%d on %u--"
                               "in allow list.",
                               inet_ntoa(hisaddr.sin_addr), hisaddr.sin_port,
                               rptr->redir->listen_on_port);

             rptr->hits++;
            }
           else
            {
             syslog (LOG_INFO, "Rejecting connection from %s:%d on %u--"
                               "in denylist.",
                               inet_ntoa(hisaddr.sin_addr), hisaddr.sin_port,
                               rptr->redir->listen_on_port);

             rptr->misses++;

             close (nsocket);

             return 0;
            }
        }  
   } 

   /*intra-redir entry?*/
   intra_redir=AccessListMatchIntraRedir(&rptr->redir->redir_access_list.access_list,
                         hisaddr.sin_addr);
    if (*intra_redir)
     {
      rptr=RedirectionRegistryLocateByID (&master.redir_def, intra_redir);
       if (!rptr) /*shouldn't happen?*/
        {
         syslog (LOG_INFO, "OOPSZ Unable to locate intra-definition '%s'",
                           intra_redir);

         close (nsocket);

         return 0;
        }
      rptr->hits++;

      syslog (LOG_INFO, "Applying intra-redirection -> %s:%d",
                        rptr->redir->dst_host, rptr->redir->dst_port);
     }
   
   host=(char *)inet_ntoa(hisaddr.sin_addr);
 
   setsockopt (nsocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&opt, sizeof(int));

   xmalloc(ssptr, (sizeof(Socket)));
   memset (ssptr, 0, sizeof(Socket));

   ssptr->sock=nsocket;
   ssptr->when=time(NULL);
   strcpy (ssptr->haddress, host);
   strcpy (ssptr->address, "localhost");
   ssptr->hport=ntohs(hisaddr.sin_port);
   ssptr->port=rptr->redir->listen_on_port;

    /* 
    ** potential blocked connect(); needs review. It should
    ** work _most of the time_ without blocking specially if
    ** the network is local, but under extreme conditions or
    ** heavey load, it might block. If the code in main loop
    ** doesn't test for this, connection will never complete!
    ** FIXME
    */
    if (!(dsptr=ConnectToDestinationHost(rptr->redir->dst_host, 
                                         rptr->redir->dst_port)))
     {
      syslog (LOG_INFO, "Unable to connect to host %s on port %u"
                        "--redirection aborted.",
                        rptr->redir->dst_host, rptr->redir->dst_port);

      close (ssptr->sock);
      free (ssptr);

      return 0;
     }

    /*
    ** Session log file only open after successful return from
    ** this function.
    */ 
    if (!(sesnptr=OpenSession(ssptr, dsptr)))
     {
      close (ssptr->sock);
      free (ssptr);

      close (dsptr->sock);
      free (dsptr);
 
      return 0;
     }

   sesnptr->user_data=(void *)rptr;

   IncrementCurrentConnectionsCount (rptr);

   {
     pthread_create (&sesnptr->th, NULL,
                     Thread, (void *)sesnptr);
   }

   return nsocket;

 }  /**/


 static Socket *ConnectToDestinationHost (const char *host, unsigned long port)

 {
  Socket *sptr;

   xmalloc(sptr, (sizeof(Socket))); 
   memset (sptr, 0, sizeof(Socket));

    if (port==0)
     {
      if (!(ConnectToThis(host, port, sptr)))
	   {
		free (sptr);

		return (Socket *)NULL;
	   }
     }
    else
    if (!(ConnectToServer(host, port, sptr)))  
     {
      free (sptr); 

      return (Socket *)NULL;
     }

   /*say ("*** Connected to %s at %lu...\n", host, port);*/

   return sptr;

 }  /**/


 void RedirectionRegistryMarkInactive(Redirection *rptr)
 
 {
    if (rptr)
     {
      RedirectionRegistry *regptr;

        if ((regptr=GetRedirectionRegistry(rptr)))
         {
          regptr->status=REDIRECTION_DISABLED;
         }
     }

 } /**/


 RedirectionRegistry *RedirectionRegistryLocateByID (List *lst, const char *str)

 {
  register ListEntry *eptr;
  register RedirectionRegistry *rrptr;

    for (eptr=lst->head; eptr; eptr=eptr->next)
     {
      rrptr=(RedirectionRegistry *)eptr->whatever;

       if (strcmp(str, rrptr->redir->redir_id)==0)
        {
         return rrptr;
        }
     }

   return NULL;

 } /**/

