
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<ctype.h>

#ifdef MAIN
#define		TYPE	/* */
#else
#define		TYPE	extern
#endif

TYPE	char	*csvFile;
TYPE	char	*jsonFile;
TYPE	int		HasHeader;
TYPE	int		Debug;

#define		STYLE_TERSE		1
#define		STYLE_DICT		2
#define		STYLE_FLAT		3
#define		STYLE_BLOATED	4
#define		STYLE_KEYED		5
TYPE	int		Style;

#define		DT_STRING	1
#define		DT_INT		2
#define		DT_FLOAT	3
#define		DT_BOOLEAN	4

#define		MAXBUFFER	1024
#define		MAXTOKS		256
TYPE	char	*tokens[MAXTOKS];
TYPE	char	*columns[MAXTOKS];
TYPE	int		tokcnt, xt;
TYPE	int		dataTypes[MAXTOKS];

/* csv2json.c */
int main ( int argc , char *argv []);

/* getargs.c */
void getargs ( int argc , char *argv []);

/* gettoks.c */
int gettoks ( char *Buffer , char *Tokens[] , int MaxTokens );

/* gettypes.c */
void gettypes ( char *Tokens [], int TokenCount );

/* headers.c */
void headers ( FILE *ofp );

/* output.c */
void output ( FILE *ofp , const int outLineno );
