#include "RB_H.h"
#include <iostream>


rule::rule(){
  name = "";
  logOperator = 0;
}
rule::rule(string p_name){
  this->name = p_name;
}
rule::~rule(){
}

// RB::RB(){
//   cout << "\ncreating data base\n" << endl;
// }
// RB::~RB(){
//   cout << "\ndestroying data base\n" << endl;
// }
// void RB::add(rule p_rule){
//   pair<string, rule> p_insert (p_rule.name, p_rule);
//   this->hash.insert (p_insert);
// }
// void RB::print(){
//   cout << "Rules:" << endl;
//   for ( auto it = this->hash.begin(); it != this->hash.end(); ++it ){
//     cout << it->first << endl;
//   }
// }
//
// void RB::drop(string p_name){
//   this->hash.erase(p_name);
// }
