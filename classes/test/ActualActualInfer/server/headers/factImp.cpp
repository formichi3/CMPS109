#include "Fact_H.h"

fact::fact(){
  name = "";
}
fact::fact(string p_name, vector <string> p_paramaters){
  name = p_name;
  paramaters = p_paramaters;
}
fact::~fact(){
}
bool operator==(const fact &left, const fact &right){
  if (left.name == right.name){
    if (left.paramaters.size() == right.paramaters.size()){
      auto it2 = right.paramaters.begin();
      for (auto it = left.paramaters.begin(); it != left.paramaters.end(); it++){
        if (*it != *it2){
          return false;
        }
        it2++;
      }
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
