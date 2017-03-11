//#include "../fact/Fact_H.h"
#include "parsenew.h"
#include <unordered_map>
#include <typeinfo>

using namespace std;


void parse::checkLine(string input){
  inputSize=input.size();
  //cout<<"Enter a command"<<endl;
  string command = input.substr(0,4);//sets string equal to first 4 letters
  //  input.erase(remove(input.begin(),input.end(), '\t'), input.end());//removes tabs characters...doesn't work
  string input2=input;    //input2 will be no whitespace version
  input2.erase( remove( input2.begin(), input2.end(), ' ' ), input2.end() );//removes whitespaces from input
  //cout<<input2<<endl;
 if(command=="RULE"||command=="rule")addRule(input);//parse okay durability
 else if(command=="FACT"||command=="fact")addFact(input2);//parse durable
  else if(command=="DUMP"||command=="dump")dump(input2);//parse durable
  else if(command=="LOAD"||command=="load")load(input2);//parse durable, weak at calling from main
  else if(command=="DROP"||command=="drop")drop(input2);//parse durable
  else if(command=="INFE"||command=="infe")infer(input);//parse needs work
  else cout<<"please enter valid command"<<endl;
}

void parse::addRule(string input){//working
  vector<pair <string,vector <char> > > rules;
  vector<pair <string,vector <char> > > facts;

  int space = input.find(" " , 0);
  while(input.substr(space+1,1)==" ")space++;


  int endrule = input.find("(" , space+1);
  string factName=input.substr(space+1,(endrule-space-1));//name of rule
  //  cout<<"factname: "<<factName<<endl;

  int end1 =  input.find("(" , 0);
  int endparam=input.find(")", 0);
  string token=input.substr(end1, (endparam-end1+1));//create token of args
  token.erase( remove( token.begin(), token.end(), ' ' ), token.end() );//removes whitespaces from token
//cout<<"testing token "<<token<<endl;

  string parameter;
  int base=1;
  int tail;
  vector <string> params;
  int c = 0;
  while(base<token.length()){   //given token of args, splits into strings
    tail=token.find(",",base);
    while(token.substr(tail+1,1)==" ")tail++;
    if(tail==-1)tail=token.find(")",base);
    parameter = token.substr(base,tail-base);
    params.push_back(parameter);
    //cout<<"parameter: "<<parameter<<" & params "<<params[c]<<endl;//insert rule arg
    c++;
    base=tail+1;
  }//closes while loop getting rule args

  int operand;
  int preop=input.find(":-", endrule)+1;//sets cursor to front end of symbol
  while(input.substr(preop+1,1)==" ")preop++;
  string oper=input.substr(preop+1,2);
  if(oper=="or"||oper=="OR")operand=0;//determines operand
  else if (oper=="an"||oper=="AN")operand=1;
  else {
    cout<<"Invalid operator"<<endl;
    return;
  }
  //cout<<"operand "<<operand<<endl;//insert operator
  int cursor=preop+3;
  while(input.substr(cursor+1,1)==" ")cursor++;
  int start1;
  string name;
  vector < vector <string> > predParams;
  int predCount = 0;
  //cursor+=2;
  while(cursor<input.length()){	//continue while args remain
    vector <string> pred;
    //start1 = input.find(" " , cursor);
    start1=cursor-1;
    while(input.substr(start1+1,1)==" ")start1++;
    end1 =  input.find("(" , cursor);
    name = input.substr(start1+1,(end1-start1-1));//predicate name
    //cout<<"name: "<< name<<endl;//test then insert predicate name

    pred.push_back(name);

    cursor=end1;
    endparam=input.find(")",end1);
    token=input.substr(cursor, (endparam-cursor+1));
    token.erase( remove( token.begin(), token.end(), ' ' ), token.end() );//removes whitespaces from token
    //cout<<"testing token "<<token<<endl;
    cursor=endparam+1;

    base=1;
    while(base<token.length()){ //splits token into strings

      tail=token.find(",",base);
      if(tail==-1)tail=token.find(")",base);

      parameter = token.substr(base,tail-base);
      //cout<<"parameter: "<<parameter<<endl;//insert predicate arg
      pred.push_back(parameter);
      base=tail+1;
    }

    predParams.push_back(pred);
    //cout<<"finished with predicate"<<endl;
    cursor=endparam+1;
    while(input.substr(cursor,1)==" ")cursor++;
  }
  // make rule object
  rule curRule(factName, params, operand, predParams);
  curRB.add(curRule);
  //curRB.dump();
}

