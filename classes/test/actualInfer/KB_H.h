#include <iostream>
#include <unordered_map>
#include <vector>
#include "Fact_H.h"

using namespace std;

#ifndef KB_H
#define KB_H

class KB{
public:
       void add(fact p_item);
	 // adds a fact to the KB
       void drop(fact p_fact);
	 // removes a fact from the KB
       string print(bool out);
	 // can either print hash or store it in a string
       unordered_multimap<string, fact> hash;
	 // the hash used to store everything

};

#endif
