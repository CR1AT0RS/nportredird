/*
** utils.h Copyright (c) 1999 Ayman Akt
**
** See the COPYING file for terms of use and conditions.
**
MODULEID("$Id: utils.h,v 1.1 1999/07/26 01:46:59 ayman Exp $")
**
*/


 typedef struct LogFile {
          FILE *file;
          char *fname;
         } LogFile;

 struct OpenFile {
  const char *filename;
  char *conts; /* contents of the file */
  FILE *fp;
  size_t size;
  unsigned stat; /* errno information */
 };
 typedef struct OpenFile File;


 typedef struct Token {
         char *str;
        } Token;

typedef struct TokensHdr {
         char div;       /* delimiter char */
         char *origstr,  /* string to be tokenized */
              *leftover;
         unsigned ntoks; /* number of toks required */
         Token **toks;
        } TokensHdr;

 #define TOK(x, y) ((y)>(x)->ntoks?"":((Token *)(x)->toks[(y-1)])->str)

 #define splitw(x) tokenize((x), ' ')

 /* needs GCC */
 #define isdigits(x) ({ \
                      int numbered=1; \
                      register int n=strlen(x)-1; \
                                         \
                        while (n>=0) \
                         {  \
                           if ((x[n]<'0')||(x[n]>'9')) \
                            { \
                             numbered=0; \
                             break; \
                            } \
                          n--; \
                         } \
                                \
                       (numbered?1:0); \
                     })

 int OpenFile (File *);

 int SplitTokens (TokensHdr *, char *, int, char);
 int SplitIntoTokens (TokensHdr *);
 int CleanUpTokens (TokensHdr *);
 char *tokenize (char **, const char);
 void wipespaces (char *);

