#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "easyfsm.h"
#include "generator.h"
#include <stdlib.h>
#include <stdarg.h>
#include <map>
#include <string>


using namespace std;


vector< ENTRY > ENTRIES;
map< string , vector< ENTRY > > FSM;

ENTRY::ENTRY()
{}

ENTRY::~ENTRY()
{}

ENTRY::ENTRY( string s , string e , string c )
{
	start = s;
	end = e;
	condition = c;
}

ENTRY::ENTRY( char * s , char * e , char * c )
{
	start = s;
	end = e;
	condition = c;
}

void NewEntry( char * start , char * end , char * cond )
{
	ENTRIES.push_back( ENTRY( start , end , cond ) );	
}

int yyerror( char * s , ... )
{
	va_list ap;
	va_start( ap , s );

	fprintf( stderr , "%d: error" , yylineno );
	vfprintf( stderr , s , ap );
	fprintf( stderr , "\n" );
}
int main( int argc , char ** argv )
{
	//freopen( "test" , "r" , stdin );
	
	char * help_info = "Usage: easyfsm [flag] [source file] [object file]\n\t-j Generate Java code\n\t -d Generate dot code\n";

	if( argc == 4 && strcmp( argv[ 1 ] , "-j" ) == 0 )
	{
		if( ChangeInput( argv[ 2 ] ) == false )
		{
			cout << "Cannot open file.\n" << endl;
			return 1;
		}
		
		ENTRIES.clear();

		FSM.clear();

		yyparse();

		ofstream ofile( argv[ 3 ] );
		
		if( ofile.fail() )
		{
			cout << "Cannot open file.\n" << endl;
		
			return 1;
		}

		ofile << JavaGenerator::Instance()->GenCode( FSM ) << endl;
		
		ofile.close();

		return 0;
	}
	else if( argc == 4 && strcmp( argv[ 1 ] , "-d" ) == 0 )
	{
		if( ChangeInput( argv[ 2 ] ) == false )
		{
			cout << "Cannot open file.\n" << endl;
			return 1;
		}
		
		ENTRIES.clear();

		FSM.clear();

		yyparse();

		ofstream ofile( argv[ 3 ] );
		
		if( ofile.fail() )
		{
			cout << "Cannot open file.\n" << endl;
			return 1;
		}

		ofile << DotGenerator::Instance()->GenCode( FSM ) << endl;
		
		ofile.close();

		return 0;
		
	}
	else
	{
		cout << help_info << endl;
		
		return 0;
	}


	cout << argv[1] << endl;

	ChangeInput( "./test" );
	


	

	return 0;
}


