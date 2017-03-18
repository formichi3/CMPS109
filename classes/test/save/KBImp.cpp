#include "KB_H.h"
#include <iostream>


void KB::add(fact p_fact){
  vector <string> sameName;
  int match = 0;
  // if they have the same name
  //if(hash.find(p_fact.name)!=hash.end)
  // create a pair wiith the fact name and fact object
  pair<string, fact> p_insert (p_fact.name, p_fact);
  auto matchingNames = traverseFact(p_fact.name);
  for(auto it = matchingNames.begin(); it != matchingNames.end(); it++){
    if(p_fact == *it){
		cout << "Fact already in DB - Please enter a unnique fact\n";
      match = 1;
    }
  }
  // insert that pair into the hash
  if(!match){
    this->hash.insert (p_insert);
  }
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

vector<fact> KB::traverseFact(string factName){
  auto range = hash.equal_range(factName);
  vector<fact> matchingFacts;
  for (auto x = range.first; x != range.second; x++){
    matchingFacts.push_back(x->second);
  }
  return matchingFacts;

}

void KB::drop(string p_name/*, fact p_fact*/){
  /*for (auto it = hash.bucket(p_name).begin(); it != hash.bucket(p_name).end(); it++) {
     if (it.name == p_fact.name && it.paramaters==p_fact.paramaters) hash.erase(it);
  }*/
  this->hash.erase(p_name);
}
