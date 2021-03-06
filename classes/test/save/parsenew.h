#ifndef PARSENEW_H
#define PARSENEW_H

#include "Fact_H.h"
#include "Rule_H.h"
#include "KB_H.h"
#include "RB_H.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
class parse{

 private:
  int inputSize;

 public:
  // databases
  RB curRB;
     // unordered map that stores rules
  KB curKB;
     // unordered map that stores facts
  vector <string> inferParamNames;
     // stores the param names that are called with infer
  // functions
  void checkLine(string x);
     // checks line input
  void addRule(string x);
     // adds a rule to curRB
  void addFact(string x);
     // adds a fact to curKB
  void load(string x);
     // loads a file
  void dump(string x);
     // dumps the contents of curRB and curKB into a file
  void infer(string x);
     // infer prints all facts upon which a rule infers upon
     // about 50% complete
  void drop(string x);
     // drops facts or rules from their respective database
  vector<vector<string>> inferFact(string p_factName,string newfactname, bool doStuff);
     // helper function for infer
  vector<vector<vector<string>>> inferRule(rule p_ruleName,string newfactname, 
                                 vector<vector<vector<string>>> allRelationships, int count);
     // recursive helper function for infer
  void doOR(vector<vector<vector<string>>> allRelationships, rule p_rule, int count);
  void doAND(vector<vector<vector<string>>> allRelationships, rule p_rule, int count);
  void printSomething1D(vector<string> oneRelation, int count);
  void printSomething(vector<vector<string>> relations, int count);
  void printSomething3D(vector<vector<vector<string>>> allRelations, int count);
};

#endif
