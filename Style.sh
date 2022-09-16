#!/bin/sh

Prompt ()
{
	WAIT=$1
	shift
	echo "==== $* ===="
	if [ $WAIT = 1 ]
	then
		echo "Press ENTER to continue"
		read x
	fi
}

head -5 report.csv

Prompt 1 Convert standard CSV to JSON, using -style terse \(default\)
csv2json report.csv terse.json -header 
JsonTree terse.json
Prompt 1

Prompt 1 Convert standard CSV to JSON, using -style dict
csv2json report.csv dict.json -header -style dict
JsonTree dict.json
Prompt 1

Prompt 1 Convert standard CSV to JSON, using -style flat
csv2json report.csv flat.json -header -style flat
JsonTree flat.json
Prompt 1

Prompt 1 Convert standard CSV to JSON, using -style bloated
csv2json report.csv bloated.json -header -style bloated
JsonTree bloated.json
Prompt 1

Prompt 1 Convert standard CSV to JSON, using -style keyed
csv2json report.csv keyed.json -header -style keyed
JsonTree keyed.json


echo "Done"

