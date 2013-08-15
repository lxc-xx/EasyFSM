#ifndef EASYFSM_H
#define EASYFSM_H
#include <vector>
#include <string>
#include <map>

#define REP( i , j , k ) for( int i = 0 ; i < k ; ++i )

#ifdef DEBUG
#define D if( 1 )
#else
#define D if( 0 )
#endif

#define DEBUG

#define DEB( var... ) fprintf( stderr , var )

using namespace std;

extern "C" {
extern int yylex();
extern int yyerror( char *s, ... );
extern int yylineno;
extern int yyparse();
extern bool ChangeInput( char * );
}
struct ENTRY
{
	string start;
	string end;
	string condition;

	ENTRY();
	ENTRY( string, string, string );
	ENTRY( char *, char *, char * );
	~ENTRY();
};


extern vector <ENTRY> ENTRIES;
extern map < string , vector< ENTRY > > FSM;


void NewEntry( char * start , char * end , char * cond );




#endif
