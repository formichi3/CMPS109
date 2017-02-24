#include "Moderator_H.h"
#include <iostream>


Moderator::Moderator(){
  cout << "\ncreating data base\n" << endl;
}
Moderator::~Moderator(){
  cout << "\ndestroying data base\n" << endl;
}

template <class T>
void Moderator::add(T p_item){
  pair<string, T> p_insert (p_item.name, p_item);
  this->hash.insert (p_insert);
}
void Moderator::print(){
  cout << "Rules:" << endl;
  for ( auto it = this->hash.begin(); it != this->hash.end(); ++it ){
    cout << it->first << endl;
  }
}

void Moderator::drop(string p_name){
  this->hash.erase(p_name);
}
