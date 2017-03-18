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
#include <unordered_map>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>
#include <typeinfo>
#include <future>
#include <thread>
#include <functional>



using namespace std;
class parse{

 private:
  int inputSize;
  vector< shared_future <string> > predThreads;
  vector< shared_future < vector < vector <string> > > > ORThreads;//vector of OR threads

 public:
  // vars
  int predicates;
  string newfactname;
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
  vector<vector<string>> inferRule(rule p_ruleName,string newfactname,
                                 vector<vector<vector<string>>> allRelationships, int count);
     // recursive helper function for infer
  vector<vector<string>> doOR(vector<vector<vector<string>>> allRelationships, rule p_rule, int count);
  unordered_map<string,vector<string>> vector3DToMap(vector<vector<vector<string>>> vec, bool nAND);
  vector<vector<string>> mapToVector(unordered_map <string,vector<string>> relations);
  vector<vector<string>> mapToVector2(map <string,vector<string>> relations);
  vector<vector<string>> doAND(vector<vector<vector<string>>> allRelationships, rule p_rule, int count, bool first);
  vector<vector<string>> getSolutionAND(vector<vector<string>> result, rule p_rule);
  vector<vector<string>> doAND0(vector<vector<vector<string>>> allRelationships, rule p_rule, int count);
  void printSomething1D(vector<string> oneRelation, int count);
  void printSomething(vector<vector<string>> relations, int count);
  void printSomething3D(vector<vector<vector<string>>> allRelations, int count);
  //vector<vector<string>> searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position);
  //unordered_map<string, vector<string>> searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position);
  unordered_map<string, vector<string>> searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position);
  //vector<string> searchResultsVector(string searchName, vector<vector<string>> searchVector, int position);
  void printMap(unordered_map<string,vector<string>> result2);
  void printMap2(map<string, vector<string>> result2);
  void addFacts(unordered_map<string, vector <string>> facts, string factName);
};

#endif
