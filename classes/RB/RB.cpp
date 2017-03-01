#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
#include "../rule/ruleImp.cpp"
#include "RBImp.cpp"


int main(){



  RB myRB;


  vector< vector < string > > preds;

  vector< string > arg1;
  arg1.push_back("father");
  arg1.push_back("$X");
  arg1.push_back("$Z");

  vector< string > arg2;
  arg2.push_back("parent");
  arg2.push_back("$Z");
  arg2.push_back("$Y");

  preds.push_back(arg1);
  preds.push_back(arg2);


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
  arg5.push_back("$Z");


  preds.push_back(arg3);
  preds.push_back(arg4);
  preds.push_back(arg5);

  vector< string > args;
  args.push_back("$X");
  args.push_back("$Y");


  rule myRule("MyRule", args, 1, preds);
  rule myRule2("MyRule2", args, 1, preds);
  rule myRule3("MyRule3", args, 1, preds);

  myRB.add(myRule);
  myRB.add(myRule2);
  myRB.add(myRule3);



  rule myRule4("MyRule3", args, 1, preds);

  cout << "rule base size: " << myRB.hash.size() << endl;
  //myRB.print();

  myRB.add(myRule4);
  cout << "rule base size: " << myRB.hash.size() << endl;

  myRB.dump();



  return 0;
}
