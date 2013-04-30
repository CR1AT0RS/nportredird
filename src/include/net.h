/*
** net.h Copyright (c) 1998 Ayman Akt
**
** See the COPYING file for terms of use and conditions.
**
MODULEID("$Id: net.h,v 1.1 1999/07/26 01:46:59 ayman Exp $")
**
*/

#ifndef NET_H
# define NET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sockets.h>

/* struct resolved {
         char dns[MAXHOSTLEN];
         char dotted[14];
         unsigned long ip;
        };
*/
 struct ResolvedAddress {
        char dns[MAXHOSTLEN],
             dotted[MAXHOSTLEN];
        unsigned flags;
        struct in_addr inetaddr;
       };
 typedef struct ResolvedAddress ResolvedAddress;


 void InitNet (void); 
 int SetupListeningSocket (const char *, unsigned, unsigned);
 void FetchLocalhost (void);
 int InitTelnet (void);
 int isdottedquad (const char *);
 int RequestSocket (void);
 int RequestTCPSocket (void);
 int SetSocketFlags (int, int, int);
 int ResolveAddress (const char *, ResolvedAddress *);
 int ConnectToServer (const char *, unsigned long, Socket *);
 int ConnectToThis (const char *, unsigned long, Socket *);
 int Connect (struct in_addr *, unsigned long); 
 void nslookup (char *);
 char *RawIPToDotted (unsigned long);
 char *HostToDotted (char *);
 char *DottedToHost (char *);
 struct in_addr *NetworkToAddress (const char *);
 char *AddressToNetwork (struct in_addr *);
 int ServiceToPort (const char *, unsigned short); 
 char *PortToService (int, unsigned short); 
 char *ProtocolToName (unsigned short);
 struct in_addr NetworkPrefixToAdress (unsigned int);
 int IsLocalIP (const char *);
 
#if !(HAVE_HSTRERROR)
 char *h_strerror (int);
# define hstrerror h_strerror
#endif
 unsigned long atoul (char *);
#endif

