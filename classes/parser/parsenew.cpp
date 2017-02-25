#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class parse{

public:
   void checkLine(string input){
    inputSize=input.size();
    cout<<"parsing input"<<endl;
    string command = input.substr(0,4);//sets string equal to first 4 letters 

    if(command=="RULE"||command=="rule")rule(input);//cout<<"do rule stuff"<<endl;
    else if(command=="FACT"||command=="fact")fact(input);
    else if(command=="DUMP"||command=="dump")cout<<"do dump stuff"<<endl;
    else if(command=="LOAD"||command=="load")cout<<"do load stuff"<<endl;
    else if(command=="DROP"||command=="drop")cout<<"do drop stuff"<<endl;
    else if(command=="INFE"||command=="infe")infer(input);
    else cout<<"please enter valid command"<<endl;
  }

  void rule(string input){
    int space = input.find(" " , 0);
    int endrule = input.find(" " , space+1);
    string factName=input.substr(space+1,(endrule-space-1));
    cout<<"fact: "<<factName<<endl;
    int operand;
    int preop=input.find(" ", endrule);
    string oper=input.substr(preop+1,2); 
    if(oper=="or"||oper=="OR")operand=0;
    else operand=1;
    cout<<"operand "<<operand<<endl;



    int start1 = input.find(" " , postop);
    int end1 = input.find("(" ,start1+1);
    int start2 = input.find(" " , end1);
    int end2 = input.find("\n",start2);

    // string param1=input.substr(start+1,(comma-start-1));
    //    string param2=input.substr(comma+1,end-comma-1);
    cout<<"param1 "<< param1 <<endl;
    cout<<"param2 "<<param2<<endl;


}



  void fact(string input){

    int space = input.find(" " , 0);
    int endfact = input.find(" " , space+1);
    string factName=input.substr(space+1,(endfact-space-1));
    cout<<"fact: "<<factName<<endl;

    int start = input.find("(" , 0);
    int comma = input.find("," ,0);
    int end = input.find(")" , 0);
    string param1=input.substr(start+1,(comma-start-1));
    string param2=input.substr(comma+1,end-comma-1);
    cout<<"param1 "<< param1 <<endl;
    cout<<"param2 "<<param2<<endl;
  }

  void load(string input){//opens file and reads it line by line      
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
	checkLine(line);
	cout<<line<<endl; // Process str                              
      }
  }//end of load parsing                                               



  void infer(string input){
    int inferSpace = input.find(" " , 0);
      int brace = input.find("(" , 0);
      string query=input.substr(inferSpace+1,(brace-inferSpace-1));
      cout<<"inference: "<<query<<endl;
      int end=input.find(")" , 0);
      if(end+1<inputSize){
	int space2=input.find(" ",end);
	int end2=input.find(" ",space2+1);
	cout<<"space2 value "<<space2<<" end2 value " <<end2<<endl;
	if(end2==-1) end2=input.find("\n",space2);
	string query2=input.substr(space2+1,end2-space2-1);
	cout<<"query2  ("<<query2<<")"<<endl;
      }
  }


private:
 int inputSize;


};

int main(){
  parse p;
  cout<< "enter a command...-1 to exit"<<endl;
  string input;

  while(getline(cin,input)&&input!="-1"){
    p.checkLine(input);

  }

  return 0;
}
