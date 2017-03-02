#include "RB_H.h"
#include <iostream>
#include <typeinfo>


RB::RB(){
  cout << "\ncreating data base\n" << endl;
}
RB::~RB(){
  hash.erase(hash.begin(), hash.end());
  cout << "\ndestroying data base\n" << endl;
}
void RB::add(rule p_rule){
  pair<string, rule> p_insert (p_rule.name, p_rule);
  this->hash.insert (p_insert);
}

void RB::dump(){
  for (auto it = this->hash.begin(); it != this->hash.end(); it++){
    it->second.print();
  }
}
void RB::drop(string p_name){
  this->hash.erase(p_name);
}
void RB::traversRule(string p_name){
  auto range = hash.equal_range(p_name);
  for (auto x = range.first; x != range.second; x++){
    x->second.print();
  }
  cout << endl;
}
