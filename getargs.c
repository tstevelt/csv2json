/*---------------------------------------------------------------------------
	Copyright © 2022 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"csv2json.h"

static void Usage ()
{
	printf ( "USAGE:  csv2json csvfile jsonfile [options]\n" );
	printf ( "  output to stdout by setting jsonfile to stdout or -\n" );
	printf ( "options:\n" );
	printf ( "  -header  first line is column headers\n" );
	printf ( "  -style {terse|dict|flat|bloated|keyed}\n" );
	printf ( "  -d       debug\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	int		xa;

	if ( argc < 3 )
	{
		Usage ();
	}

	csvFile = argv[1];
	jsonFile = argv[2];

	HasHeader = 0;
	Style = STYLE_TERSE;
	Debug = 0;

	for ( xa = 3; xa < argc; xa++ )
	{
		if ( strcmp ( argv[xa], "-header" ) == 0 )
		{
			HasHeader = 1;
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-style" ) == 0 )
		{
			xa++;
			if ( strcmp ( argv[xa], "terse" ) == 0 )
			{
				Style = STYLE_TERSE;
			}
			else if ( strcmp ( argv[xa], "dict" ) == 0 )
			{
				Style = STYLE_DICT;
			}
			else if ( strcmp ( argv[xa], "flat" ) == 0 )
			{
				Style = STYLE_FLAT;
			}
			else if ( strcmp ( argv[xa], "bloated" ) == 0 )
			{
				Style = STYLE_BLOATED;
			}
			else if ( strcmp ( argv[xa], "keyed" ) == 0 )
			{
				Style = STYLE_KEYED;
			}
			else
			{
				Usage ();
			}
		}
		else if ( strcmp ( argv[xa], "-d" ) == 0 )
		{
			Debug = 1;
		}
		else
		{
			Usage ();
		}
	}

	switch ( Style )
	{
		case STYLE_DICT:
		case STYLE_BLOATED:
		case STYLE_KEYED:
			if ( HasHeader == 0 )
			{
				printf ( "Column header row is required for this style\n" );
				exit ( 1 );
			}
			break;
	}
}
