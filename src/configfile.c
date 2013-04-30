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
#include <list.h>
#include <configfile.h>
#include <configlex.h>
#include <sys/stat.h>
#include <nportredird.h>


 static unsigned long FileExist (char *, const char *);


 static unsigned long FileExist (char *file, const char *conf)

 {
  char path[_POSIX_PATH_MAX];
  struct stat st;
  extern msredird *const masterptr;

   sprintf (path, "%s/%s", masterptr->config_dir, masterptr->config_file);

   strcpy (file, path);

    if ((access(path, F_OK|R_OK))<0)  return 0;

    if ((stat(path, &st))<0)  return 0;

    return st.st_size;

 }  /**/


 int ProcessConfigfile (const char *conf)

 {
  char path[_POSIX_PATH_MAX];
  unsigned long size;
  FILE *fp;
  extern int yyparse (void);
  extern msredird *const masterptr;

   size=FileExist(path, conf);
      
    if (!size)
     {
      syslog (LOG_INFO, "Configuration file is missing (%s) - %s", 
              path, strerror(errno));
      fprintf (stderr, "Configuration file is missing (%s) - %s.\n",
               path, strerror(errno));

      exit (1);
     } 

    if (!(fp=fopen(path, "r")))
     {
      syslog (LOG_INFO, 
              "Unable to open configuration file (%s) - %s", 
              path, strerror(errno));
      fprintf (stderr, 
               "Unable to open configuration file (%s) - %s",
              path, strerror(errno));

      exit (1);
     }

   {
    lexer_initialize ();
    lexer_setup ();

    lexer_begin_file (path, NULL);

    yyparse();
   }

   fclose (fp);

   {
     if (masterptr->redir_def.nEntries==0)
      {
       fprintf (stderr, "No redirections found.\n");
       syslog (LOG_INFO, "No redirections found.");

       exit (1);
      }
   }

   return 1;

 }  /**/

