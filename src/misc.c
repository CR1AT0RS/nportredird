/*
    nportredird - TCP/IP networks port forwarder daemon.

    Copyright (C) 1999-2001  Ayman Akt
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
#include <signal.h>
#include <misc.h>

 MODULEID("$Id: misc.c,v 1.4 2000/03/29 09:27:04 ayman Beta $");


 signal_f *nsignal (int signo, signal_f *func)

 {
  struct sigaction  sa,
                    osa;

   sa.sa_handler=func;
   sigemptyset (&sa.sa_mask);
   sa.sa_flags|=SA_RESTART;

    if (sigaction(signo, &sa, &osa)<0)
     {
      return (SIG_ERR);
     }

   return (osa.sa_handler);

 }  /**/


 void InitSignals (void)

 {
   if (nsignal(SIGPIPE, SIG_IGN)==SIG_ERR)
     {
      psignal (SIGPIPE, "Couldn't install signal handler");
      exit (0);
     }

 }  /**/


 /*
 ** "+x.y" --> c_version >= "x.y"
 ** "-x.y" --> c_version <= "x.y"
 ** "x.y" --> c_version == "x.y"
 ** return 1 if any of the above conditions is true
 */
 int ValidateRequiredVesrion (const char *s)

 {
  char per=0;
  const char *p;
  extern const char *c_version;

	if ((s)&&(*s))
	 {
      float cv, /*current version*/
            v;

       p=s;
	   sscanf(p, "%f", &v);
	   sscanf(c_version, "%f", &cv);
 
		if ((*p=='+')||(*p=='-'))  per=*p++;

		if (!per)
		 {
		   return (!(strcmp(c_version, p)));
		 }
		else
		 {
			if (per=='+')  return (cv>=v);
			else  return (cv<=v);
		 }
	 } 

   return 0;

 } /**/


 void dummy (void)

 {
 }  /**/

