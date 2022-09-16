
#include	"csv2json.h"


int gettoks ( char *Buffer, char *Tokens[], int MaxTokens )
{
	int		TokenCount = 0;
	char	*Delim = ",\r\n";
	char	*cp;

	for ( cp = strtok ( Buffer, Delim ); 
		  cp;
		  cp = strtok ( NULL,   Delim ) )
	{
		Tokens[TokenCount] = cp;
		TokenCount++;
	}

	return ( TokenCount );
}
