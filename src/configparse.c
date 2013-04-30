/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "configparse.y"

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


/* Line 268 of yacc.c  */
#line 96 "configparse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 25 "configparse.y"

	char *cp;
	int s_int;
	long num;



/* Line 293 of yacc.c  */
#line 192 "configparse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 204 "configparse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    16,    22,
      24,    27,    28,    32,    34,    36,    38,    39,    46,    48,
      51,    55,    59,    63,    67,    71,    72,    79,    80,    86,
      88,    91,    95,    99,   103,   107,   111,   115,   119,   123,
     125,   126,   132,   134,   137,   141,   144,   147,   149,   151,
     152,   158,   160,   163,   167,   170,   173,   177,   178,   184,
     186,   189,   193
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      31,     0,    -1,    32,    -1,    35,    33,    -1,    34,    -1,
      33,    34,    -1,    39,    -1,    -1,    11,    36,    27,    37,
      28,    -1,    38,    -1,    37,    38,    -1,    -1,    26,     6,
       3,    -1,    44,    -1,    46,    -1,    40,    -1,    -1,     8,
      22,    41,    27,    42,    28,    -1,    43,    -1,    42,    43,
      -1,    42,     1,    29,    -1,    23,     6,     3,    -1,     9,
       6,     3,    -1,    10,     6,     3,    -1,    12,     6,     3,
      -1,    -1,     8,    21,    45,    27,    48,    28,    -1,    -1,
       8,    47,    27,    48,    28,    -1,    49,    -1,    48,    49,
      -1,    48,     1,    29,    -1,    23,     6,     3,    -1,     9,
       6,     3,    -1,    10,     6,     3,    -1,    12,     6,     3,
      -1,    13,     6,     3,    -1,    15,     6,     3,    -1,    14,
       6,     3,    -1,    50,    -1,    -1,    16,    51,    27,    52,
      28,    -1,    53,    -1,    52,    53,    -1,    52,     1,    29,
      -1,    17,     3,    -1,    18,     3,    -1,    54,    -1,    59,
      -1,    -1,    19,    55,    27,    56,    28,    -1,    57,    -1,
      56,    57,    -1,    56,     1,    29,    -1,     6,     3,    -1,
       6,    58,    -1,    24,     6,     3,    -1,    -1,    20,    60,
      27,    61,    28,    -1,    62,    -1,    61,    62,    -1,    61,
       1,    29,    -1,     6,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    66,    69,    70,    73,    85,    84,    98,
      99,   102,   103,   113,   114,   115,   119,   118,   164,   165,
     166,   169,   174,   191,   195,   207,   206,   276,   275,   347,
     348,   349,   352,   357,   374,   378,   387,   396,   406,   411,
     417,   416,   423,   424,   425,   428,   432,   437,   439,   442,
     441,   459,   460,   461,   464,   471,   481,   488,   487,   505,
     506,   507,   510
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "L_EOS", "L_NUMBER", "L_STRING",
  "L_QSTRING", "L_IPADDR", "T_REDIRECTION", "T_REDIRECTION_TYPE",
  "T_DESTINATION_HOST", "T_OPTIONS", "T_DESTINATION_PORT",
  "T_LISTEN_ON_PORT", "T_LISTEN_ON_IP", "T_MAX_CONNECTIONS",
  "T_ACCESS_LIST", "T_ALLOW_ALL", "T_DENY_ALL", "T_ALLOW", "T_DENY",
  "T_ACTIVE", "T_PASSIVE", "T_REDIRECTION_ID", "T_INTRA_REDIRECT_TO",
  "L_END_INCLUDE", "T_REQUIRE_VERSION", "'{'", "'}'", "';'", "$accept",
  "config_file", "top_containers", "grouped_statements",
  "grouped_statement", "options_statement", "$@1", "options_directives",
  "option_directive", "redirection_statements",
  "passive_redirection_statement", "$@2", "passive_redirection_directives",
  "passive_redirection_directive", "active_redirection_statement", "$@3",
  "default_redirection_statement", "$@4", "redirection_directives",
  "redirection_directive", "accesslist_group", "$@5", "accesslist_list",
  "accesslist_list_directive", "allow_group_stat", "$@6", "allow_group",
  "allow_group_directive", "allow_group_redirected_redirective",
  "deny_group_stat", "$@7", "deny_group", "deny_group_directive", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    33,    33,    34,    36,    35,    37,
      37,    38,    38,    39,    39,    39,    41,    40,    42,    42,
      42,    43,    43,    43,    43,    45,    44,    47,    46,    48,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    49,
      51,    50,    52,    52,    52,    53,    53,    53,    53,    55,
      54,    56,    56,    56,    57,    57,    58,    60,    59,    61,
      61,    61,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     0,     5,     1,
       2,     0,     3,     1,     1,     1,     0,     6,     1,     2,
       3,     3,     3,     3,     3,     0,     6,     0,     5,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       0,     5,     1,     2,     3,     2,     2,     1,     1,     0,
       5,     1,     2,     3,     2,     2,     3,     0,     5,     1,
       2,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     0,     2,     0,     0,     1,    27,     3,     4,
       6,    15,    13,    14,    11,    25,    16,     0,     5,     0,
       0,     9,     0,     0,     0,     0,     8,    10,     0,     0,
       0,     0,     0,     0,     0,     0,    40,     0,     0,    29,
      39,    12,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    30,
      26,     0,     0,     0,     0,     0,    17,    19,    33,    34,
      35,    36,    38,    37,     0,    32,    31,    22,    23,    24,
      21,    20,     0,     0,    49,    57,     0,    42,    47,    48,
      45,    46,     0,     0,     0,    41,    43,     0,     0,    44,
       0,     0,    51,     0,     0,    59,    54,     0,    55,     0,
      50,    52,    62,     0,    58,    60,     0,    53,    61,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     8,     9,     4,     5,    20,    21,    10,
      11,    23,    47,    48,    12,    22,    13,    17,    38,    39,
      40,    55,    86,    87,    88,    92,   101,   102,   108,    89,
      93,   104,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yytype_int8 yypact[] =
{
     -10,   -37,    10,   -37,     8,    -7,   -37,    19,     8,   -37,
     -37,   -37,   -37,   -37,    -3,   -37,   -37,    -6,   -37,    27,
      23,   -37,    28,    30,    50,    55,   -37,   -37,    50,    -5,
      44,    48,    61,    66,    70,    71,   -37,    72,    -1,   -37,
     -37,   -37,    16,    73,    74,    75,    76,    33,   -37,    80,
      81,    82,    83,    84,    85,    62,    87,    63,   -37,   -37,
     -37,    88,    90,    91,    92,    67,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,    51,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,    94,    95,   -37,   -37,    18,   -37,   -37,   -37,
     -37,   -37,    77,    78,    79,   -37,   -37,    93,    96,   -37,
       0,    46,   -37,    97,    47,   -37,   -37,   100,   -37,    86,
     -37,   -37,   -37,    89,   -37,   -37,    98,   -37,   -37,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,    99,   -37,   -37,   -37,   101,   -37,
     -37,   -37,   -37,    56,   -37,   -37,   -37,   -37,   102,   -36,
     -37,   -37,   -37,    24,   -37,   -37,   -37,    11,   -37,   -37,
     -37,   -37,     5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,     1,    59,   106,    43,    44,    59,    45,    30,    31,
       6,    32,    33,    34,    35,    36,     7,    57,    46,    94,
      14,    24,    37,    19,   107,    30,    31,    58,    32,    33,
      34,    35,    36,    25,    65,    82,    83,    84,    85,    37,
      15,    16,    43,    44,    60,    45,    95,   109,   113,    19,
      49,    26,   100,   103,    50,    28,    46,    29,    41,    30,
      31,    66,    32,    33,    34,    35,    36,    51,    82,    83,
      84,    85,    52,    37,   110,   114,    53,    54,    56,    61,
      62,    63,    64,    68,    69,    70,    71,    72,    73,    74,
      75,    77,    76,    78,    79,    80,    81,    90,    91,   100,
     112,   119,   103,    67,    97,    98,   116,    18,    99,   115,
      96,     0,   111,     0,     0,   117,     0,     0,   118,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
      42
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-37))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       1,    11,    38,     3,     9,    10,    42,    12,     9,    10,
       0,    12,    13,    14,    15,    16,     8,     1,    23,     1,
      27,    27,    23,    26,    24,     9,    10,    28,    12,    13,
      14,    15,    16,     6,     1,    17,    18,    19,    20,    23,
      21,    22,     9,    10,    28,    12,    28,     1,     1,    26,
       6,    28,     6,     6,     6,    27,    23,    27,     3,     9,
      10,    28,    12,    13,    14,    15,    16,     6,    17,    18,
      19,    20,     6,    23,    28,    28,     6,     6,     6,     6,
       6,     6,     6,     3,     3,     3,     3,     3,     3,    27,
       3,     3,    29,     3,     3,     3,    29,     3,     3,     6,
       3,     3,     6,    47,    27,    27,     6,     8,    29,   104,
      86,    -1,   101,    -1,    -1,    29,    -1,    -1,    29,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    31,    32,    35,    36,     0,     8,    33,    34,
      39,    40,    44,    46,    27,    21,    22,    47,    34,    26,
      37,    38,    45,    41,    27,     6,    28,    38,    27,    27,
       9,    10,    12,    13,    14,    15,    16,    23,    48,    49,
      50,     3,    48,     9,    10,    12,    23,    42,    43,     6,
       6,     6,     6,     6,     6,    51,     6,     1,    28,    49,
      28,     6,     6,     6,     6,     1,    28,    43,     3,     3,
       3,     3,     3,     3,    27,     3,    29,     3,     3,     3,
       3,    29,    17,    18,    19,    20,    52,    53,    54,    59,
       3,     3,    55,    60,     1,    28,    53,    27,    27,    29,
       6,    56,    57,     6,    61,    62,     3,    24,    58,     1,
      28,    57,     3,     1,    28,    62,     6,    29,    29,     3
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 61 "configparse.y"
    {
     /*nothing*/
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 85 "configparse.y"
    {
	  if (seen_options)
	   {
		parser_error (0, "cannot redefine options");
		exit (1);
	   }
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 93 "configparse.y"
    {
	 seen_options=1;
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 104 "configparse.y"
    {
      if (!ValidateRequiredVesrion((yyvsp[(2) - (3)].cp)))
       {
        printf ("Failed to satisfy version requirement %s.\n", (yyvsp[(2) - (3)].cp));
        exit (1);
       }  
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 119 "configparse.y"
    {
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 122 "configparse.y"
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
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 170 "configparse.y"
    {
     mstrncpy(redir.redir_id, (yyvsp[(2) - (3)].cp), MAXREDIRID);
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 175 "configparse.y"
    {
	  if (arethesame((yyvsp[(2) - (3)].cp), "tcp"))
	   {
		redir.redir_type=REDIR_TCP;
	   }
	  else
	  if (arethesame((yyvsp[(2) - (3)].cp), "udp"))
	   {
		redir.redir_type=REDIR_UDP;
	   }
	  else
	   {
		parser_error (0, "*** Unknown redirection type '%s'", (yyvsp[(2) - (3)].cp));
		exit (1);
	   }  
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 192 "configparse.y"
    {
      mstrncpy(redir.dst_host, (yyvsp[(2) - (3)].cp), MAXHOSTLEN);	
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 196 "configparse.y"
    {
	  if (isdigits((yyvsp[(2) - (3)].cp)))  redir.dst_port=atoi((yyvsp[(2) - (3)].cp));
	  else  
	   {
		mstrncpy(dport, (yyvsp[(2) - (3)].cp), 20);
		redir.dst_port=0; 
	   }
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 207 "configparse.y"
    {
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 210 "configparse.y"
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
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 276 "configparse.y"
    {
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 279 "configparse.y"
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
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 353 "configparse.y"
    {
     mstrncpy(redir.redir_id, (yyvsp[(2) - (3)].cp), MAXHOSTLEN+10);
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 358 "configparse.y"
    {
	  if (arethesame((yyvsp[(2) - (3)].cp), "tcp"))
	   {
		redir.redir_type=REDIR_TCP;
	   }
	  else
	  if (arethesame((yyvsp[(2) - (3)].cp), "udp"))
	   {
		redir.redir_type=REDIR_UDP;
	   }
	  else
	   {
		parser_error (0, "*** Unknown redirection type '%s'", (yyvsp[(2) - (3)].cp));
		exit (1);
	   }  
	}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 375 "configparse.y"
    {
     mstrncpy(redir.dst_host, (yyvsp[(2) - (3)].cp), MAXHOSTLEN);	
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 379 "configparse.y"
    {
	  if (isdigits((yyvsp[(2) - (3)].cp)))  redir.dst_port=atoi((yyvsp[(2) - (3)].cp));
	  else  
	   {
		mstrncpy(dport, (yyvsp[(2) - (3)].cp), 20);
		redir.dst_port=0; 
	   }
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 388 "configparse.y"
    {
	  if (isdigits((yyvsp[(2) - (3)].cp)))  redir.listen_on_port=atoi((yyvsp[(2) - (3)].cp));
	  else
	   {
		mstrncpy(sport, (yyvsp[(2) - (3)].cp), 20);
		redir.listen_on_port=0;
	   }
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 397 "configparse.y"
    {
      if (!(isdigits((yyvsp[(2) - (3)].cp)))) 
	   {
        parser_error (0, "max_connections needs numeric");
        redir.max_connections=0;
       }	

	 redir.max_connections=atoi((yyvsp[(2) - (3)].cp));
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 407 "configparse.y"
    {
     mstrncpy(redir.local_host, (yyvsp[(2) - (3)].cp), MAXHOSTLEN);
     /*printf("local ip %s\n", $2); */
    }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 412 "configparse.y"
    {
      	 /**/
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 417 "configparse.y"
    {
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 420 "configparse.y"
    {
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 429 "configparse.y"
    {
         /*redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_ALLOW;*/
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 433 "configparse.y"
    {
         /*redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_DENY;*/
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 442 "configparse.y"
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
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 455 "configparse.y"
    {
        redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_DENY;
        }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 465 "configparse.y"
    {
          if (!(AddACLEntry(&redir.redir_access_list.access_list, (yyvsp[(1) - (2)].cp), "")))
           {
            printf ("invalid host definition '%s'\n", (yyvsp[(1) - (2)].cp));
           }
        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 472 "configparse.y"
    {
         if (!(AddACLEntry(&redir.redir_access_list.access_list, (yyvsp[(1) - (2)].cp), intraredir)))
           {
            printf ("invalid host definition '%s'\n", (yyvsp[(1) - (2)].cp));
           }
         intraredir[0]=0;
        }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 482 "configparse.y"
    {
         mstrncpy(intraredir, (yyvsp[(2) - (3)].cp), MAXREDIRID);
        }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 488 "configparse.y"
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
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 501 "configparse.y"
    {
        redir.redir_access_list.redir_access_mode=REDIR_ACCESS_MODE_ALLOW;
        }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 511 "configparse.y"
    {
          if (!(AddACLEntry (&redir.redir_access_list.access_list, (yyvsp[(1) - (2)].cp), "")))
           {
            printf ("invalid host definition '%s'\n", (yyvsp[(1) - (2)].cp));
           }
        }
    break;



/* Line 1806 of yacc.c  */
#line 2087 "configparse.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 519 "configparse.y"



