#ifndef PARSENEW_H
#define PARSENEW_H

#include <iostream>
#include <string>

using namespace std;
class parse{

 private:
  int inputSize;

 public:
  void checkLine(string x);
  void rule(string x);
  void fact(string x);
  void load(string x);
  void dump(string x);
  void infer(string x);
  void drop(string x);

};





#endif
