#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#include "KB_H.h"


int main(){


  vector <string> test;
  test.push_back("a");
  test.push_back("b");

  fact myfact1("joe", test);
  fact myfact2("trevor", test);
  fact myfact3("jake", test);
  fact myfact4("bronte", test);

  KB myKB;
  myKB.add(myfact1);
  myKB.add(myfact2);
  myKB.add(myfact3);
  myKB.add(myfact4);

  myKB.print();

  myKB.drop("joe");

  myKB.print();

  return 0;
}
