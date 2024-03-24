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
	char	xheader[MAXBUFFER];
	char	xbuffer[MAXBUFFER];
	int		xt, inLineno, outLineno, xi, xo, xl;
	char	*cp, *next;

	getargs ( argc, argv );

	if (( ifp = fopen ( csvFile, "r" )) == NULL )
	{
		fprintf ( stderr, "Cannot open %s for input\n", csvFile );
		exit ( 1 );
	}

	if (( strcmp ( jsonFile, "stdout" ) == 0 ) ||
		( strcmp ( jsonFile, "-" )      == 0 ))
	{
		ofp = stdout;
	}
	else
	{
		if (( ofp = fopen ( jsonFile, "w" )) == NULL )
		{
			fprintf ( stderr, "Cannot open %s for output\n", jsonFile );
			exit ( 1 );
		}
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

		/*----------------------------------------------------------
			if first line and has headers, get columns
			else get tokens.
		----------------------------------------------------------*/
		if ( HasHeader && inLineno == 1 )
		{
			if ( Style == STYLE_TERSE )
			{
				sprintf ( xheader, "%s", xbuffer );
			}
			else
			{
				xl = strlen ( xbuffer );
				for ( xi = 0, xo = 0; xi < xl; xi++ )
				{
					if ( xbuffer[xi] == ',' || isalpha(xbuffer[xi]) || isdigit(xbuffer[xi]) )
					{
						xheader[xo++] = xbuffer[xi];
					}
				}
				xheader[xo] = '\0';
			}

			tokcnt = gettoks ( xheader, columns, MAXTOKS );

			if ( Debug )
			{
				for ( xt = 0; xt < tokcnt; xt++ )
				{
					printf ( "%3d: %3d %s\n", inLineno, xt, columns[xt] );
				}
			}
			continue;
		}
		else
		{
			tokcnt = gettoks ( xbuffer, tokens, MAXTOKS );

			if ( outLineno == 0 )
			{
				gettypes ( tokens, tokcnt );
			}

			if ( Debug )
			{
				for ( xt = 0; xt < tokcnt; xt++ )
				{
					printf ( "%3d: %3d %s\n", inLineno, xt, tokens[xt] );
				}
			}
		}

		if ( HasHeader && outLineno == 0 )
		{
			headers ( ofp );
		}

		output ( ofp, outLineno );
		outLineno++;
	}

	fprintf ( ofp, "]" );

	fclose ( ifp );
	fclose ( ofp );

	return ( 0 );
}
