ls#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char* argv[]){
  if(argc>1){ //read from file
  ifstream infile(argv[1]);
  string line;
  while (std::getline(infile, line))
    {
      cout<<line<<endl; // Process str
    }
  }
  
  else{   //no file input
    cout<< "enter a command...-1 to exit"<<endl;
    string input;
    while(getline(cin,input)&&input!="-1"){
      cout<<"parsing input"<<endl;
      string command = input.substr(0,4);//sets string equal to first 4 letters
      if(command=="RULE")cout<<"do rule stuff"<<endl;
      else if(command=="FACT")cout<<"do fact stuff"<<endl;
      else if(command=="DUMP")cout<<"do dump stuff"<<endl;
      else if(command=="LOAD")cout<<"do load stuff"<<endl;
      else if(command=="DROP")cout<<"do drop stuff"<<endl;
      else if(command=="INFE")cout<<"do inference stuff"<<endl;
      else cout<<"please enter valid command"<<endl;
   
      int space = input.find(" " , 0);
      int end1 = input.find("(" , 0);
      cout << "space found at " << space << endl;
      string firstword=input.substr(space+1,(end1-space-1));
      cout<<firstword<<"---"<<endl;

   cout<<"enter a command...-1 to exit"<<endl; 
    }//close while loop
    
  }//close else/user input loop
  
  return 0;
}
