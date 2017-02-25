#include "Rule_H.h"

rule::rule(){
  name = "";
  logOperator = 0;
}
rule::rule(string p_name){
  this->name = p_name;
}
rule::~rule(){
}
