#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#ifndef Moderator_H
#define Moderator_H

template <class T>
class Moderator{
public:
       Moderator();
       ~Moderator();
       void add(T p_item);
       void drop(string p_name);
       void print();
       //unordered_map<string, T> hash;

private:

};

#endif
