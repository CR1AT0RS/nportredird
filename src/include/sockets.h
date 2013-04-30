/*
** sockets.c Copyright (c) 1999 Ayman Akt
**
** See the COPYING file for terms of use and conditions.
**
MODULEID("$Id: sockets.h,v 1.1 1999/07/26 01:46:59 ayman Exp $")
**
*/

#ifndef SOCKETS_H
# define SOCKETS_H

#define NO_SOCKETS    0
                                
#define QUEUE_EMPTY 0

/* sptr->type */                                
#define SOCK_LISTENINGTELNET 2
#define SOCK_CONNECTEDTELNET 3
#define SOCK_IPC             6
#define SOCK_IPCCLIENT       7
#define SOCK_SOCKSCOUNT      8
#define SOCK_OTHER           11
#define SOCK_SNDSERVER       12

/* connection termination modes */
#define WHILE_CONNECTED (mode==1)
#define SELECT_ERROR    (mode==2)
#define FORCIBLE        (mode==3)
#define WHILE_LOGGING   (mode==4)
#define NONBLOCKING     (mode==5)

#define IS_LISTENINGTELNET(x) ((x)->type==SOCK_LISTENINGTELNET)
#define IS_CONNECTEDTELNET(x) ((x)->type==SOCK_CONNECTEDTELNET)
#define IS_OTHER(x) ((x)->type==SOCK_OTHER)
#define IS_IPC(x) ((x)->type==SOCK_IPC)
#define IS_IPCCLIENT(x) ((x)->type==SOCK_IPCCLIENT)
#define IS_SNDSERVER(x) ((x)->type==SOCK_SNDSERVER)

#define CONNECTEDTELNET    (0x1<<4)
#define AWAITINGUSERNAME   (0x1<<5)
#define AWAITINGCONNECTION (0x1<<6)
#define FIRING_SQUAD       (0x1<<7)
#define BLOCKING           (0x1<<8)
#define REPORTED           (0x1<<9)
#define TRANSIENT          (0x1<10) /* sockets waiting on certain events */

 struct SocketQueue {
         time_t  when;
         int     flag;
         char   *msg;

         struct SocketQueue *next;
        };
 typedef struct SocketQueue SocketQueue;

 struct Socket {
         time_t when;

         int type,
             sock,
             block_sz;
         unsigned flag;

         ssize_t sbytes,
                 rbytes;

         long hport,
              port;

         char address[MAXHOSTLEN],
              haddress[MAXHOSTLEN];
         void *index;  /* generic data place-holder */

         struct Socket *next;
#ifdef SOCKET_QUEUE
         long nMsg;
         SocketQueue *front,
                     *rear;
#else
         char msg[XLARGBUF];
         ssize_t msglen;
#endif
        };
 typedef struct Socket Socket;

 struct SocketsTable {
         int nEntries;
         Socket *head,
                *tail;
        };
 typedef struct SocketsTable SocketsTable;

#define SOCKETTOINDEX(x) ((Index *)(x)->index)
#define QUEUE_NOT_EMPTY(x) ((x)->nMsg>=1)

 void InitSocketsTable (void);
 Socket *AddtoSocketsTable (SocketsTable *, int);
 int RemovefromSocketsTable (SocketsTable *, int);
 void TellSocketType (const Socket *, char *);
 void TellSocketInfo (const Socket *);
 void ShowSocketsTable (void);
 Socket *SocketByName (int);
 Socket *Socketbyaddress (const char *, int);
 void ConnectionLost (int);
 void setsockflag (int, int, boolean);
 boolean SocketsTableEmpty (const SocketsTable *);
 boolean SocketsTableFull (const SocketsTable *);
 boolean SocketQueueEmpty (Socket *);

#endif

