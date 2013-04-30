/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     L_EOS = 258,
     L_NUMBER = 259,
     L_STRING = 260,
     L_QSTRING = 261,
     L_IPADDR = 262,
     T_REDIRECTION = 263,
     T_REDIRECTION_TYPE = 264,
     T_DESTINATION_HOST = 265,
     T_OPTIONS = 266,
     T_DESTINATION_PORT = 267,
     T_LISTEN_ON_PORT = 268,
     T_LISTEN_ON_IP = 269,
     T_MAX_CONNECTIONS = 270,
     T_ACCESS_LIST = 271,
     T_ALLOW_ALL = 272,
     T_DENY_ALL = 273,
     T_ALLOW = 274,
     T_DENY = 275,
     T_ACTIVE = 276,
     T_PASSIVE = 277,
     T_REDIRECTION_ID = 278,
     T_INTRA_REDIRECT_TO = 279,
     L_END_INCLUDE = 280,
     T_REQUIRE_VERSION = 281
   };
#endif
/* Tokens.  */
#define L_EOS 258
#define L_NUMBER 259
#define L_STRING 260
#define L_QSTRING 261
#define L_IPADDR 262
#define T_REDIRECTION 263
#define T_REDIRECTION_TYPE 264
#define T_DESTINATION_HOST 265
#define T_OPTIONS 266
#define T_DESTINATION_PORT 267
#define T_LISTEN_ON_PORT 268
#define T_LISTEN_ON_IP 269
#define T_MAX_CONNECTIONS 270
#define T_ACCESS_LIST 271
#define T_ALLOW_ALL 272
#define T_DENY_ALL 273
#define T_ALLOW 274
#define T_DENY 275
#define T_ACTIVE 276
#define T_PASSIVE 277
#define T_REDIRECTION_ID 278
#define T_INTRA_REDIRECT_TO 279
#define L_END_INCLUDE 280
#define T_REQUIRE_VERSION 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 25 "configparse.y"

	char *cp;
	int s_int;
	long num;



/* Line 2068 of yacc.c  */
#line 110 "configparse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


