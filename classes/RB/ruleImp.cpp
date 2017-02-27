#include "Rule_H.h"

rule::rule(){
  name = "";
  logOperator = 0;
}
rule::rule(string p_name){
  this->name = p_name;
}
rule::~rule(){
}
void rule::print2(){
  cout << "entered print function"
  for ( auto it  = predicates.begin(); it != predicates.end(); it++){
    cout << it->first << "(";
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
        //cout << *it2;
      }
    //cout << ") ";
  }
}
