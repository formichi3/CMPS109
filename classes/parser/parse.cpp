#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char* argv[]){
  string check = "aaaaa";
  int testing;
  testing=check.find("a",0);

 cout<<"test"<<testing<<endl;

    cout<< "enter a command...-1 to exit"<<endl;
    string input;
    while(getline(cin,input)&&input!="-1"){
      cout<<"parsing input"<<endl;      
      string command = input.substr(0,4);//sets string equal to first 4 letters
      
      if(command=="RULE"||command=="rule")cout<<"do rule stuff"<<endl;//working
      else if(command=="FACT"){
	int start = input.find("(" , 0);
	int comma = input.find("," ,0);
	int end = input.find(")" , 0);
	string param1=input.substr(start+1,(comma-start-1));
	string param2=input.substr(comma+1,end-comma-1);
	cout<<"param1 "<< param1 <<endl;
	cout<<"param2 "<<param2<<endl;
      }//end of rule parsing
      

      else if(command=="DUMP")cout<<"do dump stuff"<<endl;
      else if(command=="LOAD"){//opens file and reads it line by line
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
	    cout<<line<<endl; // Process str                              
	  }
      }//end of load parsing
      
      else if(command=="DROP")cout<<"do drop stuff"<<endl;
      else if(command=="INFE"){
cout<<"do inference stuff"<<endl;

 int space = input.find(" " , 0);
 int end = input.find("(" , 0);
 string query=input.substr(space+1,(end-space-1));
 cout<<"inference "<<query<<endl;

}

      else cout<<"please enter valid command"<<endl;
      
      int space = input.find(" " , 0);
      int end1 = input.find("(" , 0);
      cout << "space found at " << space << endl;
      string firstword=input.substr(space+1,(end1-space-1));
      cout<<firstword<<"---"<<endl;
      
   cout<<"enter a command...-1 to exit"<<endl; 

    }//close while loop
  
  return 0;
}
