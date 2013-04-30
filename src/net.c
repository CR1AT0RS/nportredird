/*
** net.c Copyright (c) 1998,99,00 Ayman Akt
** 
*/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <main.h>
#include <net.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/un.h>
#include <fcntl.h>
#include <netdb.h>
#include <sockets.h>
#include <net/if.h>

 char *localhost="";
 unsigned long localip;


 void InitNet (void)

 {

 }  /**/


#include <sys/stat.h>

                                                                 /*tcp,udp*/
 int SetupListeningSocket (const char *ip, unsigned port, unsigned sock_type)

 {
  int reuse,
      telnet_sock;
  struct sockaddr_in telnet;
  struct in_addr ina;

   memset ((char *)&telnet, 0, sizeof(telnet));

    if ((ip)&&(!inet_aton(ip, &ina)))  return 0;

   telnet.sin_family=AF_INET;
   telnet.sin_port=htons(port);
   telnet.sin_addr.s_addr=(ip)?(ina.s_addr):(htonl(INADDR_ANY));

   telnet_sock=RequestTCPSocket();

   setsockopt (telnet_sock,
	           SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	 
    if (bind(telnet_sock, (struct sockaddr *)&telnet, sizeof(telnet))<0)
     {
      close (telnet_sock);

      return -1;  /*caller should read errno*/
     }

    if ((listen(telnet_sock, 1)<0)&&(errno!=EINTR))
     {
      close (telnet_sock);

      return -1;  /*caller should read errno*/
     }

   return telnet_sock;

 }  /**/


 int ConnectToThis (const char *server, unsigned long port, Socket *sptr)

 {
  int nsocket=0;

    if (!strcmp("/dev/null", server))
     {
       if ((nsocket=open("/dev/null", O_RDWR))==-1)
        {
         syslog (LOG_INFO, "Unable to open /dev/null -- %s", strerror(errno));

         return 0;
        }

      if (sptr)
	   {
		sptr->when=time(NULL);
		sptr->hport=0;
		sptr->port=0;
		sptr->sock=nsocket;
		strcpy (sptr->haddress, server);
		strcpy (sptr->address, "localhost");
	   }
     }

   return nsocket;

 }  /**/


 /*
 ** If socket returned is < 0, then we know the connection is still
 ** in progress, i.e., it hasn't been accepted straight away...
 ** We need to persue that in our select function.
 **
 ** dsptr->haddress: dest_host
 ** dsptr->hport: dest_port
 ** dsptr->address: localhost
 ** dsptr->port: our port to that connection
 **
 ** ssptr->haddress: connecting host
 ** ssptr->hport: hist port
 ** ssptr->address: localhost
 ** ssptr->port: our port on which he's connected
 */
 int ConnectToServer (const char *server, unsigned long port, Socket *sptr)

 {
  int len,
      nsocket;
  ResolvedAddress raddr;
  struct sockaddr_in me;

   memset (&raddr, 0, sizeof(ResolvedAddress));

   say ("*** Resolving server %s...\n", server);

    if (!(ResolveAddress(server, &raddr)))  return 0;

   say ("*** Negotiating connection to %s (%s) on port %lu...\n",
         raddr.dns, raddr.dotted, port);

    if (!(nsocket=Connect(&raddr.inetaddr, port)))  return 0;

    if (getsockname(abs(nsocket),(struct sockaddr*)&me,(len=sizeof(me),&len))<0)     {
      syslog (LOG_INFO, "'getsockname' failed on socket %d", nsocket);

      close (abs(nsocket));

      return 0;
     }

    if (sptr)
     {
      sptr->when=time(NULL);
      sptr->hport=port;
      sptr->port=ntohs(me.sin_port);
      sptr->sock=abs(nsocket);
      strcpy (sptr->haddress, server);
      strcpy (sptr->address, "localhost");

       if (nsocket<0)  sptr->flag|=BLOCKING;  /* in fact non-blocking...*/
     }

   return nsocket;

 }  /**/



 /*
 ** Caller should allocate radrr 
 */ 
 int ResolveAddress (const char *address, ResolvedAddress *raddr)

 {
  struct hostent *hp;
  struct in_addr saddr;

    if (!raddr)  return 0;
    if (!(hp=gethostbyname(address)))  
     {
      syslog (LOG_INFO, "Unable to resolve %s - %s.\n", 
               address, hstrerror(h_errno));

      return 0;
     }

   memcpy (&saddr, hp->h_addr, sizeof(saddr));
   mstrncpy(raddr->dns, hp->h_name, MAXHOSTLEN);
   mstrncpy(raddr->dotted, inet_ntoa(saddr), MAXHOSTLEN);
   memcpy (&raddr->inetaddr, (void *)hp->h_addr, sizeof(saddr));

   return 1;
 }  /**/


 int Connect (struct in_addr *addr, unsigned long port) 

 {
  int sock, 
      connected;
  struct sockaddr_in address;

   memset ((char *)&address, 0, sizeof(address));

   address.sin_family=AF_INET;
   address.sin_port=htons(port);
   address.sin_addr.s_addr=addr->s_addr;
   
    if (!(sock=RequestSocket()))
     {
      syslog (LOG_INFO, "*** Unable to obtain socket -  %s.\n", 
              strerror(errno));

      return 0;
     }

    if (!(SetSocketFlags(sock, 1, O_NONBLOCK)))  return 0;
       
   connected=connect(sock, (struct sockaddr *)&address, sizeof(address));

   switch (connected)
    {
     case 0:
      SetSocketFlags (sock, 0, O_NONBLOCK);
      return sock;

     default:
       if (errno!=EINPROGRESS) 
        {
         syslog (LOG_INFO, "*** Connection refused - %s.\n", strerror(errno));
         close (sock);

         return 0;
        }
       else
        {
         return (-sock);  /* in progress */
        }
    }

 }  /**/


 int RequestSocket (void)

 {
  int nsocket;
  
    if ((nsocket=socket(AF_INET, SOCK_STREAM, 0))<0)  return 0;

   return nsocket;

 }  /**/


 int RequestTCPSocket (void)

 {
  int nsocket;
  
    if ((nsocket=socket(AF_INET, SOCK_STREAM, 0))<0)  return 0;

   return nsocket;

 }  /**/


 int SetSocketFlags (int socket, int ON_OFF, int flags)

 {
  int cur;

     if ((cur=fcntl(socket, F_GETFL, 0))<0)
      {
       syslog (LOG_INFO, "*** Unable to F_GETFL socket - %s.\n", strerror(errno));

       return 0;
      }

   switch (ON_OFF)
     {
      case 1:
       cur|=flags;
       break;

      case 0:
       cur&=~flags;
       break;
      }
    
    if ((fcntl(socket, F_SETFL, cur))<0)
     {
      syslog (LOG_INFO, "*** Unable to set socket flags - %s.\n", 
              strerror(errno));

      return 0;
     }

   return 1;

 }  /**/


     /*AddressToDotted*/
 char *RawIPToDotted (unsigned long raw)

 {
  static char rv[16];
  unsigned long ip;
 
   ip=htonl (raw);
 
   sprintf (rv, "%d.%d.%d.%d",
            (int)((ip>>0)&0xFF),
            (int)((ip>>8)&0xFF),
            (int)((ip>>16)&0xFF),
            (int)((ip>>24)&0xFF));

   return rv;

 }  /**/


 char *HostToDotted (char *host)
 
 {
  unsigned long ip;
  struct hostent *hp;
  struct in_addr addr;
   
    if (isdottedquad(host))  return host;

   hp=gethostbyname(host);

    if (hp==(struct hostent *)NULL)  return ((char *)NULL);

  memcpy ((void *)&addr, (void *)hp->h_addr, sizeof(addr));

  ip=ntohl(addr.s_addr);

   if (!ip)  return ((char *)NULL);

  return (RawIPToDotted(ip));

 }  /**/


 char *DottedToHost (char *dip) 
 {
  struct sockaddr_in addr;
  struct hostent *hp;

   addr.sin_addr.s_addr=inet_addr(dip);

   hp=gethostbyaddr((char *)&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
    if (hp==(struct hostent *)NULL)  return ((char *)dip);

   return ((char *)hp->h_name);

 }  /**/


 struct in_addr *NetworkToAddress (const char *name)

 {
  struct netent *net;
  static struct in_addr addr;

    if ((net=getnetbyname(name))!=NULL) 
     {
       if (net->n_addrtype!=AF_INET)  return (struct in_addr *)NULL;

      addr.s_addr=htonl((unsigned long)net->n_net);

      return &addr;
     } 
    else
     {
      return (struct in_addr *)NULL;
     }
 
 }  /**/


 char *AddressToNetwork (struct in_addr *addr)

 {
  struct netent *net;

    if ((net=getnetbyaddr((long) ntohl(addr->s_addr), AF_INET))!=NULL)
      return (char *)net->n_name;
    else
     return (char *)NULL;

 }  /**/


 /* ("irc", IPPROTO_TCP) --> 6667 */
 int ServiceToPort (const char *name, unsigned short proto)

 {
  struct servent *service;

    if ((proto==IPPROTO_TCP)&&
	((service=getservbyname(name, "tcp"))!=NULL))
     return ntohs((unsigned short) service->s_port);
    else 
    if ((proto==IPPROTO_UDP)&&
	((service=getservbyname(name, "udp"))!=NULL))
     return (ntohs((unsigned short)service->s_port));
    else
     return -1;

 }  /**/


 char *PortToService (int port, unsigned short proto)

 {
  struct servent *service;

    if ((proto==IPPROTO_TCP)&&
        ((service=getservbyport(htons(port), "tcp"))!=NULL))
     return service->s_name;
    else 
    if ((proto==IPPROTO_UDP)&&
        ((service=getservbyport(htons(port), "udp"))!=NULL))
     return service->s_name;
    else /*add more here*/
     return (char *)NULL;

 }  /**/


 /* (6) --> TCP */
 char *ProtocolToName (unsigned short proto)

 {
  /*const struct pprot *pp;*/

    if (proto) 
     {
      struct protoent *pent=getprotobynumber(proto);

   	    if (pent)  return pent->p_name;
     }

   return NULL;

 }  /**/


 int isdottedquad (const char *address)

 {
  register int n,
           numbered=1;

   n=strlen(address)-1;

    while ((address[n]!='.')&&(n))
    {
      if ((address[n]<'0')||(address[n]>'9'))
	   {
		numbered=0;
		break;
	   }

     n--;
    }

   return numbered;

 }  /**/


 struct in_addr NetworkPrefixToAdress (unsigned int bits)

 {
  struct in_addr addr;
  unsigned long mask;

    memset (&addr, 0, sizeof(struct in_addr));

   if (bits==0)  mask=0;
   else 
    {
     /* set the 'mask_bits' most significant bits */
     mask=0xffffffffU;
     mask>>=(32-bits);
     mask<<=(32-bits);
    }

   mask=ntohl(mask);
   addr.s_addr=mask;

   return addr;

 }  /**/


 int IsLocalIP (const char *ip)

 {
  struct ifconf ifc;
  struct ifreq ifreq;
  struct in_addr ina,
                 tmpina;
  struct sockaddr sa; 
  char *buf,
       *cp,
       *cplim;
  int bufsiz=4095,
      s, n, cpsize;

     if ((!ip)||(!*ip))  return -1;

     if (!inet_aton(ip, &tmpina))  return -2; /*illformed addr*/
  

    if ((s=socket(AF_INET, SOCK_DGRAM, 0))<0)  return -1;

    while (1!=2)
     {
      buf=malloc(bufsiz);
      ifc.ifc_len=bufsiz;
      ifc.ifc_buf=buf;

       if ((n=ioctl(s, SIOCGIFCONF, (char *)&ifc))!=-1)
        {
          if (ifc.ifc_len+2*sizeof(ifreq)<bufsiz)  break;  /*got it*/
        }

       if ((n==-1)&&(errno!=EINVAL))  return -1;

      free (buf);
      bufsiz+=4096;  /* try again*/
     }  /*while*/

   cplim=buf+ifc.ifc_len;
    for (cp=buf; cp<cplim; cp+=cpsize)
     {
      memcpy (&ifreq, cp, sizeof(ifreq));

#if HAVE_SA_LEN
      cpsize = sizeof ifreq;
       if (ifreq.ifr_addr.sa_len>sizeof(struct sockaddr))
        cpsize+=(int)ifreq.ifr_addr.sa_len-(int)(sizeof(struct sockaddr));
#else
      cpsize=sizeof(ifreq);
#endif

       if (ifreq.ifr_addr.sa_family!=AF_INET)
        {
         /*printf ("ERR: getnetconf: %s AF %d != INET\n",
                 ifreq.ifr_name, ifreq.ifr_addr.sa_family);*/
         continue;
        }

      sa=ifreq.ifr_addr;
      ina=((struct sockaddr_in *)&ifreq.ifr_addr)->sin_addr;

      /*printf ("*** getnetconf: considering %s [%s]\n",
              ifreq.ifr_name, inet_ntoa(ina));*/

       if (ina.s_addr==tmpina.s_addr)  return 1;
     } /*for*/

   close (s);

   free (buf);

   return 0;

 }  /**/


 unsigned long atoul (char *addr)

 {
  unsigned long ip=0L;

   if (!addr)  return 0L;

    while ((*addr>='0')&&(*addr<='9'))
     {
      ip=(ip*10)+(*addr++)-'0';
     }

   return ip;

 }  /**/


#if !(HAVE_HSTRERROR) 
 static char *_h_errlist[]={
    "You should be fine",
    "Host not found",
    "Host name lookup failure",
    "Unknown server error",
    "No address associated with name",
    "Service unavailable",
};

static int _h_nerr = sizeof(_h_errlist)/sizeof(_h_errlist[0]);

 char *h_strerror (int error)

 {
  static char aux[35];

    if ((error<0)||(error>_h_nerr)) 
       {
        sprintf (aux, "Unknown resolver error");

        return (char *)aux;
       }

   return (char *)_h_errlist[error];

 }  /**/
#endif

