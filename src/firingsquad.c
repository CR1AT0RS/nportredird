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

#include <list.h>
#include <sockets.h>
#include <session.h>
#include <nportredird.h>

 static Session *Align (void);
 static void Shoot (Session *);


 void *FiringSquad (void *args)

 {
  Session *sesnptr;
  extern msredird *const masterptr;

   pthread_mutex_lock (&masterptr->nready_mutex);

    while (1!=2)
     {
       while (masterptr->nready==0)
		{
		 /* lock is released byond this point */
		 pthread_cond_wait (&masterptr->nready_cond, &masterptr->nready_mutex);
		}

      /* lock re-acquired... */
      /* get the soon-to-be shot session */
       if ((sesnptr=Align()))
        {
         Shoot (sesnptr);
         /*say ("a thread exited...\n");*/
         masterptr->nready--;

         PrintSessions ();
        }
       else
        {
         syslog (LOG_INFO, "Align() return NULL sesnptr");
        }

      pthread_mutex_unlock (&masterptr->nready_mutex);
     }

   return NULL;

 }  /**/


 static Session *Align (void)

 {
  Session *sesnptr;
  
    while ((sesnptr=GetFlaggedSession(FIRING_SQUAD)))
     {
       if (sesnptr->stat&FIRING_SQUAD)  /* redundant... */
        {
         CloseSession (sesnptr);

         return (Session *)sesnptr;
        }
     }

   return (Session *)NULL;

 }  /**/


 static void Shoot (Session *sesnptr)

 {
   pthread_join (sesnptr->th, NULL);

   KillSession (sesnptr);

 }  /**/