void parse::addFact(string input){//working
  int space =4;
  //while(input.substr(space+1,1)==" ")space++;
  int endfact = input.find("(" , space+1);
  string factName=input.substr(space,(endfact-space));
  //cout<<"fact: "<<factName<<endl;//insert fact name

  int end1 =  input.find("(" , 0);
  int endparam=input.find(")", 0);
  string token=input.substr(end1, (endparam-end1+1));
  token.erase( remove( token.begin(), token.end(), ' ' ), token.end() );//removes whitespaces from token
  //cout<<"testing token "<<token<<endl;

  string parameter;
  vector <string> params; // vector containing facts
  int base=1;
  int tail;
  int p = 0; // contains current index for param vector
  while(base<token.length()){
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    parameter = token.substr(base,tail-base); // string containing a paramater
    //cout<<"parameter: "<<parameter;
    params.push_back(parameter); // add paramater to vector
    //cout<<" & params "<<p<<": "<<params[p]<<endl;
    p++;
    base=tail+1;
  }
  // create fact obj
  fact curFact(factName, params); // takes name then paramater vector as it's paramaters
  // add fact to KB
  curKB.add(curFact);
  //curKB.print(true);
  //cout << curKB.hash.bucket(factName) << endl;
}

void parse::dump(string input){
  int endfile = input.find("\n" , 0);
  string filename=input.substr(4,(endfile-4));
  ofstream file;
  file.open(filename);
  string f = curKB.print(false);
  file << f;
  string r = curRB.dump();
  file << r;
  cout<<"File "<<filename<<" created"<<endl;
  file.close();
}

void parse::load(string input){//working, opens file and reads it line by line
  int endfile = input.find("\n" , 0);
  string filename=input.substr(4,(endfile-4));
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
  int money = input.find("$", 0);
  // query holds the name of the rule being inferenced
  string query=input.substr(inferSpace+1,(end1-inferSpace-1));
  //cout<<"inference: "<<query<<endl;
  int endr = input.find("(", inferSpace+1);
  int endparam=input.find(")", 0);
  // token holds the name
  string token=input.substr(end1, (endparam-end1+1));
  //cout<<"testing token "<<token<<endl;

  vector <string> params; // params is a vector of parameters
  string parameter; // parameter holds the current parameter
  int base=1;
  int tail;
  inferParamNames.clear();
  while(base<token.length()){
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    parameter = token.substr(base,tail-base);
    //cout<<"parameter: "<<parameter<<endl;
    params.push_back(parameter);
    base=tail+1;
  }

  inferParamNames = params;

  string newfactname="";
  int end=input.find(")" , 0);
  int zerocheck=0;
  for(int i=end+1;i<inputSize;i++){
    if(input.substr(i,1)!=" ")zerocheck=1;
  }

  if(zerocheck==1){
    int space2=input.find(" ",end);
    while(input.substr(space2,1)==" ")space2++;
    int end2=input.find(" ",space2+1);
    if(end2==-1) end2=input.find("\n",space2);
    // newfactname stores an newname if used
    newfactname=input.substr(space2,end2-space2);
    cout<<"new fact name "<<newfactname<<"---"<<endl;
  }

  vector<vector<vector<string>>> big;
  // if query is a fact...
  if (curKB.hash.find(query) != curKB.hash.end()) {
     inferFact(query,newfactname,true);
     big.clear();
  }
  // if query is a rule...
  else if (curRB.hash.find(query) != curRB.hash.end()) {
    // split rules into indices of a vector call one by one
    vector <rule> rules_to_be_inferred;
    rules_to_be_inferred = curRB.traverseRule(query);
    for (auto it=rules_to_be_inferred.begin(); it!=rules_to_be_inferred.end(); it++){
      rule newRule = it->substitute(inferParamNames);
      //vector<vector<vector<string>>> big;
      int count = 0;
      inferRule(*it,newfactname, big, count);
      //big.clear();
    }
    // if query is neither a rule or fact...
  } else { cout<<query<<" is not a fact or rule."<<endl; }
  big.clear();
}

// void parse::removeDuplicates(fact r_fact){
//
//
// }


