#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
#include "../rule/ruleImp.cpp"
#include "RBImp.cpp"


int main(){



  RB myRB;


  vector< vector < string > > rules;

  vector< string > arg1;
  arg1.push_back("father");
  arg1.push_back("$X");
  arg1.push_back("$Z");

  vector< string > arg2;
  arg2.push_back("parent");
  arg2.push_back("$Z");
  arg2.push_back("$Y");

  rules.push_back(arg1);
  rules.push_back(arg2);

  vector< vector < string > > facts;

  vector< string > arg3;
  arg3.push_back("brother");
  arg3.push_back("$X");
  arg3.push_back("$Z");

  vector< string > arg4;
  arg4.push_back("sister");
  arg4.push_back("$Z");
  arg4.push_back("$Y");

  vector< string > arg5;
  arg5.push_back("dog");
  arg5.push_back("$Z");
  arg5.push_back("$Y");


  facts.push_back(arg3);
  facts.push_back(arg4);
  facts.push_back(arg5);

  vector< string > args;
  args.push_back("$X");
  args.push_back("$Y");

  rule myRule("MyRule", args, 1, rules, facts);
  rule myRule2("MyRule2", args, 1, rules, facts);

  myRB.add(myRule);
  myRB.add(myRule2);

  cout << "rule base size: " << myRB.hash.size();
  myRB.print();




  return 0;
}
