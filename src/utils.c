/*
** utils.c Copyright (c) 1999,00 Ayman Akt
**
*/

#include <main.h>
#include <stdio.h>
#include <sys/stat.h>


 int OpenFile (File *file)

 {
  struct stat st;

    if (!(file->fp=fopen(file->filename, "r")))
     {
      file->stat=errno;

      return -1;
     }

    if ((stat(file->filename, &st))<0)
     {
      file->stat=errno;

      return -2;
     }

    if (file->size=st.st_size, file->size==0)
     {
      file->stat=errno;

      return -3;
     }

   {
      if (!(file->conts=malloc(file->size+1)))
       {
        return -4;
       }

      if ((read(fileno(file->fp), file->conts, file->size))<0)
       {
        file->stat=errno;

        return -5;
       }
   }

   return 1;

 }  /**/


 int SplitIntoTokens (TokensHdr *tokshdr)

 {
  register char *p,
                *q,
                *r,
                *aux;
  int i=-1;

    if (!tokshdr)  return -1;

   aux=q=strdup(tokshdr->origstr);

   tokshdr->toks=malloc(tokshdr->ntoks*sizeof(Token));

    while ((*q)&&(((++i)+1)<=tokshdr->ntoks))
     {
       while ((*q)&&(isspace(*q)))  q++;

      p=strchr (q, tokshdr->div);

       if (p==(char *)NULL)
        {
          for (r=q+strlen(q)-1; ((isspace(*r))&&(r>=q)); r--)
           ;

         *(r+1)=0;

         {
          tokshdr->toks[i]=malloc(sizeof(Token));
          ((Token *)tokshdr->toks[i])->str=strdup(q);
         }

         *q=0;
        }
       else
        {
         *p=0;
          for (r=q+strlen(q)-1; ((isspace(*r))&&(r>=q)); r--)
           ;

         *(r+1)=0;

         {
          tokshdr->toks[i]=malloc(sizeof(Token));
          ((Token *)tokshdr->toks[i])->str=strdup(q);
         }

         q=p+1;
        }
     }


    /* adjust to reflect the actual tokens number */
    if (i+1<tokshdr->ntoks)  tokshdr->ntoks=i+1;

    if (*q)  tokshdr->leftover=strdup(q);
    else  tokshdr->leftover=NULL;

   free (aux);

   return (i+1);

 }  /**/


 /*
 ** Frontend function to SplitIntoTokens()
 */
 int SplitTokens (TokensHdr *tokshdr, char *origstr, int ntoks, char div)

 {
   tokshdr->ntoks=ntoks;
   tokshdr->div=div;
   tokshdr->origstr=origstr;

   return (SplitIntoTokens(tokshdr));

 }  /**/


 int CleanUpTokens (TokensHdr *tokshdr)

 {
  register int n;
  register Token *tok;

    if (!(tokshdr))  return -1;
    if ((tokshdr->ntoks=0))  return -1;

    for (n=0; n<tokshdr->ntoks; n++)
     {
      tok=tokshdr->toks[n];

       if (tok->str)  free (tok->str);
      free (tok);
     }

    if (tokshdr->leftover)  free (tokshdr->leftover);

   free (tokshdr->toks);

   return 1;

 }  /**/


 /* see the definition of macro splitw */
 char *tokenize (char **str, const char c)

 {
  register char *s,
                *p;

    if ((!str)||(!*str))  return *str="";

   s=*str;

    while ((*s==' '))  s++;

    if ((p=strchr(s, c)))
     {
      *str=(*p++=0, p);

      return (char *)s;
     }

   *str=0;

   return (char *)s;

 }  /**/


 void wipespaces (char *s)

 {
  #define whitespace(c) (((c)==32)||((c)==9)||((c)==13)||((c)==10))
  register char *p;

    for (p=s+strlen(s)-1; ((whitespace(*p))&&(p>=s)); p--)  ;

   if (p!=s+strlen(s)-1)  *(p+1)=0;

   for (p=s; ((whitespace(*p)) && (*p)); p++)
    ; 

   if (p!=s)  strcpy (s, p);

 }  /**/

