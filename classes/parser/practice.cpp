#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main(){
  string name;

  cout<<"enter rule name: ";
  cin>>name; 

  vector< vector<string> > facts;
  vector< vector<string> > rules;
  vector <string> args;
  vector <string> temp;
  
  temp.push_back(name);
  temp.push_back("arg1");
  temp.push_back("arg2");
  
  facts.push_back(temp);
  
  temp.clear();//= vector<string>();
  cout<<"checking clear: "<<(temp)[0]<<endl;
  
  temp.push_back("clear!");
  cout<<"checking push: "<<(temp)[1]<<endl;
  cout<<(temp)[0]<<endl;
  cout<<temp.size()<<endl;
  facts.push_back(temp);
  
  for(int i=0; i<5;i++)
    cout<<(facts)[1][i]<<endl;
  
  cout<<(temp)[2];
  cout<<temp.size()<<endl;
  return 0;
}