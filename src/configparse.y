%{
/*bison -d -o configparse.c*/
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <main.h>
#include <misc.h>
#include <configlex.h>
#include <redirection.h>
#include <accesslist.h>

MODULEID("$Id: configparse.y,v 1.1 2000/10/21 22:24:19 ayman Beta $");

#define YYDEBUG 0

static int seen_options;
static Redirection redir;
/* service names as opposed to port numbers */
static char dport[20];
static char sport[20];
static char intraredir[MAXREDIRID];
%}

%union {
	char *cp;
	int s_int;
	long num;
}

/* Lexical analyzer return values. */
%token			L_EOS
%token  <num>		L_NUMBER
%token  <cp>		L_STRING
%token  <cp>		L_QSTRING
%token	<cp> 		L_IPADDR

%token T_REDIRECTION
%token T_REDIRECTION_TYPE
%token T_DESTINATION_HOST
%token T_OPTIONS
%token T_DESTINATION_PORT
%token T_LISTEN_ON_PORT
%token T_LISTEN_ON_IP
%token T_MAX_CONNECTIONS
%token T_ACCESS_LIST
%token T_ALLOW_ALL
%token T_DENY_ALL
%token T_ALLOW
%token T_DENY
%token T_ACTIVE
%token T_PASSIVE
%token T_REDIRECTION_ID
%token T_INTRA_REDIRECT_TO
%token L_END_INCLUDE 
%token T_REQUIRE_VERSION
/* start of bison grammer */
%%

config_file: top_containers
	{
     /*nothing*/
	}
	;

top_containers: options_statement grouped_statements
	;

grouped_statements: grouped_statement
	| grouped_statements grouped_statement
	;

grouped_statement: redirection_statements
	;

/*grouped_statements: grouped_statement
	| grouped_statements grouped_statement
	;

grouped_statement: options_statement
	| redirection_statements
	;
*/
options_statement: T_OPTIONS
	{
	  if (seen_options)
	   {
		parser_error (0, "cannot redefine options");
		exit (1);
	   }
	}
	'{' options_directives '}'
	{
	 seen_options=1;
	}
	;

options_directives: option_directive
	| options_directives option_directive
	/*| options_directives error ';'*/
	;
option_directive: /*empty*/
	| T_REQUIRE_VERSION L_QSTRING L_EOS
	{
      if (!ValidateRequiredVesrion($2))
       {
        printf ("Failed to satisfy version requirement %s.\n", $2);
        exit (1);
       }  
	}
	;

redirection_statements: active_redirection_statement
	| default_redirection_statement
	| passive_redirection_statement
	;

passive_redirection_statement: T_REDIRECTION T_PASSIVE
	{
	}
	'{' passive_redirection_directives '}'
	{
          if (!redir.redir_type)  
           {
            printf ("Redirection type omitted.\n");
            exit (1); 
           }
          if (!redir.dst_host)  
           {
             printf ("Destination host omitted.\n");
             exit (1); 
           }
          if (!redir.dst_port)  
           {
             if (dport[0])
              {
				if ((redir.dst_port=ServiceToPort(dport, 
					(redir.redir_type==REDIR_TCP?
					 (IPPROTO_TCP):(IPPROTO_UDP))))==-1)
				 {
				  printf ("Invalid destination port %s.\n", dport);
				  exit (1);
				 }

               dport[0]=0;
              }
             else
              {
               printf ("Destination port omitted.\n");
               exit (1); 
              }
           }

         redir.redir_mode=REDIR_MODE_PASSIVE; 
          if (!(AddRedirection(&redir)))
           {
            printf ("unable to add redirection (%s:%u:%u)\n",
                    redir.dst_host, redir.dst_port, redir.listen_on_port);
           }
         CleanupRedirectionEntry (&redir);
	}
	;

passive_redirection_directives: passive_redirection_directive
	| passive_redirection_directives passive_redirection_directive
	| passive_redirection_directives error ';'
	;
