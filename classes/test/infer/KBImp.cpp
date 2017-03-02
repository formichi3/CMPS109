#include "KB_H.h"
#include <iostream>


void KB::add(fact p_fact){
  vector <string> sameName;
  // if they have the same name
  //if(hash.find(p_fact.name)!=hash.end) 
  // create a pair wiith the fact name and fact object
  pair<string, fact> p_insert (p_fact.name, p_fact);
  // insert that pair into the hash
  this->hash.insert (p_insert);
}

string KB::print(bool out){
  // stores output into a string
  string file;
  // loop through hash
  for ( auto it = hash.begin(); it != hash.end(); ++it){
    // print the fact name
    if (out) cout << "FACT " << it->first << " ";
    file += "FACT ";
    file += it->first;
    file += "(";
    // loop through the vector of parameters
    for (int i = 0; i<it->second.paramaters.size(); ++i) {
      // print these paramaters
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
