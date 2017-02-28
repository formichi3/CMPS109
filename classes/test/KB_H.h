#include <iostream>
#include <unordered_map>
#include <vector>
#include "../fact/Fact_H.h"

using namespace std;

#ifndef KB_H
#define KB_H

class KB{
public:
       //KB(fact);
       //~KB();
       void add(fact p_item);
       void drop(string p_name);
       void print();
       unordered_map<string, fact> hash;

};

#endif
