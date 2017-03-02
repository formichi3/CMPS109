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
  RB curRB;
  KB curKB;
  void checkLine(string x);
  void addRule(string x);
  void addFact(string x);
  void load(string x);
  void dump(string x);
  void infer(string x);
  void drop(string x);
  void inferFact(string p_factName);
  void inferRule(rule p_ruleName);
  //vector <vector<string>> getFacts(string p_name);
};

#endif