vector<vector<vector<string>>> parse::inferRule(rule p_rule,string newfactname,
                               vector<vector<vector<string>>> allRelationships, int count){
  int operand = p_rule.logOperator;
  cout<<endl<<"operand:"<<endl;
  cout<<operand<<endl;
  //printSomething3D(allRelationships);
  cout<<"finished"<<endl<<endl;
  //vector<vector<vector<string>>> allRelationships;
  //cout << endl << p_rule.name << endl << "---------" <<endl;
  string name;
  for (auto it = p_rule.predicates.begin(); it != p_rule.predicates.end(); it++){

   // store name of first predicate
   name = *it->begin();
   // search KB for name
   if (curKB.hash.find(name) != curKB.hash.end()) {
     // if found call infer fact
     //vector<vector<string>> relationships;
     //vector<vector<vector<string>>> allRelationships;
     allRelationships.push_back(inferFact(*it->begin(),newfactname,false));

     auto it2 = allRelationships.end()-1;
     //*it2->insert(it2->begin(), p_rule.args.begin()+1, p_rule.args.end());


     vector<string> preds;
     for(auto it3 = it->begin()+1; it3!=it->end(); it3++){
      preds.push_back(*it3);
     }
     it2->push_back(preds);

   }
   // search the RB for name
   else if (curRB.hash.find(name) != curRB.hash.end()) {
     count++;
     // get the Rule object from the hash
     auto R = *(curRB.hash.find(name));
     // call substitue to change the variables of the temporary rule
     rule newRule = R.second;
     allRelationships = inferRule(newRule,newfactname,allRelationships, count);
     vector <string> preds;
     for(auto it3 = it->begin()+1; it3!=it->end(); it3++){
          preds.push_back(*it3);
     }
     vector<vector<vector<string>>> temp;
     auto it2 = allRelationships.end()-1;
     for (int count = R.second.predicates.size(); count>0; count--) {
	if (R.second.predicates.size()<count) temp.push_back(*it2);
	it2->push_back(preds);
	it2--;
     }
     doOR(temp,newRule,count);

     /*auto it2 = allRelationships.end()-1;
     vector<string> preds;
     for(auto it3 = it->begin()+1; it3!=it->end(); it3++){
      preds.push_back(*it3);
     }
     it2->push_back(preds);*/

     //inferRule(newRule,newfactname);
     //return allRelationships;
   }
   // if name is not in RB or KB print error msg then break
   else {
     cout<<"Rule "<<p_rule.name<<" invalid predicate "<<name<<endl;
     break;
   }


   /*auto it2 = allRelationships.end()-1;
   vector<string> preds;
   for(auto it3 = it->begin()+1; it3!=it->end(); it3++){
     preds.push_back(*it3);
   }
   cout<<endl<<"Hello"<<endl;
   printSomething1D(preds);
   cout<<endl<<endl;
   */
   //it2->push_back(preds);


   // call OR/swap here
   //cout << endl << endl;
   //printSomething3D(allRelationships);

  }
  cout <<"print 3d vector recursion "<<count<<endl;
  doOR(allRelationships, p_rule, count);
  //printSomething3D(allRelationships, count);
  return allRelationships;
}

vector<vector<string>> parse::inferFact(string p_factName,string newfactname, bool doStuff){
  // this vector holds all the relations for a given fact
  vector <vector<string>> relations;
  vector<string> args;
  int inferArgs=inferParamNames.size();//#of inferred args i.e. infer parent(x,y,z) ==3
  //cout<<"vector size: "<<inferArgs<<endl;
  // loop through all facts of the same name
  auto range = curKB.hash.equal_range(p_factName);
  for (auto x = range.first; x!=range.second; x++){
    bool flag = true;
    // stores a vector of all arguments for a fact

    // loop through all the paramaters of each fact
    int paramSize=x->second.paramaters.size();


    int counter=0;
    if(inferArgs==paramSize){
      // push the vector of arguments of a fact into the larger vector of all relations
      if (flag) {
        for( auto y = x->second.paramaters.begin(); (y != x->second.paramaters.end()&&counter<inferArgs); y++){
          string curArg=inferParamNames[counter];//first args of inferred args
          if(1/*curArg.substr(0,1)=="$"*/){  //if args first char is $, it's a free variable. Proceed
          args.push_back(*y);
        }
        //else if(curArg==*y)args.push_back(*y);//check with arg of fact
        else{                           //inferred arg isn't free and doesn't match fact arg.Stop
          args.clear();
          flag = false;
          break;   //stop adding fact
        }
        counter++; //move forward to next inferred arg
        }
        relations.push_back(args);
        args.clear();
      }
    }
  }
  int count = 0;
  if (doStuff) printSomething(relations, count);
  return relations;
}

void parse::doOR(vector<vector<vector<string>>> allRelationships, rule p_rule, int count) {
   cout<<"Doing OR operation"<<endl;
   cout << p_rule.logOperator<<endl;
   cout << count <<endl;
   vector<vector<string>> result;
   unordered_map<string, vector<string>> result2;
   for (auto i = 0; i < allRelationships.size(); i++){
      int c = allRelationships[i].size();
      for (auto j = 0; j < allRelationships[i].size(); j++){
	 vector<string>vars = allRelationships[i][allRelationships[i].size()-1];
	 c--;
	 vector<string> relations;
	 int m = 0;
	 for (auto k = 0; k<allRelationships[i][j].size(); k++) {
	    for (auto m = 0; m<p_rule.args.size(); m++) {
	       if (vars[k]==p_rule.args[m]) relations.push_back(allRelationships[i][j][m]);
	    }
	 }
	 result.push_back(relations);
	 string key = "";
	 for(auto it = relations.begin(); it!=relations.end(); it++){
	    key = key + " " + *it;
	 }
    //   if (key.at(0)!='$'){
    //   result2.insert({key, relations});
    // }
      result2.insert({key, relations});
      }
   }
   for (int i = 0; i<inferParamNames.size(); i++){
      string curArg=inferParamNames[i];
      cout << "we outcheeyyaa" << endl;
      if (curArg.at(0)!='$') {
        cout << "we not outcheeyyaa" << endl;
        string n = inferParamNames[i];
        result2 = searchResults(n,result2,i);
      }
   }
   cout << result2.size() << endl;
   addFacts(result2, "newFact");
   printMap(result2);
}

