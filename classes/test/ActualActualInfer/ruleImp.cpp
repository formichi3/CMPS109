#include "Rule_H.h"
#include <typeinfo>

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

string rule::createString(){
  string ruleString = name + "(";
  for ( auto it  = args.begin(); it != args.end(); it++){
    ruleString = ruleString + *it + ",";
  }
  ruleString.pop_back();
  ruleString = ruleString + "):- ";
  if(logOperator == 1){
    ruleString = ruleString + "AND";
  }
  else{
    ruleString = ruleString + "OR";
  }

  int index = 0;
  for ( auto it  = predicates.begin(); it != predicates.end(); it++){
      auto it2 = it->begin();
      for ( auto it2 = it->begin(); it2 != it->end(); it2++){
        if (it2 == it->begin()){
          ruleString = ruleString + " " + *it2 + "(";
        }
        else{
          ruleString = ruleString + *it2 + ",";
        }
      }
      ruleString.pop_back();
      ruleString = ruleString + ")";
  }
  return ruleString;
}

bool operator==(const rule &left, const rule &right){

  if (left.logOperator == right.logOperator && left.args.size() == right.args.size() && left.predicates.size() == right.predicates.size()){
    for (int i = 0; i < left.args.size(); i++){
      if(left.args[i] != right.args[i]){
        return false;
      }
    }
    auto it2 = right.predicates[0].begin();
    for (int j = 0 ;j < left.predicates.size(); j++){
	  it2 = right.predicates[j].begin();
      for (auto it = left.predicates[j].begin(); it != left.predicates[j].end(); it++){
        if(*it != *it2){
          return false;
        }
        it2++;
      }
    }
    return true;
  }
  else{
    return false;
  }



}
