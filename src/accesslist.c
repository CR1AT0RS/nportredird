/*
    nportredird - TCP/IP networks port forwarder daemon.

    Copyright (C) 1999-2001 Ayman Akt
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
#include <net/if.h>


 static dList access_list;
 static dList lnetworks_list;
 static dList lhosts_list;
 const dList *const acl_ptr=&access_list;
 const dList *const lhacl_ptr=&lhosts_list;
 const dList *const lnacl_ptr=&lnetworks_list;


 int AddACLEntry (dList *lstptr, const char *addr, const char *intraredir)

 {
	if (lstptr)
	 {
	  AccessListEntry *aclptr;

		if ((aclptr=AccessListEntryCreate(addr, intraredir)))
		 {
		  AddThisTodList (lstptr, (void *)aclptr);

		  return 1;
		 }
	}

   return 0;

#if 0
  char s[MAXHOSTLEN+20]={0};
  char *host;
  unsigned attr;
  struct in_addr sin;
  struct hostent *hp=NULL;
  struct netent *np=NULL;

    if (!lstptr)  return 0;
    if ((!addr)||(!*addr))  return 0;

   mstrncpy(s, addr, (MAXHOSTLEN+20));
   
    if ((host=strrchr(s, '/'))) /* x.x.x.x/x.x.x.x */
     {
      char *network="";
      unsigned prefix=0;

       *host=0;
       network=host+1;
       host=s;

        if (!(hp=gethostbyname(host)))  
         {
           if (!(np=getnetbyname(host)))  return 0;
         }

        if (strchr(network, '.')) /* x.x.x.x/x.x.x.x */
         {
           if (!inet_aton(network, &sin))  return 0; /*network invalid*/

          attr=ACL_ATTR_NET;
         }
        else /* x.x.x.x/x */
         {
          prefix=atoi(network); 
           if ((prefix<1)||(prefix>32))  return 0;
           if (prefix==32)  attr=ACL_ATTR_HOST;
           else  attr=ACL_ATTR_NET;
         }

       {
        AccessListEntry *aclptr;

         xmalloc(aclptr, (sizeof(AccessListEntry)));
         memset (aclptr, 0, sizeof(AccessListEntry));

         aclptr->attr=attr;
          if (hp)  memcpy (&aclptr->addr, hp->h_addr, sizeof(sin));
          else  aclptr->addr.s_addr=np->n_net;

          /*if (*network)  inet_aton(network, &aclptr->mask);
          else  aclptr->mask=NetworkPrefixToAdress(prefix);*/
          if (prefix)  aclptr->mask=NetworkPrefixToAdress(prefix);
          else  inet_aton(network, &aclptr->mask);

         AddThisTodList (lstptr, (void *)aclptr);
        
         return 1;
       }
     }
    else
     {
        if (!(hp=gethostbyname(s)))
         {
           if (!(np=getnetbyname(s)))  return 0;
         }
        /*if (!(hp=gethostbyname(s)))  return 0;*/

       {
        AccessListEntry *aclptr;

         xmalloc(aclptr, (sizeof(AccessListEntry)));
         memset (aclptr, 0, sizeof(AccessListEntry));

         aclptr->attr=ACL_ATTR_HOST;
          if (hp)  memcpy (&aclptr->addr, (void *)hp->h_addr, sizeof(sin));
          else  aclptr->addr.s_addr=np->n_net;
         /*memcpy (&aclptr->addr, (void *)hp->h_addr, sizeof(sin));*/
         aclptr->mask=NetworkPrefixToAdress(32);

         AddThisTodList (lstptr, (void *)aclptr);

         return 1;
       }

     }