passive_redirection_directive:
	T_REDIRECTION_ID L_QSTRING L_EOS
	{
     mstrncpy(redir.redir_id, $2, MAXREDIRID);
	}
	|
	T_REDIRECTION_TYPE L_QSTRING L_EOS
	{
	  if (arethesame($2, "tcp"))
	   {
		redir.redir_type=REDIR_TCP;
	   }
	  else
	  if (arethesame($2, "udp"))
	   {
		redir.redir_type=REDIR_UDP;
	   }
	  else
	   {
		parser_error (0, "*** Unknown redirection type '%s'", $2);
		exit (1);
	   }  
	}
	| T_DESTINATION_HOST L_QSTRING L_EOS
	{
      mstrncpy(redir.dst_host, $2, MAXHOSTLEN);	
	}
	| T_DESTINATION_PORT L_QSTRING L_EOS
	{
	  if (isdigits($2))  redir.dst_port=atoi($2);
	  else  
	   {
		mstrncpy(dport, $2, 20);
		redir.dst_port=0; 
	   }
	}
	;

active_redirection_statement: T_REDIRECTION T_ACTIVE
	{
	}
	'{' redirection_directives '}'
	{
          if (!redir.redir_type)  
           {
            printf ("Redirection type omitted.\n");
            exit (1); 
           }
          if (!redir.dst_host)  
           {
             printf ("Destination host omitted.\n");
             exit (1); 
           }
          if (!redir.dst_port)  
           {
             if (dport[0])
              {
				if ((redir.dst_port=ServiceToPort(dport, 
					(redir.redir_type==REDIR_TCP?
					 (IPPROTO_TCP):(IPPROTO_UDP))))==-1)
				 {
				  printf ("Invalid destination port %s.\n", dport);
				  exit (1);
				 }

               dport[0]=0;
              }
             else
              {
               if (!(arethesame("/dev/null", redir.dst_host)))
				{
				 printf ("Destination port omitted.\n");
				 exit (1); 
				}
              }
           }
          if (!redir.listen_on_port)  
           {
             if (sport[0])
              {
                if ((redir.dst_port=ServiceToPort(sport,
                    (redir.redir_type==REDIR_TCP?
                     (IPPROTO_TCP):(IPPROTO_UDP))))==-1)
                 {
                  printf ("Invalid local port %s.\n", sport);
                  exit (1);
                 }

               sport[0]=0;
              }
             else
              {
               printf ("Local port omitted.\n");
               exit (1); 
              } 
           }

         redir.redir_mode=REDIR_MODE_ACTIVE;
          if (!(AddRedirection(&redir)))  
           {
            printf ("unable to add redirection (%s:%u:%u)\n",
                    redir.dst_host, redir.dst_port, redir.listen_on_port);
           }
         CleanupRedirectionEntry (&redir);
	}
	;

default_redirection_statement: T_REDIRECTION
	{
	}
	'{' redirection_directives '}'
	{
          if (!redir.redir_type)  
           {
            printf ("Redirection type omitted.\n");
            exit (1); 
           }
          if (!redir.dst_host)  
           {
             printf ("Destination host omitted.\n");
             exit (1); 
           }
          if (!redir.dst_port)  
           {
             if (dport[0])
              {
    /*            if (!(arethesame("/dev/null", redir.dst_host)))*/
                 {
				   if ((redir.dst_port=ServiceToPort(dport, 
					   (redir.redir_type==REDIR_TCP?
						(IPPROTO_TCP):(IPPROTO_UDP))))==-1)
					{
					 printf ("Invalid destination port %s.\n", dport);
					 exit (1);
					}
                }

               dport[0]=0;
              }
             else
              {
               if (!(arethesame("/dev/null", redir.dst_host)))
                 {

               printf ("Destination port omitted.\n");
               exit (1);
                 } 
              }
           }
          if (!redir.listen_on_port)  
           {
             if (sport[0])
              {
                if ((redir.dst_port=ServiceToPort(sport,
                    (redir.redir_type==REDIR_TCP?
                     (IPPROTO_TCP):(IPPROTO_UDP))))==-1)
                 {
                  printf ("Invalid local port %s.\n", sport);
                  exit (1);
                 }

               sport[0]=0;
              }
             else
              {
               printf ("Local port omitted.\n");
               exit (1); 
              } 
           }

         redir.redir_mode=REDIR_MODE_ACTIVE;
          if (!(AddRedirection(&redir)))
           {
            printf ("unable to add redirection (%s:%u:%u)\n",
                    redir.dst_host, redir.dst_port, redir.listen_on_port);
           }
         CleanupRedirectionEntry (&redir);
	}
	;
redirection_directives: redirection_directive
	| redirection_directives redirection_directive
	| redirection_directives error ';'
	;
