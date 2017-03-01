#include "KB_H.h"
#include <iostream>


void KB::add(fact p_fact){
  pair<string, fact> p_insert (p_fact.name, p_fact);
  this->hash.insert (p_insert);
}

string KB::print(bool out){
  string file;
  for ( auto it = hash.begin(); it != hash.end(); ++it){
    if (out) cout << "fact " << it->first << " ";
    file += "fact ";
    file += it->first;
    file += "(";
    for (int i = 0; i<it->second.paramaters.size(); ++i) {
      if (out) cout << it->second.paramaters[i] << " ";
      file+=it->second.paramaters[i];
      if (i != it->second.paramaters.size()-1) file+=",";
    }
    if (out) cout << endl;
    file+=")\n";
  }
  if (out) cout << endl;
  file+="\n";
  return file;
}

void KB::drop(string p_name){
  this->hash.erase(p_name);
}
