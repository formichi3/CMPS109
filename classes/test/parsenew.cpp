//#include "../fact/Fact_H.h"
#include "parsenew.h"
//#include <unordered_map>

using namespace std;


void parse::checkLine(string input){
  inputSize=input.size();
  cout<<"parsing input"<<endl;
  string command = input.substr(0,4);//sets string equal to first 4 letters 
  
  if(command=="RULE"||command=="rule")rule(input);//cout<<"do rule stuff"<<endl;
  else if(command=="FACT"||command=="fact")addFact(input);
  else if(command=="DUMP"||command=="dump")dump(input);
  else if(command=="LOAD"||command=="load")load(input);
  else if(command=="DROP"||command=="drop")drop(input);
  else if(command=="INFE"||command=="infe")infer(input);
  else cout<<"please enter valid command"<<endl;
}

void parse::rule(string input){//working
  vector<pair <string,vector <char> > > rules;
  vector<pair <string,vector <char> > > facts;    
  
  int space = input.find(" " , 0);
  int endrule = input.find("(" , space+1);
  string factName=input.substr(space+1,(endrule-space-1));//name of rule
  cout<<"rule: "<<factName<<endl;
  
  int end1 =  input.find("(" , 0);
  int endparam=input.find(")", 0);
  string token=input.substr(end1, (endparam-end1+1));//create token of args
  cout<<"testing token "<<token<<endl;
  
  string parameter;
  int base=1;
  int tail;
  while(base<token.length()){   //given token of args, splits into strings
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    
    parameter = token.substr(base,tail-base);
    cout<<"parameter: "<<parameter<<endl;//insert rule arg
    base=tail+1;
  }
  
  
  int operand;
  int preop=input.find(" ", endrule);
  string oper=input.substr(preop+1,2); 
  if(oper=="or"||oper=="OR")operand=0;//determines operand
  else if (oper=="an"||oper=="AN")operand=1;
  else {
    cout<<"Please enter valid operator."<<endl;
    return;
  }
  cout<<"operand "<<operand<<endl;//insert operator
  int cursor=preop+1;
  
  int start1;
  string name;
  while(cursor<input.length()){	//continue while predicates remain
    start1 = input.find(" " , cursor);
    end1 =  input.find("(" , cursor);
    name = input.substr(start1+1,(end1-start1-1));//predicate name
    cout<<"name: "<< name<<endl;//test then insert predicate name
    cursor=end1;
    endparam=input.find(")",end1);
    
    token=input.substr(cursor, (endparam-cursor+1));
    cout<<"testing token "<<token<<endl;
    cursor=endparam+1;
    
    base=1;	 
    while(base<token.length()){ //splits token into strings
      tail=token.find(",",base);
      if(tail==-1)tail=token.find(")",base);
      
      parameter = token.substr(base,tail-base);
      cout<<"parameter: "<<parameter<<endl;//insert predicate arg
      base=tail+1;
    }    
    cout<<"finished with predicate"<<endl;
    cursor=endparam+1;
  }
}

void parse::addFact(string input){//working

  int space = input.find(" " , 0);
  int endfact = input.find("(" , space+1);
  string factName=input.substr(space+1,(endfact-space-1));
  cout<<"fact: "<<factName<<endl;//insert fact name
  
  int end1 =  input.find("(" , 0);
  int endparam=input.find(")", 0);
  string token=input.substr(end1, (endparam-end1+1));
  cout<<"testing token "<<token<<endl;
  
  string parameter;
  vector <string> params; // vector containing facts
  int base=1;
  int tail;
  int p = 0; // contains current index for param vector
  while(base<token.length()){
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    parameter = token.substr(base,tail-base); // string containing a paramater
    cout<<"parameter: "<<parameter;
    params.push_back(parameter); // add paramater to vector
    cout<<" & params "<<p<<": "<<params[p]<<endl; 
    p++;
    base=tail+1;
  }
  // create fact obj
  fact curFact(factName, params); // takes name then paramater vector as it's paramaters
  // add fact to KB
  curKB.add(curFact);
  curKB.print(true);
}

void parse::dump(string input){
   cout<<"do dump stuff"<<endl;
   int space = input.find(" " , 0);
   int endfile = input.find("\n" , 0);
   string filename=input.substr(space+1,(endfile-space-1));
   ofstream file;
   file.open(filename);
   string f = curKB.print(false);
   file << f;
   file.close();
}

void parse::load(string input){//working, opens file and reads it line by line      
  cout<<"do load stuff"<<endl;
  int space = input.find(" " , 0);
  int endfile = input.find("\n" , 0);
  string filename=input.substr(space+1,(endfile-space-1));
  cout<<filename<<"---"<<endl;
  
  ifstream infile;
  infile.open(filename.c_str());
  string line;
    while (std::getline(infile, line))
      {
	cout<<endl<<line<<endl; // Process str                              
	checkLine(line); 
      }
}//end of load parsing                                               

void parse::infer(string input){      //working
  int inferSpace = input.find(" " , 0);
  int end1 = input.find("(" , 0);
  string query=input.substr(inferSpace+1,(end1-inferSpace-1));
  cout<<"inference: "<<query<<endl;
  
  int endparam=input.find(")", 0);
  string token=input.substr(end1, (endparam-end1+1));
  cout<<"testing token "<<token<<endl;
  
  string parameter;
  int base=1;
  int tail;
  while(base<token.length()){
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    
    parameter = token.substr(base,tail-base);
    cout<<"parameter: "<<parameter<<endl;
    base=tail+1;
  }
  
  int end=input.find(")" , 0);
  if(end+1<inputSize){
    int space2=input.find(" ",end);
    int end2=input.find(" ",space2+1);
    if(end2==-1) end2=input.find("\n",space2);
    string query2=input.substr(space2+1,end2-space2-1);
    cout<<"query2  ("<<query2<<")"<<endl;
  }
}

void parse::drop(string input){
  int space=input.find(" ",0);
  int end = input.find(" ",space+1);
  if(end==-1)end=input.find("\n",space);
  
  string name=input.substr(space+1,end-space-1);
  cout<<"name: "<<name<<endl;
  curKB.drop(name);
}

int main(){
  parse p;
  cout<< "enter a command...-1 to exit"<<endl;
  string input;
  
  while(getline(cin,input)&&input!="-1"){
    p.checkLine(input);
  }
  return 0;
}
