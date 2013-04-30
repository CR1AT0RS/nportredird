/*
**
**
MODULEID("$Id: main.h,v 1.1 1999/07/26 01:46:59 ayman Exp $")
**
*/
#ifndef MAIN_H
# define MAIN_H

#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <pthread.h>

#include "utils.h"

#define MODULEID(id) static const char rcs[]=id;

 /* Standard boolean definition */
 typedef enum { False, True } Boolean;

 typedef enum {FALSE, TRUE} boolean;

#define xmalloc(x, y) \
         (x)=malloc ((y)); \
          if (!(x)) \
           { \
            printf("Unable to obtain additional memory--quiting\n"); \
            exit (1); \
           }

#define xfree(x) free((x)); (x)=NULL
#define log(x...) syslog(LOG_INFO|LOG_LOCAL7, x)
#define logf(x, y...) fprintf ((x)->logf.file, y)
#define say(x...) printf(x)
#define arethesame(x, y) (!strcasecmp((x), (y)))
#define mstrncpy(s, p, n) \
   strncpy (s, p, strlen(p)>n-1?n:strlen(p)+1); \
   s[n-1]='\0'

#define BACKGROUND     (1<<9)

#define ALL      1
#define NUMBER   2
#define NAME     3
#define WILDCARD 4

#define MODE1 1
#define MODE2 2

#define MAXREDIRID  (MAXHOSTLEN+10)

#define MINIBUF     50
#define SMALLBUF    150
#define MEDIUMBUF   300
#define LARGBUF     600
#define XLARGBUF    1024
#define XXLARGBUF   2048

#define NOTCONNECTED 1
#define CONNECTED    2
#define TRYING       4

/* mptr->flags */
#define DEV_RESERVED (0x1<<0)

 int main (int, char **);
 void *Thread (void *);
 void SetConfigurationDefaults (void);
 void CheckCommandLine (int, char **);
 void Help (void);

#endif

