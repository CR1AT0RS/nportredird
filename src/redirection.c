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
#include <redirection.h>
#include <nportredird.h>
#include <net.h>

 MODULEID("$Id: redirection.c,v 1.1 2000/03/29 08:59:24 ayman Beta $");

 static int CheckActiveRedirectionIntegrity (Redirection *);
 static int CheckDuplicateRedirection (Redirection *);
 static void DuplicateAccessList (RedirectionAccessList *, RedirectionAccessList *);
 static void BuildRedirectionID (Redirection *);
 static int CheckPassiveRedirectionIntegrity (Redirection *);
 static int AddPassiveRedirection (Redirection *);
 static int AddActiveRedirection (Redirection *);


 /* bison */
 /* intermediate function; acts as buffer zone between bison and the 
    intarnals
 */
 int AddRedirection (Redirection *redir_ptr)
 
 {
   if (redir_ptr)
    {
      if (redir_ptr->redir_mode==REDIR_MODE_ACTIVE)
       {
        return (AddActiveRedirection(redir_ptr));
       }
      else
      if (redir_ptr->redir_mode==REDIR_MODE_PASSIVE)
       {
        return (AddPassiveRedirection(redir_ptr));
       } 
    }

   return 0;

 }  /**/

 
 static int AddActiveRedirection (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
      int ret;

       if (!(ret=CheckActiveRedirectionIntegrity(redir_ptr)))  return 0;
       if (!CheckDuplicateRedirection(redir_ptr))  return 0;

      {
       Redirection *rptr;

        xmalloc(rptr, (sizeof(struct Redirection)));
        memset (rptr, 0, sizeof(struct Redirection));

        rptr->redir_type=redir_ptr->redir_type;
        mstrncpy(rptr->dst_host, redir_ptr->dst_host, MAXHOSTLEN);
        mstrncpy(rptr->local_host, redir_ptr->local_host, MAXHOSTLEN);
        rptr->dst_port=redir_ptr->dst_port;
        rptr->listen_on_port=redir_ptr->listen_on_port;
        rptr->redir_mode=redir_ptr->redir_mode;
         if (!(*redir_ptr->redir_id))  BuildRedirectionID (rptr);
         else  mstrncpy(rptr->redir_id, redir_ptr->redir_id, MAXREDIRID);
         if (redir_ptr->max_connections<0)  redir_ptr->max_connections=0;
        rptr->max_connections=redir_ptr->max_connections;

        /*copy access list*/
        DuplicateAccessList (&rptr->redir_access_list, 
                             &redir_ptr->redir_access_list);

        RegisterRedirection (rptr);
         if (ret==-1)  {printf ("disabeling redirection\n");RedirectionRegistryMarkInactive(rptr);}
        /*AddThisToList (redir_list_ptr, (void *)rptr);*/
        
        return 1;
      }
     }

   return 0;

 }  /**/


 static int AddPassiveRedirection (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
       if (!CheckPassiveRedirectionIntegrity(redir_ptr))  return 0;
       if (!CheckDuplicateRedirection(redir_ptr))  return 0;

      {
       Redirection *rptr;

        xmalloc(rptr, (sizeof(struct Redirection)));
        memset (rptr, 0, sizeof(struct Redirection));

        rptr->redir_type=redir_ptr->redir_type;
        mstrncpy(rptr->dst_host, redir_ptr->dst_host, MAXHOSTLEN);
        rptr->dst_port=redir_ptr->dst_port;
        rptr->redir_mode=redir_ptr->redir_mode;
         if (!(*redir_ptr->redir_id))  BuildRedirectionID (rptr);
         else  mstrncpy(rptr->redir_id, redir_ptr->redir_id, MAXREDIRID);   
        RegisterRedirection (rptr);
 
        return 1;
      }
     }

   return 0;

 }  /**/


 /*
  0 -> fatal
 -1 -> non fatal, but redirection cannon be used
  1 -> OK
 */
 static int CheckActiveRedirectionIntegrity (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
       if (!redir_ptr->redir_type)  
        {
         printf ("Redirection type unset.\n");

         return 0;
        }

       if ((!redir_ptr->listen_on_port)||(redir_ptr->listen_on_port<0))
        { 
         printf ("Invalid local port: %u\n", redir_ptr->listen_on_port);

         return 0;
        }

       if ((!redir_ptr->dst_port)||(redir_ptr->dst_port<0))  
        {
          if (!(arethesame("/dev/null", redir_ptr->dst_host)))
           { 
            printf ("Invalid destination port: %u\n", redir_ptr->dst_port);

            return 0;
           }
        }

       if ((!*redir_ptr->dst_host))  
        {
         printf ("Invalid destination host: %s\n", redir_ptr->dst_host);

         return 0;
        } 

      if (*redir_ptr->local_host)
	   {
		int err;

		 switch (err=(IsLocalIP(redir_ptr->local_host)))
		  {
		   case -1:
			printf ("Specified local ip is not valid '%s'\n", 
					redir_ptr->local_host);
		   return -1;

		   case -2:
			printf ("Specified local ip (%s) location error: %s\n", 
					redir_ptr->local_host,
					strerror(errno));
		   return -1;  
		   
		   case 0:
			printf ("Specified local ip (%s) might not be local.\n",
					redir_ptr->local_host);
		   return -1;
		  
		   case 1:/*match*/
		   break;  

		  } 
	   }
        
      return 1;
     }

   return 0;

 }  /**/


 static int CheckPassiveRedirectionIntegrity (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
       if (!redir_ptr->redir_type)  
        {
         printf ("Redirection type unset.\n");

         return 0;
        }

       if ((!redir_ptr->dst_port)||(redir_ptr->dst_port<0))  
        {
         printf ("Invalid destination port: %u\n", redir_ptr->dst_port);

         return 0;
        }

       if ((!*redir_ptr->dst_host))  
        {
         printf ("Invalid destination host: %s\n", redir_ptr->dst_host);

         return 0;
        } 

       
      return 1;
     }

   return 0;

 }  /**/


 void CleanupRedirectionEntry (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
      redir_ptr->redir_type=0;
      redir_ptr->listen_on_port=0;
      redir_ptr->dst_port=0;
      redir_ptr->dst_host[0]=0;
      redir_ptr->local_host[0]=0;
      redir_ptr->redir_id[0]=0;

      redir_ptr->redir_access_list.redir_access_mode=0;

       if (redir_ptr->redir_access_list.access_list.nEntries)
        {
         /*cleanup accesslist*/
        }
     }

 }  /**/


 /* blind copy (pointers swap actually) */
  static void 
 DuplicateAccessList (RedirectionAccessList *d, RedirectionAccessList *s)

 {
  register dListEntry *eptr,
                      *auxptr; 

    for (eptr=s->access_list.head; eptr; eptr=eptr->next)
     {
      auxptr=AddtodList(&d->access_list);
      auxptr->whatever=eptr->whatever;
      /*free (eptr);*/
     }

   s->access_list.nEntries=0;
   s->access_list.head=s->access_list.tail=NULL;
   d->redir_access_mode=s->redir_access_mode;
   s->redir_access_mode=0;

 }  /**/


 /*
 ** Check is only performed on local port and redir type
 ** We don't care if he redirecting connection to some already defined
 ** host/port combo but with same/different of access list.
 */
 static int CheckDuplicateRedirection (Redirection *redir_ptr)

 {
    if (redir_ptr)
     {
     }

   return 1; 

 } /**/


 static void BuildRedirectionID (Redirection *rptr)

 {
    if (rptr)
     {
       sprintf (rptr->redir_id, "%s:%u:%s", rptr->dst_host, rptr->dst_port,
                               (rptr->redir_type==REDIR_TCP)?("tcp"):("udp"));
     }

 } /**/
 
