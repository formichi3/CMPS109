#include "RB_H.h"
#include <iostream>
#include <typeinfo>
#include <fstream>


RB::RB(){
  cout << "\ncreating data base\n" << endl;
}
RB::~RB(){
  hash.erase(hash.begin(), hash.end());
  cout << "\ndestroying data base\n" << endl;
}
void RB::add(rule p_rule){
  int match = 0;
  pair<string, rule> p_insert (p_rule.name, p_rule);
  vector<rule> sameKeyRules = this->traversRule(p_rule.name);
  if(sameKeyRules.size() != 0){
    for (auto it = sameKeyRules.begin(); it != sameKeyRules.end(); it++){
      if (p_rule == *it){
		cout << "Rule already exists! Please enter a unique rule\n";
        match = 1;
        break;
      }
    }
    if(~match){
      this->hash.insert(p_insert);
    }
  }
  else{
    this->hash.insert(p_insert);
  }
}

string RB::dump(){
  string allRules;
  vector <string> rules;
  for (auto it = this->hash.begin(); it != this->hash.end(); it++){
    rules.push_back(it->second.createString());
  }
  for (auto it = rules.begin(); it != rules.end(); it++){
    allRules += "RULE " + *it + "\n";
    cout << *it << endl;
  }

  return allRules;
}
void RB::drop(string p_name){
  this->hash.erase(p_name);
}
vector<rule> RB::traversRule(string p_name){
  auto range = hash.equal_range(p_name);
  vector <rule> matchingRules;
  for (auto x = range.first; x != range.second; x++){
    matchingRules.push_back(x->second);
  }
  cout << endl;
  return matchingRules;
}
