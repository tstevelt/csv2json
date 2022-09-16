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
Prompt 1 Convert standard CSV to JSON
csv2json report.csv report.json -header 
JsonTree report.json
Prompt 1

head -5 quoted.csv
Prompt 1 Convert quoted string CSV to JSON
csv2json quoted.csv quoted.json -header 
JsonTree quoted.json
Prompt 1

Prompt 1 Make sure both JSON files are the same
diff report.json quoted.json
if [ $? = 0 ]
then
	echo "both files are the same"
else
	echo "oh oh"
fi
Prompt 1

head -5 NoHeader.csv
Prompt 1 Convert CSV with no column headers to JSON
csv2json NoHeader.csv NoHeader.json
JsonTree NoHeader.json
Prompt 1

head -5 boolean.csv
Prompt 1 Convert CSV file with BOOLEAN column to JSON
csv2json boolean.csv boolean.json -header
JsonTree boolean.json

echo "Done"