void parse::addFacts(unordered_map<string, vector <string>> facts, string factName){
  cout << "Adding Facts::::" << endl;
  for (auto it = facts.begin(); it != facts.end(); it ++){
    fact newFact(factName, it->second);
    curKB.add(newFact);
    curKB.print(true);
  }

}

void parse::printMap(unordered_map<string, vector<string>> result2){
   cout << endl << endl;
   for (auto it2 = result2.begin(); it2 !=result2.end(); it2++){
     for(auto it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
       cout << *it3 << " ";
     }
     cout << endl;
   }
}

void parse::doAND(vector<vector<vector<string>>> allRelationships, rule p_rule, int count) {
   //for (auto i = 0; i < allRelationships.size(); i++){


}

void parse::printSomething1D(vector<string> oneRelation, int count) {
   for (auto it1 = oneRelation.begin(); it1 != oneRelation.end(); it1++){
      cout << *it1 << " ";
   }
   cout << endl;
}

void parse::printSomething(vector<vector<string>> relations, int count) {
   for (auto it1 = relations.begin(); it1 != relations.end(); it1++){
      printSomething1D(*it1, count);
   }
    /*  bool flag = false;
      for (auto it2 = it1->begin(); it2 != it1->end(); it2++){
	 cout << *it2 << " ";
         flag = true;
      }
      if (flag) cout<<endl;
   }*/
}

void parse::printSomething3D(vector<vector<vector<string>>> allRelations, int count) {
   for (auto it1 = allRelations.begin(); it1 != allRelations.end(); it1++){
      printSomething(*it1, count);
   }
}

/*void parse::traverseList(vector<vector<string>> relations, rule p_rule){
   for (it = inferParamNames.begin(); it != inferParamNames.end(); it++) {
      if p_rule
*/

   /*if(newfactname!=""){
     cout<<"creating facts with name "<<newfactname<<endl;

     // this double loop is reserved for printing the relationships
     cout << endl << p_factName << ":" << endl;
     for (auto it1 = relations.begin(); it1 != relations.end(); it1++){
       auto it0 = inferParamNames.begin();
       for (auto it2 = it1->begin(); it2 != it1->end(); it2++){
	 cout << *it0 << ": " << *it2;
	 args.push_back(*it2);

	 if (it2 != it1->end()-1) cout << " ";
	 it0++;
       }
       cout << endl;
       fact newFact(newfactname,args);
       curKB.add(newFact);
       args.clear();
     }
   }
   else{
     // this double loop is reserved for printing the relationships
     cout << endl << p_factName << ":" << endl;
     for (auto it1 = relations.begin(); it1 != relations.end(); it1++){
       auto it0 = inferParamNames.begin();
       for (auto it2 = it1->begin(); it2 != it1->end(); it2++){
	 cout << *it0 << ": " << *it2;
	 if (it2 != it1->end()-1) cout << " ";
	 it0++;
       cout << endl;
     }
   }
}*/

void parse::drop(string input){
  int end = input.find("\n",0);
  string name=input.substr(4,end-4);
  curKB.drop(name);
  curRB.drop(name);
}

unordered_map<string, vector<string>> parse::searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position){
  unordered_map<string, vector<string>> result2;
  vector<vector<string>> result;
  string key = "";
  for (auto it = searchMap.begin(); it != searchMap.end(); it++){
    auto strings = it->second;
    if (strings[position] == searchName){
      result.push_back(it->second);
    }
  }
  for (auto it = result.begin(); it != result.end(); it++){
    for (auto it2 = it->begin(); it2 != it->end(); it2 ++){
      key = key + *it2;
    }
    result2.insert({key, *it});
  }
  return result2;
}

int main(){

  parse p;
  cout<< "enter a command...-1 to exit"<<endl;
  string input;
  p.load("loadinput2.sri");

  while(getline(cin,input)&&input!="-1"){
    p.checkLine(input);
  }
  return 0;
}
