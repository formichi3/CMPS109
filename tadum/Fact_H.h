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
	 // default constructor
       fact(string p_name, vector < string > p_paramaters);
	 // fact constructor that takes name and vector of it's arguments

       // destructor
       ~fact();
       
       // variables
       string name;
	 // holds the fact's name
       vector < string > paramaters;
	 // holds the fact's arguments
};

#endif
