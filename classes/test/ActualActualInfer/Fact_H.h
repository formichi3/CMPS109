#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#ifndef Fact_H
#define Fact_H

class fact{
public:
       // constructors
       fact();
       fact(string p_name, vector < string > p_paramaters);
       ~fact();
       string name;
       vector < string > paramaters;
       friend bool operator==(const fact &left, const fact &right);

};

#endif
