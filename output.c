/*---------------------------------------------------------------------------
	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"csv2json.h"

void output ( FILE *ofp, const int outLineno )
{
	if ( outLineno )
	{
		fprintf ( ofp, "," );
	}

	switch ( Style )
	{
		case STYLE_TERSE:
		case STYLE_DICT:
		case STYLE_FLAT:
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
			break;

		case STYLE_BLOATED:
			fprintf ( ofp, "{" );
			for ( xt = 0; xt < tokcnt; xt++ )
			{
				if ( xt )
				{
					fprintf ( ofp, "," );
				}
				fprintf ( ofp, "\"%s\":", columns[xt] );
				if ( dataTypes[xt] == DT_STRING )
				{
					fprintf ( ofp, "\"%s\"", tokens[xt] );
				}
				else
				{
					fprintf ( ofp, "%s", tokens[xt] );
				}
			}
			fprintf ( ofp, "}" );
			break;

		case STYLE_KEYED:
			fprintf ( ofp, "{\"%s\":{", tokens[0] );
			for ( xt = 1; xt < tokcnt; xt++ )
			{
				if ( xt > 1 )
				{
					fprintf ( ofp, "," );
				}
				fprintf ( ofp, "\"%s\":", columns[xt] );
				if ( dataTypes[xt] == DT_STRING )
				{
					fprintf ( ofp, "\"%s\"", tokens[xt] );
				}
				else
				{
					fprintf ( ofp, "%s", tokens[xt] );
				}
			}
			fprintf ( ofp, "}}" );
			break;
	}
}
