#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#ifndef Fact_H
#define Fact_H

class fact{

public:
       
       fact();
       fact(string p_name, vector < string > p_paramaters);
       ~fact();
       string name;
       vector < string > paramaters;
};


#endif
