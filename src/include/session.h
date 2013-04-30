
#ifndef SESSION_H
# define SESSION_H

#include <sockets.h>

 typedef struct Session {
          time_t when;
          unsigned stat;  /* FIRING_DQUAD */
#ifdef PER_SESSION_LOG
          LogFile logf;
#endif

          Socket *dsptr; /* destination socket */
          Socket *ssptr; /* source socket */

          void *user_data;

          pthread_t th;
          pid_t pid;
         } Session;


 Session *OpenSession (Socket *, Socket *);
 Session *GetFlaggedSession (unsigned);
 int CloseSession (Session *);
 int KillSession (Session *);
 Session *LocateSession (int);
 void PrintSessions (void);

#endif

