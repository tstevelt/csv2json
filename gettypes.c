/*---------------------------------------------------------------------------
	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"csv2json.h"

void gettypes ( char *Tokens[], int TokenCount )
{
	int		xt, xi, xl;

	for ( xt = 0; xt < TokenCount; xt++ )
	{
		if (( strcmp ( Tokens[xt], "true"  ) == 0 ) ||
			( strcmp ( Tokens[xt], "false" ) == 0 ))
		{
			dataTypes[xt] = DT_BOOLEAN;
			continue;
		}

		xl = strlen ( Tokens[xt] );

		dataTypes[xt] = 0;
		for ( xi = 0; xi < xl; xi++ )
		{
			if ( isalpha(Tokens[xt][xi]) )
			{
				dataTypes[xt] = DT_STRING;
				break;
			}
			else if ( isdigit(Tokens[xt][xi]) && dataTypes[xt] != DT_FLOAT )
			{
				dataTypes[xt] = DT_INT;
			}
			else if ( Tokens[xt][xi] == '.' && dataTypes[xt] == DT_INT )
			{
				dataTypes[xt] = DT_FLOAT;
			}
		}
	}

	if ( Debug )
	{
		for ( xt = 0; xt < TokenCount; xt++ )
		{
			printf ( "%3d: %3d\n", xt, dataTypes[xt] );
		}
	}

}
