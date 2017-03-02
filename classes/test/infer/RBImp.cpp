#include "RB_H.h"
#include <iostream>


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

string RB::dump(bool out){
  string b, rb;
  for (auto it = this->hash.begin(); it != this->hash.end(); it++){
    // it->second.print();
    rb = it->second.print();
  }
  return rb; 
}
void RB::drop(string p_name){
  this->hash.erase(p_name);
}
