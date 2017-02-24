#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#ifndef RB_H
#define RB_H


class rule{

public:
       rule();
       rule(string p_name);
       ~rule();
       string name;
       bool logOperator; //0=OR, 1=AND
};

class RB : public Moderator{
public:
       RB();
       ~RB();
       unordered_map<string, rule> hash;

private:

};



#endif
