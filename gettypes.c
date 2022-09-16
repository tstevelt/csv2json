
#include	"csv2json.h"

void gettypes ( char *Tokens[], int TokenCount )
{
	int		xt, xi, xl;

/*---------------------------------------------------------------------------
TICKER,NAME,FOREIGN
BG,Bunge Limited,false
CRH,CRH PLC American Depositary Shares,true
CVX,Chevron Corporation,false
EMN,Eastman Chemical Company,false
GLW,Corning Incorporated,false
HIG,Hartford Financial Services Group Inc. (The),false
HPE,Hewlett Packard Enterprise Company,false
HUN,Huntsman Corporation,false
IP,International Paper Company,false
LXFR,Luxfer Holdings PLC,false
MO,Altria Group Inc.,false
NOK,Nokia Corporation Sponsored American Depositary Shares,true
OMC,Omnicom Group Inc.,false
STX,Seagate Technology PLC,false
THG,Hanover Insurance Group Inc,false
XOM,Exxon Mobil Corporation,false
---------------------------------------------------------------------------*/
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
