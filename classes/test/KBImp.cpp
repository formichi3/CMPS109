#include "KB_H.h"
#include <iostream>


/*KB::KB(fact){
  cout << "\ncreating data base\n" << endl;
}
KB::~KB(){
  cout << "\ndestroying data base\n" << endl;
}*/
void KB::add(fact p_fact){
  pair<string, fact> p_insert (p_fact.name, p_fact);
  this->hash.insert (p_insert);
}

void KB::print(){
  cout << "Facts:" << endl;
  for ( auto it = hash.begin(); it != hash.end(); ++it){
    cout << it->first << " ";
    for (int i = 0; i<it->second.paramaters.size(); ++i) {
      cout << it->second.paramaters[i] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void KB::drop(string p_name){
  this->hash.erase(p_name);
}
