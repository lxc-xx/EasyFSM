%{
#include "easyfsm.h"
#include <string.h>
#include <vector>
#include <map>


using namespace std;

%}

%union{
	char* str;
}

%token <str> NAME ARROW COLON EOL LBRACE RBRACE

%type <str> entry fsm

%expect 2

%%

fsm: fsm fsm
| NAME EOL LBRACE EOL entry RBRACE EOL { string name = $1; FSM[ name ] = ENTRIES ; ENTRIES.clear(); }


entry: entry entry
| NAME ARROW NAME COLON NAME EOL { ENTRIES.push_back( ENTRY( $1 , $3 , $5 ) ); }
;

%%
