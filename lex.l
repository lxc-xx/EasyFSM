%option noyywrap nodefault yylineno

%{
#include <stdio.h>
#include "easyfsm.h"
#include "parser.h"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;


%}


%%


[a-zA-z]+ {
yylval.str = ( char * )malloc( ( sizeof( char ) ) * ( strlen( yytext ) + 1 ) );
strcpy( yylval.str , yytext ); 
//cout << yytext << endl;

return NAME; 
}

":" { return COLON; }  

"->" { return ARROW; }

"{" { return LBRACE; }

"}" { return RBRACE; }

\n[ \t\n]* { return EOL; }

[ \t]  { /*ignored*/ }

. { fprintf( stderr , "Bad Syntax" ); }


%%

bool ChangeInput( char * file_path )
{
	FILE * fp;

	fp = fopen( file_path , "r" );

	
	if( fp == NULL )
	{
		return false;
	}
	else
	{
		yyin = fp;
	}

	return true;

}

