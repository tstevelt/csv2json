/*----------------------------------------------------------------------------
	Program : csv2json.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Sep 2022
	Synopsis: Convert CSV to JSON
	Return  : 

	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/

#define		MAIN
#include	"csv2json.h"

int main ( int argc, char *argv[] )
{
	FILE	*ifp, *ofp;
	char	xbuffer[MAXBUFFER];
	int		xt, inLineno, outLineno, xl;
	char	*cp, *next;

	getargs ( argc, argv );

	if (( ifp = fopen ( csvFile, "r" )) == NULL )
	{
		fprintf ( stderr, "Cannot open %s for input\n", csvFile );
		exit ( 1 );
	}

	if (( ofp = fopen ( jsonFile, "w" )) == NULL )
	{
		fprintf ( stderr, "Cannot open %s for output\n", jsonFile );
		exit ( 1 );
	}
	fprintf ( ofp, "[" );

	inLineno = 0;
	outLineno = 0;
	while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
	{
		inLineno++;

		/*----------------------------------------------------------
			remove trailing NL and CR
		----------------------------------------------------------*/
		for ( cp = xbuffer; cp; cp++ )
		{
			if ( *cp == '\r' || *cp == '\n' )
			{
				*cp = '\0';
				break;
			}
		}

		/*----------------------------------------------------------
			double quotes not allowed in input file.
		----------------------------------------------------------*/
		while (( cp = strchr ( xbuffer, '"' )) != NULL )
		{
			xl = strlen ( cp );
			next = cp + 1;
			memmove ( cp, next, xl );
		}

		tokcnt = gettoks ( xbuffer, tokens, MAXTOKS );
		if ( tokcnt == 0 )
		{
			continue;
		}

		if ( HasHeader && inLineno == 1 )
		{
			for ( xt = 0; xt < tokcnt; xt++ )
			{
				if ( xt == 0 )
				{
					fprintf ( ofp, "{" );
				}
				else
				{
					fprintf ( ofp, "," );
				}
				fprintf ( ofp, "\"column%d\":\"%s\"", xt+1, tokens[xt] );
			}
			fprintf ( ofp, "}," );

			continue;
		}

		if ( Debug )
		{
			for ( xt = 0; xt < tokcnt; xt++ )
			{
				printf ( "%3d: %3d %s\n", inLineno, xt, tokens[xt] );
			}
		}

		outLineno++;
		if ( outLineno == 1 )
		{
			gettypes ( tokens, tokcnt );
		}
		else if ( outLineno > 1 )
		{
			fprintf ( ofp, "," );
		}
		fprintf ( ofp, "[" );
		for ( xt = 0; xt < tokcnt; xt++ )
		{
			if ( xt )
			{
				fprintf ( ofp, "," );
			}
			if ( dataTypes[xt] == DT_STRING )
			{
				fprintf ( ofp, "\"%s\"", tokens[xt] );
			}
			else
			{
				fprintf ( ofp, "%s", tokens[xt] );
			}
		}
		fprintf ( ofp, "]" );
	}

	fprintf ( ofp, "]" );

	fclose ( ifp );
	fclose ( ofp );

	return ( 0 );
}
