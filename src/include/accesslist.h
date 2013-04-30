#ifndef ACCESSLIST_H
# define ACCESSLIST_H

#include <net.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <list.h>

 enum {
  ACL_ATTR_NET=1, 
  ACL_ATTR_HOST
 };

 struct AccessListEntry {
  unsigned attr;
  struct in_addr addr;
  struct in_addr mask;
  /*ugly hack*/
  char intraredir_id[MAXREDIRID];
 };
 typedef struct AccessListEntry AccessListEntry;


 AccessListEntry *AccessListEntryCreate (const char *, const char *);
 void BuildLocalHostsNetworksACL (void);
 void PrintAccessList (const dList *);
 int AccessListMatch (const dList *, struct in_addr);
 char *AccessListMatchIntraRedir (const dList *, struct in_addr);
 int AddACLEntry (dList *, const char *, const char *);
 
#endif

