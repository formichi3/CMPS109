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
  cout << name << endl;
}
