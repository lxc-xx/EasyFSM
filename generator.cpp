#include "easyfsm.h"
#include "generator.h"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#define LINE( str ) result += str;result+="\n"
#define DEBUG

using namespace std;



Generator::Generator()
{}

Generator::~Generator()
{}


JavaGenerator::JavaGenerator()
{}

JavaGenerator::~JavaGenerator()
{}



struct Transition
{
	string target;
	string condition;
	
	Transition( string t = "" , string c = "" ) : target( t ) , condition( c )
	{}

	~Transition()
	{}

};





struct State
{
	string name;

	vector< Transition > trans;
	
	State( string n = "" ) : name( n )
	{}
	~State()
	{}

	string GenCode()
	{
		set< string > conditions;

		REP( i , 0 , trans.size() )
		{
			conditions.insert( trans[ i ].condition );
		}


		string result;
		result += "\tprivate State STATE_" + name  + " = new State()\n";
		result += "\t{\n\n";
		
		for( set< string >:: iterator it = conditions.begin() ; it != conditions.end() ; ++it )
		{
			result += "\t\tboolean CONDITION_";
			result += *it;
			result += "()\n";
			result += "\t\t{\n";
			result += "\t\t\t//Add your code here to define the condition\n";
			result += "\t\t\treturn false;\n";
			result += "\t\t}\n\n";
		}

		result += "\t\tvoid work()\n";
		result += "\t\t{\n";
		result += "\t\t\t//Add your code here to define the job\n";
		result += "\t\t}\n\n";

		result += "\t\tState nextState()\n";
		result += "\t\t{\n";
		
		REP( i , 0 , trans.size() )
		{
			result += "\t\t\tif( CONDITION_";
		       	result += trans[ i ].condition;
			result += "() )\n";
			result += "\t\t\t{\n";
			result += "\t\t\t\treturn STATE_";
			result += trans[ i ].target;
			result += ";\n";
			result += "\t\t\t}\n";
		}

		result += "\t\t\treturn this;\n";

		result += "\t\t}\n\n";
		

		

		result += "\t};\n\n";

		return result;

	}
};


set< string > ALL_STATES_NAME;

map< string , int > STATES_TABLE;


vector< State > ALL_STATES;



string JavaGenerator::GenCode( map< string , vector< ENTRY > > & fsm ) 
{
	string result;
	result += "class State\n { \n \tvoid work()\n\t{}\n\n\tState nextState()\n\t{\n\t\treturn this;\n\t}\n}\n\n";
	
	result += "class StateMachine\n";
	result += "{\n";
	result += "\tpublic StateMachine()\n";
	result += "\t{}\n";
	result += "\n";
	result += "\tvoid work()\n";
	result += "\t{}\n";
	result += "\tvoid update()\n";
	result += "\t{}\n";
	result += "}\n\n";

	for( map< string , vector< ENTRY > >::iterator it = fsm.begin() ; it != fsm.end() ; ++it )
	{
		result += JavaGenerator::GenCode( it->first , it->second );

		result += "\n";
	}
	
	
	result += "class StateMachineFactory\n";
	result += "{\n";
	result += "\tpublic static StateMachine getStateMachine( String name )\n";
	result += "\t{\n";
	result += "\t\tswitch( name )\n";
	result += "\t\t{\n";

	
	for( map< string , vector< ENTRY > >::iterator it = fsm.begin() ; it != fsm.end() ; ++it )
	{
		
		result += "\t\t\tcase \"";
		result += it->first;
		result += "\":\n";
		result += "\t\t\t\treturn new StateMachine_";
		result += it->first;
		result += "();\n";
	}

	result += "\t\t\tdefault:\n";
	result += "\t\t\t\treturn new StateMachine();\n";
	result += "\t\t}\n";
	result += "\t}\n";
	result += "}\n";


	return result;
}


string JavaGenerator::GenCode( string name , vector< ENTRY > & entries ) 
{
	string result;



	ALL_STATES.clear();
	ALL_STATES_NAME.clear();
	STATES_TABLE.clear();


	REP( i , 0 , entries.size() )
	{
		
		if( STATES_TABLE.find( entries[ i ].start ) == STATES_TABLE.end() )
		{
			ALL_STATES.push_back( State( entries[ i ].start ) );
			STATES_TABLE[ entries[ i ].start ] = ALL_STATES.size() - 1;
		}
		if( STATES_TABLE.find( entries[ i ].end ) == STATES_TABLE.end() )
		{
			ALL_STATES.push_back( State( entries[ i ].end ) );
			STATES_TABLE[ entries[ i ].end ] = ALL_STATES.size() - 1;
		}

		ALL_STATES[ STATES_TABLE[ entries[ i ].start ] ].trans.push_back( Transition( entries[ i ].end , entries[ i ].condition ) );
	
	}
	
	result += "class StateMachine_";
	result += name;
	result += " extends StateMachine\n{\n";
	result += "\tpublic State current_state;\n\n";
	result += "\tvoid work()\n";
	result += "\t{\n";
	result += "\t\tthis.current_state.work();\n";
	result += "\t}\n\n";
	
	result += "\tvoid update()\n";
	result += "\t{\n";
	result += "\t\tcurrent_state = current_state.nextState();\n";
	result += "\t}\n\n";
	
	REP( i , 0 , ALL_STATES.size() )
	{
		result += ALL_STATES[ i ].GenCode();
	}
	 

	result += "}\n";
  
	
	return result;

}	


JavaGenerator * JavaGenerator::Instance()
{
	if( instance == NULL )
	{
		instance = new JavaGenerator();
	}

	return instance;
}


JavaGenerator * JavaGenerator::instance = NULL;


DotGenerator::DotGenerator()
{}

DotGenerator::~DotGenerator()
{}

DotGenerator * DotGenerator::instance = NULL;

DotGenerator * DotGenerator::Instance()
{
	if( instance == NULL )
	{
		instance = new DotGenerator();
	}

	return instance;
}

string DotGenerator::GenCode( string name , vector< ENTRY > & entries )
{
	string result;
	result.clear();

	static int count = 0;
	
	char str_count[ 50 ];

	sprintf( str_count , "%d" , count++ );

	result += "\tsubgraph ";
	result += "cluster";
	result += str_count;
	result += "\n";

	result += "\t{\n\n";
	

	
	

	REP( i , 0 , entries.size() )
	{
		result += "\t\t";
		result += name;
	       	result += "_";
	       	result += entries[ i ].start;
	       	result += " -> ";
	       	result += name;
	       	result += "_";
	       	result += entries[ i ].end;
	       	result += "[ label = \"";
	       	result += entries[ i ].condition;
	       	result += "\" ];\n"; 
	}

	result += "\n";
	
	result += "\t\tlabel = \"" + name + "\";\n\n";

	result += "\t}\n";

	return result;


}


string DotGenerator::GenCode( map< string , vector< ENTRY > > & fsm )
{
	string result;
	result.clear();

	result += "digraph StateMachine\n";
	result += "{\n";




	
	for( map< string , vector< ENTRY > >::iterator it = fsm.begin() ; it != fsm.end() ; ++it )
	{
		
		result += DotGenerator::GenCode( it->first , it->second );
		
		result += "\n";
	}


	result += "}\n";

	return result;	


}

