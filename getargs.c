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
	printf ( "options:\n" );
	printf ( "  -header  first line is column headers\n" );
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
	Debug = 0;

	for ( xa = 3; xa < argc; xa++ )
	{
		if ( strcmp ( argv[xa], "-header" ) == 0 )
		{
			HasHeader = 1;
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
}
