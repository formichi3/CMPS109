#include <iostream>
#include <utility>

using namespace std;

#ifndef Rule_H
#define Rule_H

class rule{

public:
       rule();
       rule(string p_name);
       ~rule();
       void print2();
       string name;
       bool logOperator; //0=OR, 1=AND
       vector < pair < string, vector < char > > > predicates;
};


#endif
