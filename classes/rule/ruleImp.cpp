#include "Rule_H.h"

using namespace std;

rule::rule(){
  name = "";
  logOperator = 0;
}
rule::rule(string p_name){
  this->name = p_name;
}
rule::rule(string p_name, vector < string > p_args, int p_Operator, vector < vector < string > > p_rules, vector < vector < string > > p_facts ){
  name = p_name;
  args = p_args;
  logOperator = p_Operator;
  rules = p_rules;
  facts = p_facts;
}
rule::~rule(){
}

void rule::print(){
  cout << endl << name << "(";
  for ( auto it  = args.begin(); it != args.end(); it++){
    cout << *it;
  }
  cout << "):- ";

  if(logOperator){
    cout << "AND ";
  }
  else{
    cout << "OR ";
  }

  int index = 0;
  for ( auto it  = facts.begin(); it != facts.end(); it++){
      auto it2 = it->begin();
      for ( auto it2 = it->begin(); it2 != it->end(); it2++){
        if (it2 == it->begin()){
          cout << *it2 << "(";
        }
        else{
          cout << *it2;
        }
      }
      cout << ")";
  }


}
