#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#include "RBImp.cpp"


int main(){


  rule myrule1("joe");
  rule myrule2("trevor");
  rule myrule3("jake");
  rule myrule4("bronte");

  RB myRB;

  myRB.add(myrule1);
  myRB.add(myrule2);
  myRB.add(myrule3);
  myRB.add(myrule4);


  myRB.print();

  myRB.drop("joe");

  myRB.print();



  return 0;
}
