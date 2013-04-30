  nportredird - TCP/IP Networks Port Redirector
  Ayman Akt <ayman@pobox.com>
  Version 0.6  18/03/2001
  ____________________________________________________________

  Table of Contents


  1. Copyright

  2. Introduction

  3. Installation

  4. Running

  5. Contribution

  6. Bugs



  ______________________________________________________________________

  11..  CCooppyyrriigghhtt

  This software is Copyright (c) 1999-2001 Ayman Akt.  nportredird is
  released under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.


  Please consult the file COPYING for the exact terms.



  22..  IInnttrroodduuccttiioonn

  Nportredird is a UNIX server program that can redirect (forward)
  TCP/IP connections between servers and clients. It acts as a "middle
  man" and therefore can enforce certain policies. Currently supported
  policies:

  +o  Access restrictions based on IP addresses.

  +o  Limit on the number of concurrent connections.


  This is very popular concept and extremely useful in situations where
  certain protected services need to be exposed to the
  outside--securely.


  Nportredird can handle multible, concurrent connections to one, or
  more remote ends making it ideal as a central redirection facility.

  Nportredird offers many variations on the concept of redirection which
  can be helpful for people with rather exotic demands. For example you
  can redirect an incoming connection to /dev/null, or fork multible
  redirections off the same port number based on IP addresses (also
  known within the program as intra-redirection).

  The implementation is multi-threaded and scales very well. Its memory
  footprint is quite light.


  The software lacks quite a few features, which I hope to implement
  later:

  +o  UDP connections are not supported

  +o  ftp traffic cannot be redirected


  33..  IInnssttaallllaattiioonn

  Please read the INSTALL file for detailed intructions. The
  installation procedure follows the standard UNIX convention, namely;

  _._/_c_o_n_f_i_g_u_r_e_; _m_a_k_e_; _m_a_k_e _i_n_s_t_a_l_l

  A sample configuration file is provided. It's copied to
  /etc/nportredird by default.



  44..  RRuunnnniinngg

  The defaults insure command-line parameters-free invocation. The
  server will run in daemon mode by default, i.e. it will detach itself
  from the controlling terminal and log with your system's syslog
  facility.  Please run the software with the '-h' switch for more
  details.


  The programs is completely configuration file-driven; therefore you
  have to write one that reflects your needs. The configuration file is
  well structured and quite easy to put together. A sample file is
  provided.


  A standard UNIX man page is also provided and offers some hints and
  information on the various invocation modes and features. The man page
  is currently the most uptodate and authoritative documentation
  available.



  55..  CCoonnttrriibbuuttiioonn

  I've set up a mailing list and discussion group at
  <http://www.egroups.com/group/nportredird>. You can join through the
  web interface, or send e-mail to <nportredird-subscribe@egroups.com>


  66..  BBuuggss

  The program has been in use in production systems for quite some time
  and seems to hang together very well. But, I have been toying with it
  lately and added some "features", and those features cut right through
  the thing, therefore I'm not sure how well-behaved they are. My
  initial tests look OK.

  Please read the BUGS file for any known issues.

  You can send your bug reports to the mailing list at
  <http://www.egroups.com/group/nportredird>





