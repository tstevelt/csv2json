/*---------------------------------------------------------------------------
	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"csv2json.h"

static char *ascii_type ( int Type )
{
	switch ( Type )
	{
		case DT_STRING:
			return ( "string" );
		case DT_INT:
			return ( "int" );
		case DT_FLOAT:
			return ( "double" );
		case DT_BOOLEAN:
			return ( "boolean" );
	}
	return ( "unknown" );
}

void headers ( FILE *ofp )
{
	int		xt;

	switch ( Style )
	{
		case STYLE_TERSE:
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
				fprintf ( ofp, "\"column%d\":\"%s\"", xt+1, columns[xt] );
			}
			fprintf ( ofp, "}," );
			break;

		case STYLE_DICT:
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
				fprintf ( ofp, "\"%s\":\"%s\"", columns[xt], ascii_type(dataTypes[xt]) );
			}
			fprintf ( ofp, "}," );
			break;

		case STYLE_FLAT:
			fprintf ( ofp, "[" );
			for ( xt = 0; xt < tokcnt; xt++ )
			{
				if ( xt )
				{
					fprintf ( ofp, "," );
				}
				fprintf ( ofp, "\"%s\"", columns[xt] );
			}
			fprintf ( ofp, "]," );
			break;

		case STYLE_BLOATED:
		case STYLE_KEYED:
			break;
	}
}
