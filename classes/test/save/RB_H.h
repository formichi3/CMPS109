#include <iostream>
#include <unordered_map>
#include <vector>
#include "Rule_H.h"

using namespace std;

#ifndef RB_H
#define RB_H


class RB{
public:
       RB();
       ~RB();
       void add(rule p_item);
       void drop(string p_name);
       string dump();
       vector<rule> traverseRule(string p_name);
       unordered_multimap<string, rule> hash;
       //unordered_map<string, rule> hash;
};



#endif
