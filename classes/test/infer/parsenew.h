#ifndef PARSENEW_H
#define PARSENEW_H

#include "Fact_H.h"
#include "KB_H.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <string>

using namespace std;
class parse{

 private:
  int inputSize;

 public:
  KB curKB;
  void checkLine(string x);
  void rule(string x);
  void addFact(string x);
  void load(string x);
  void dump(string x);
  void infer(string x);
  void inferRule(rule iRule);
  void drop(string x);

};

#endif