#endif
 }  /**/


 /* nice stuff, but doesn't pretend to be too strict or fool-proof */
 AccessListEntry *AccessListEntryCreate (const char *addr, 
                                         const char *intraredir)

 {
  char s[MAXHOSTLEN+20]={0};
  char *host;
  unsigned attr;
  struct in_addr sin;
  struct hostent *hp=NULL;
  struct netent *np=NULL;

    if ((!addr)||(!*addr))  return NULL;

   mstrncpy(s, addr, (MAXHOSTLEN+20));
   
    if ((host=strrchr(s, '/'))) /* x.x.x.x/x.x.x.x */
     {
      char *network="";
      unsigned prefix=0;

       *host=0;
       network=host+1;
       host=s;

        if (!(hp=gethostbyname(host)))  
         {
           if (!(np=getnetbyname(host)))  return NULL;
         }

        if (strchr(network, '.')) /* x.x.x.x/x.x.x.x */
         {
           if (!inet_aton(network, &sin))  return NULL; /*network invalid*/

          attr=ACL_ATTR_NET;
         }
        else /* x.x.x.x/x */
         {
          prefix=atoi(network); 
           if ((prefix<1)||(prefix>32))  return 0;
           if (prefix==32)  attr=ACL_ATTR_HOST;
           else  attr=ACL_ATTR_NET;
         }

       {
        AccessListEntry *aclptr;

         xmalloc(aclptr, (sizeof(AccessListEntry)));
         memset (aclptr, 0, sizeof(AccessListEntry));

         aclptr->attr=attr;
         mstrncpy(aclptr->intraredir_id, intraredir, MAXREDIRID);

          if (hp)  memcpy (&aclptr->addr, hp->h_addr, sizeof(sin));
          else  aclptr->addr.s_addr=np->n_net;

          if (prefix)  aclptr->mask=NetworkPrefixToAdress(prefix);
          else  inet_aton(network, &aclptr->mask);

         return aclptr;
       }
     }
    else
     {
        if (!(hp=gethostbyname(s)))
         {
           if (!(np=getnetbyname(s)))  return NULL;
         }

       {
        AccessListEntry *aclptr;

         xmalloc(aclptr, (sizeof(AccessListEntry)));
         memset (aclptr, 0, sizeof(AccessListEntry));

         aclptr->attr=ACL_ATTR_HOST;
         mstrncpy(aclptr->intraredir_id, intraredir, MAXREDIRID);
          if (hp)  memcpy (&aclptr->addr, (void *)hp->h_addr, sizeof(sin));
          else  aclptr->addr.s_addr=np->n_net;
         aclptr->mask=NetworkPrefixToAdress(32);

         return aclptr;
       }

     }

 }  /**/



 void BuildLocalHostsNetworksACL (void)

 {
  struct ifconf ifc;
  struct ifreq ifreq;
  struct in_addr ina;
  struct sockaddr sa; 
  char *buf,
       *cp,
       *cplim;
  int bufsiz=4095,
      s, n, cpsize;

    if ((s=socket(AF_INET, SOCK_DGRAM, 0))<0)
     {
      printf ("ERR: in 'socket()': %s\n", strerror(errno));
      exit (1);
     }

    while (1!=2)
     {
      buf=malloc(bufsiz);
      ifc.ifc_len=bufsiz;
      ifc.ifc_buf=buf;

       if ((n=ioctl(s, SIOCGIFCONF, (char *)&ifc))!=-1)
        {
          if (ifc.ifc_len+2*sizeof(ifreq)<bufsiz)  break;  /*got it*/
        }

       if ((n==-1)&&(errno!=EINVAL))
        {
         printf ("ERR: get interface configuration: %s\n", strerror(errno));
         exit (1);
        }

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
         printf ("ERR: getnetconf: %s AF %d != INET\n",
                 ifreq.ifr_name, ifreq.ifr_addr.sa_family);
         continue;
        }

      sa=ifreq.ifr_addr;
      ina=((struct sockaddr_in *)&ifreq.ifr_addr)->sin_addr;

      /*printf ("*** getnetconf: considering %s [%s]\n",
              ifreq.ifr_name, inet_ntoa(ina));*/

      {
       AccessListEntry *aclptr;

        xmalloc(aclptr, (sizeof(AccessListEntry)));
        memset (aclptr, 0, sizeof(AccessListEntry));

        aclptr->attr=ACL_ATTR_HOST;
        aclptr->addr=ina;
        aclptr->mask=NetworkPrefixToAdress(32);
        AddThisTodList (&lhosts_list, aclptr);
      }

      {
       AccessListEntry *aclptr;

         if (ioctl(s, SIOCGIFNETMASK, (char *)&ifreq)<0) 
          {
           printf ("ERR: get netmask: %s\n", strerror(errno));

           continue;
          }

        xmalloc(aclptr, (sizeof(AccessListEntry)));
        memset (aclptr, 0, sizeof(AccessListEntry));

        aclptr->attr=ACL_ATTR_NET;
        aclptr->mask=((struct sockaddr_in *)&ifreq.ifr_addr)->sin_addr;
        aclptr->addr=ina;
        aclptr->addr.s_addr&=aclptr->mask.s_addr;
        AddThisTodList (&lnetworks_list, aclptr);
      }
     } /*for*/

   close (s);

   free (buf);

 }  /**/


 int AccessListMatch (const dList *lstptr, struct in_addr addr)

 {
  int ret=0;

    if (lstptr)
     {
      register dListEntry *eptr;
 
        for (eptr=lstptr->head; eptr; eptr=eptr->next)
         {
           if (((AccessListEntry *)eptr->whatever)->attr==ACL_ATTR_NET)
            {
             ret=((addr.s_addr&
                  ((AccessListEntry *)eptr->whatever)->mask.s_addr)==
                  ((AccessListEntry *)eptr->whatever)->addr.s_addr); 
            }
           else
            {
             ret=(addr.s_addr==((AccessListEntry *)eptr->whatever)->addr.s_addr);
            }

           /* stop at 1st match */
           if (ret)  break;
         }
     }

   return ret;

 }  /**/


 char *AccessListMatchIntraRedir (const dList *lstptr, struct in_addr addr)

 {
  int ret=0;
  char *redir="";

    if (lstptr)
     {
      register dListEntry *eptr;
 
        for (eptr=lstptr->head; eptr; eptr=eptr->next)
         {
           if (((AccessListEntry *)eptr->whatever)->attr==ACL_ATTR_NET)
            {
             ret=((addr.s_addr&
                  ((AccessListEntry *)eptr->whatever)->mask.s_addr)==
                  ((AccessListEntry *)eptr->whatever)->addr.s_addr); 

              if (ret) redir=((AccessListEntry *)eptr->whatever)->intraredir_id;
            }
           else
            {
             ret=(addr.s_addr==((AccessListEntry *)eptr->whatever)->addr.s_addr);
            }

           /* stop at 1st match */
           if (ret)  
            {
             redir=((AccessListEntry *)eptr->whatever)->intraredir_id; 
             break;
            } 
         }
     }

   return redir;

 }  /**/


 void PrintAccessList (const dList *lstptr)

 {
  register dListEntry *eptr;

    for (eptr=lstptr->head; eptr; eptr=eptr->next)
     {
      printf ("addr: %s, mask: %s\n", 
              inet_ntoa(((AccessListEntry *)eptr->whatever)->addr),
              inet_ntoa(((AccessListEntry *)eptr->whatever)->mask));
     }

 }  /**/

