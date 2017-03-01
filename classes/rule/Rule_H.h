#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#ifndef Rule_H
#define Rule_H

class rule{

public:

       //constructors & destructors
       rule();
       rule(string p_name, vector < string > p_args, int p_Operator, vector < vector < string > > p_rules, vector < vector < string > > p_facts );
       ~rule();

       string name; //name of rule
       int logOperator; //0=OR, 1=AND
       vector < string > args; //args to be returned when inferred
       vector < vector < string > > rules;
       vector < vector < string > > facts;

       void print();
};


#endif
