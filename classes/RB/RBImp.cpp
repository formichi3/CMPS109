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
// void RB::print(){
//   cout << "\nRules:" << endl;
//   for ( auto it = this->hash.begin(); it != this->hash.end(); ++it ){
//     string op;
//     if (it->second.logOperator){
//       op = "OR";
//     }
//     else {op = "AND";}
//     cout << endl << it->first << "(";
//     for ( int i = 0; i < it->second.args.size(); i++){
//       cout << it->second.args[i];
//     }
//     cout << "):- " << op << " ";
//     for ( int i = 0; i < it->second.facts.size(); i++){
//       cout << it->second.facts[i][0]  << "(";
//       for ( int j = 1; j < it->second.facts[j].size(); j++){
//         cout << it->second.facts[i][j];
//       }
//       cout << ") ";
//     }
//   }
// }

void RB::print2(){
  for (auto it = this->hash.begin(); it != this->hash.end(); it++){
    it->second.print();
  }
}
void RB::drop(string p_name){
  this->hash.erase(p_name);
}