redirection_directive: /*empty*/
	T_REDIRECTION_ID L_QSTRING L_EOS
	{
     mstrncpy(redir.redir_id, $2, MAXHOSTLEN+10);
	}
	|
	T_REDIRECTION_TYPE L_QSTRING L_EOS
	{
	  if (arethesame($2, "tcp"))
	   {
		redir.redir_type=REDIR_TCP;
	   }
	  else
	  if (arethesame($2, "udp"))
	   {
		redir.redir_type=REDIR_UDP;
	   }
	  else
	   {
		parser_error (0, "*** Unknown redirection type '%s'", $2);
		exit (1);
	   }  
	}
	| T_DESTINATION_HOST L_QSTRING L_EOS
	{
     mstrncpy(redir.dst_host, $2, MAXHOSTLEN);	
	}
	| T_DESTINATION_PORT L_QSTRING L_EOS
	{
	  if (isdigits($2))  redir.dst_port=atoi($2);
	  else  
	   {
		mstrncpy(dport, $2, 20);
		redir.dst_port=0; 
	   }
	}
	| T_LISTEN_ON_PORT L_QSTRING L_EOS
	{
	  if (isdigits($2))  redir.listen_on_port=atoi($2);
	  else
	   {
		mstrncpy(sport, $2, 20);
		redir.listen_on_port=0;
	   }
	}
	| T_MAX_CONNECTIONS L_QSTRING L_EOS
	{
      if (!(isdigits($2))) 
	   {
        parser_error (0, "max_connections needs numeric");
        redir.max_connections=0;
       }	

	 redir.max_connections=atoi($2);
	}
    | T_LISTEN_ON_IP L_QSTRING L_EOS
    {
     mstrncpy(redir.local_host, $2, MAXHOSTLEN);
     /*printf("local ip %s\n", $2); */
    } 
	| accesslist_group
	{
      	 /**/
	}
	;
accesslist_group: T_ACCESS_LIST
	{
	}
	'{' accesslist_list '}'
	{
	}
	;
accesslist_list: accesslist_list_directive
	| accesslist_list accesslist_list_directive
	| accesslist_list error ';'
	;
accesslist_list_directive: /*empty*/
	T_ALLOW_ALL L_EOS
	{
         /*redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_ALLOW;*/
	}
	| T_DENY_ALL L_EOS
	{
         /*redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_DENY;*/
	}
	|
	allow_group_stat
	|
	deny_group_stat
	;
allow_group_stat: T_ALLOW
        {
         if (redir.redir_access_list.redir_access_mode==REDIR_ACCESS_MODE_ALLOW)
          {
           printf ("inconsistent access definition\n");
           exit (1);
          }
         if (redir.redir_access_list.redir_access_mode==REDIR_ACCESS_MODE_DENY)
          {
           printf ("multiple definition of allow access\n");
           exit (1);
          }
        }
        '{' allow_group '}'
        {
        redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_DENY;
        }
        ;
allow_group: allow_group_directive
        | allow_group allow_group_directive
        | allow_group error ';'
        ;
allow_group_directive: /*empty*/
        L_QSTRING L_EOS
        {
          if (!(AddACLEntry(&redir.redir_access_list.access_list, $1, "")))
           {
            printf ("invalid host definition '%s'\n", $1);
           }
        }
		| L_QSTRING allow_group_redirected_redirective
        {
         if (!(AddACLEntry(&redir.redir_access_list.access_list, $1, intraredir)))
           {
            printf ("invalid host definition '%s'\n", $1);
           }
         intraredir[0]=0;
        } 
        ;

allow_group_redirected_redirective: T_INTRA_REDIRECT_TO L_QSTRING L_EOS
        {
         mstrncpy(intraredir, $2, MAXREDIRID);
        }
		;

deny_group_stat: T_DENY
        {
         if (redir.redir_access_list.redir_access_mode==REDIR_ACCESS_MODE_DENY)
          {
           printf ("inconsistent access definition\n");
           exit (1);
          }
         if (redir.redir_access_list.redir_access_mode==REDIR_ACCESS_MODE_ALLOW)
          {
           printf ("multiple definition of deny access\n");
           exit (1);
          }
        }
        '{' deny_group '}'
        {
        redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_ALLOW;
        }
        ;
deny_group: deny_group_directive
        | deny_group deny_group_directive
        | deny_group error ';'
        ;
deny_group_directive: /*empty*/
        L_QSTRING L_EOS
        {
          if (!(AddACLEntry (&redir.redir_access_list.access_list, $1, "")))
           {
            printf ("invalid host definition '%s'\n", $1);
           }
        }
        ;
/* end of bison grammar */
%%

