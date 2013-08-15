#ifndef GENERATOR_H
#define GENERATOR_H

#include "easyfsm.h"
#include <string>
#include <map>

using namespace std;

class Generator
{
public:
	Generator();
	virtual ~Generator();
	virtual string GenCode( map< string , vector< ENTRY > > & ) = 0;
	virtual string GenCode( string , vector< ENTRY > & ) = 0;
};


class JavaGenerator : public Generator
{
private:
	JavaGenerator();
	virtual ~JavaGenerator();
	static JavaGenerator * instance;
public:
	static JavaGenerator * Instance();
	virtual string GenCode( map< string , vector< ENTRY > > & );
	virtual string GenCode( string , vector< ENTRY > & );
};

class DotGenerator : public Generator
{
private:
	DotGenerator();
	virtual ~DotGenerator();
	static DotGenerator * instance;
public:
	static DotGenerator * Instance();
	virtual string GenCode( map< string , vector< ENTRY > > & );
	virtual string GenCode( string , vector< ENTRY > & );

};
#endif
