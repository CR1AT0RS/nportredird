/*
**
**
MODULEID("$Id: sredird.h,v 1.1 1999/09/01 00:42:00 ayman Exp $")
**
*/
#ifndef NPORTREDIRD_H
# define NPORTREDIRD_H

#include <list.h> 
#include <redirection.h>
#include <sockets.h>

 enum {
  LOG_MODE_SYSLOG, LOG_MODE_OWN
 }; /*struct msredird.log_mode*/

 enum {
  RUNNING_MODE_DAEMON, RUNNING_MODE_TERM
 };

 enum {
  REDIRECTION_ACTIVE, REDIRECTION_DISABLED
 }; /*status*/

 struct RedirectionRegistry {
  struct Redirection *redir;
  unsigned long hits,
                misses;
  unsigned status; /*ACTIVE, DISABLED*/
  unsigned long current_connections_count;
  pthread_mutex_t current_connections_count_mutex;

  struct Socket *sptr; /*listening socket*/
 };
 typedef struct RedirectionRegistry RedirectionRegistry;
 
 typedef struct msredird {
          time_t when;  /* up-time... */

          unsigned running_mode; /*enum*/
          unsigned log_mode; /*own|syslog*/ /*enum*/
          char config_dir[_POSIX_PATH_MAX];
          char config_file[_POSIX_PATH_MAX];

          List redir_def; /*struct RedirectionRegistry*/

          int nready;
          pthread_mutex_t nready_mutex;
          pthread_cond_t nready_cond;
         } msredird;

 void InitNportredird (void);
 Redirection *RegisterRedirection (Redirection *);
 void LaunchRedirectors (List *);
 unsigned long GetCurrentConnectionsCount (RedirectionRegistry *);
 void IncrementCurrentConnectionsCount (RedirectionRegistry *);
 void DecrementCurrentConnectionsCount (RedirectionRegistry *);
 int AnswerTelnetRequest (RedirectionRegistry *);
 RedirectionRegistry *RedirectionRegistryLocateByID (List *, const char *);
 void RedirectionRegistryMarkInactive(Redirection *);
 void  RedirectionSignalFiringSquad (RedirectionRegistry *);
#endif

