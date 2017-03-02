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
#include <utility>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
class parse{

 private:
  int inputSize;

 public:
  // instances of databases
  RB curRB;
  KB curKB;

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
  void inferFact(string p_factName);
     // helper function for infer
  void inferRule(rule p_ruleName);
     // recursive helper function for infer
};

#endif
