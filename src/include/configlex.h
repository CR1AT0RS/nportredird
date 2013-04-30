#ifndef CONFIGLEX_H
#define CONFIGLEEX_H

#define LEX_MAX_IDENT_SIZE 1024

#define SYM_CLASS	0x01
#define SYM_CATEGORY	0x02
#define SYM_LOGGING	0x04
#define SYM_SYSLOG	0x08

int	parser_warning(int, const char *, ...);
int	parser_error(int, const char *, ...);
void	yyerror(const char *);
void	lexer_begin_file(const char *, FILE *);
void	lexer_end_file(void);
int	yylex(void);
void	lexer_initialize(void);
void	lexer_setup(void);
void	lexer_shutdown(void);

#endif 

