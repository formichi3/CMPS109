#include "Rule_H.h"

using namespace std;

rule::rule(){
  name = "";
  logOperator = 0;
}

rule::rule(string p_name, vector < string > p_args, int p_Operator, vector < vector < string > > p_preds){
  name = p_name;
  args = p_args;
  logOperator = p_Operator;
  predicates = p_preds;
}

rule::~rule(){
}

void rule::print(){
  cout << endl << name << "(";
  for ( auto it  = args.begin(); it != args.end(); it++){
    cout << *it;
  }
  cout << "):- ";

  if(logOperator == 1){
    cout << "AND ";
  }
  else{
    cout << "OR ";
  }

  int index = 0;
  for ( auto it  = predicates.begin(); it != predicates.end(); it++){
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
