/*---------------------------------------------------------------------------
	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

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
