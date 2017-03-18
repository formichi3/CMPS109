//#include "../fact/Fact_H.h"
#include "parsenew.h"
#include <unordered_map>
#include <typeinfo>

using namespace std;


vector<vector<string>> parse::checkLine(string input){
  inputSize=input.size();
  vector<vector<string>> send;
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
  else if(command=="INFE"||command=="infe")send=infer(input);//parse needs work
  else cout<<"please enter valid command"<<endl;
 return send;  
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
  cout<<endl;
}//end of load parsing

vector<vector<string>> parse::infer(string input){      //working
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
  token.erase( remove( token.begin(), token.end(), ' ' ), token.end() );//removes whitespaces from token
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

  newfactname="";
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

  for (int i=0;i<inferParamNames.size();i++){
     cout<<inferParamNames[i]<<" ";
  }
  cout<<endl;

  vector<vector<string>> answer;
  vector<vector<string>> finVec;
  vector<vector<vector<string>>> bigAnswer;
  vector<vector<vector<string>>> big;
  unordered_map<string, vector<string>> mapResult;
  bool isRule = true;
  bool isAND = false;
  // if query is a fact...
  if (curKB.hash.find(query) != curKB.hash.end()) {
     answer=inferFact(query,newfactname,true);
     bigAnswer.push_back(answer);
     //printSomething(answer,0);
     answer.clear();
     isRule=false;
     //isAND=false;
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
      //doOR(big, p_rule, count)
      answer = inferRule(*it,newfactname, big, count);
      bigAnswer.push_back(answer);
      answer.clear();
      if (it->logOperator==1) isAND = true;
      //printSomething(answer,0);
      //big.clear();
    }
    //printSomething3D(bigAnswer,0);
    // if query is neither a rule or fact...
  } else {
     cout<<query<<" is not a fact or rule."<<endl;
  }
  mapResult=vector3DToMap(bigAnswer,isAND);

  /*cout<<"PRE VEC"<<endl;
  printSomething3D(bigAnswer,0);
  cout<<endl;
  cout<<"PRE MAP"<<endl;
  printMap(mapResult);
  cout<<"here"<<endl;*/

  unordered_map<string, vector<string>> fin;
  // for specified names
  if (isRule) {
  for (int sub = 0; sub<inferParamNames.size(); sub++){
      string curArg=inferParamNames[sub];
      if (curArg.at(0)!='$') {
        //cout<<"in if"<<endl;
	string n = inferParamNames[sub];
        mapResult = searchResults(n,mapResult,sub);
      }
  }
  }

  cout<<"ANSWER BELOW";
  printMap(mapResult);

  // BUGGY
  // adds facts to KB if specified
  if (newfactname != "") {
     cout<<"Creating facts with the name: "<<newfactname<<endl;
     addFacts(mapResult, newfactname);
  }
  vector<vector<string>> send;
  send=mapToVector(mapResult);
  //printSomething3D(bigAnswer,0);
  bigAnswer.clear();
  mapResult.clear();
  cout<<endl;
  return send;
}


vector<vector<string>> parse::inferRule(rule p_rule,string newfactname,
                              vector<vector<vector<string>>> allRelationships, int count){
  int operand = p_rule.logOperator;
  //cout<<endl<<"operand:"<<endl;
  //cout<<operand<<endl;
  //printSomething3D(allRelationships);
  //cout<<"finished"<<endl<<endl;
  //vector<vector<vector<string>>> allRelationships;
  //cout << endl << p_rule.name << endl << "---------" <<endl;
  string name;
  for (auto it = p_rule.predicates.begin(); it != p_rule.predicates.end(); it++){

   // store name predicate
   name = *it->begin();
   // search KB for name
   if (curKB.hash.find(name) != curKB.hash.end()) {
     // if found call infer fact
     //vector<vector<string>> relationships;
     //vector<vector<vector<string>>> allRelationships;
     //----------------------------
     int threadNum=ORThreads.size()+1;
     vector< vector<string> > returned;
     auto factThread = async(bind(&parse::inferFact, this, *it->begin(), newfactname,false));

     cout << "Thread number "<<threadNum<<" created for "<<name<<endl;
     shared_future < vector < vector <string> > > outThreads = factThread.share();
     ORThreads.push_back(outThreads);
     returned = ORThreads[ORThreads.size()-1].get();
     cout << "Thread "<<threadNum<<  " is finished with "<<name<<endl;
     allRelationships.push_back(returned);

     //--------------------------------


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
     //cout<<endl<<"here1"<<endl;
     vector<vector<vector<string>>> temp;
     auto it2 = allRelationships.end()-1;
     for (int count = R.second.predicates.size(); count>0; count--) {
        if (R.second.predicates.size()<count) temp.push_back(*it2);
        /*cout<<"*it2"<<endl;
	printSomething(*it2,0);
	cout<<endl;*/
	//it2->push_back(preds);
        it2--;
     }
     /*
     cout<<endl<<"temp"<<endl;
     printSomething3D(allRelationships,0);
     cout<<endl<<"DONE"<<endl;
     */
     vector<vector<string>> returned;
     //----------------------------
     int threadNum=ORThreads.size()+1;
     auto ruleThread = async(bind(&parse::inferRule, this, newRule, newfactname, temp, count));
     cout << "Thread number "<<threadNum<<" created for "<<newRule.name<<endl;
     shared_future < vector < vector <string> > > outThreads = ruleThread.share();
     ORThreads.push_back(outThreads);
     returned = ORThreads[ORThreads.size()-1].get();
     cout << "Thread "<<threadNum<<  " is finished with "<<newRule.name<<endl;
     //----------------------------

     allRelationships.push_back(returned);

     /*cout<<endl<<"allR in recursion"<<endl;
     printSomething3D(allRelationships,0);
     cout<<endl<<"DONE"<<endl;
     cout<<endl<<"inferRule return in recursion"<<endl;
     printSomething(returned,0);
     cout<<endl<<"DONE"<<endl;
     */

     vector <string> preds;
     for(auto it3 = it->begin()+1; it3!=it->end(); it3++){
          preds.push_back(*it3);
     }
     //vector<vector<vector<string>>> temp;
     /*auto it2 = allRelationships.end()-1;
     for (int count = R.second.predicates.size(); count>0; count--) {
	if (R.second.predicates.size()<count) temp.push_back(*it2);
	//it2->push_back(preds);
	it2--;
     }*/
     //allRelationships.push_back(doOR(temp,newRule,count));
     it2 = allRelationships.end()-1;
     it2->push_back(preds);

   }
   // if name is not in RB or KB print error msg then break
   else {
     cout<<"Rule "<<p_rule.name<<" invalid predicate "<<name<<endl;
     //break;
   }

  }
  //cout <<"print 3d vector recursion "<<count<<endl;
  vector<vector<string>> printRelationships;
  printRelationships.clear();
  if (operand==0) {
     // allRelationships.clear();
     printRelationships=(doOR(allRelationships, p_rule, count));
  } else {
     printRelationships=(doAND(allRelationships, p_rule, count,true));  //printSomething3D(allRelationships, count);
  }
  //cout<<endl<<"ALL RELATIONSHIPS"<<endl;
  //printSomething3D(allRelationships, 0);
  /*cout<<endl<<"PRINT RELATIONSHIPS"<<endl;
  printSomething(printRelationships, 0);
  cout<<"Done"<<endl;*/
  return printRelationships;
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
    // 5stores a vector of all arguments for a fact

    // loop through all the paramaters of each fact
    int paramSize=x->second.paramaters.size();


    int counter=0;
    //if(inferArgs==paramSize){
      // push the vector of arguments of a fact into the larger vector of all relations
      if (flag) {
        for( auto y = x->second.paramaters.begin(); (y != x->second.paramaters.end()&&counter<inferArgs); y++){
          string curArg=inferParamNames[counter];//first args of inferred args
          if (doStuff) {
	     if(curArg.substr(0,1)=="$"){  //if args first char is $, it's a free variable. Proceed
	       args.push_back(*y);
	     }
	     else if(curArg==*y)args.push_back(*y);//check with arg of fact
	     else{                           //inferred arg isn't free and doesn't match fact arg.Stop
	       args.clear();
	       flag = false;
	       break;   //stop adding fact
	     }
	  } else {
	     args.push_back(*y);
	  }
          counter++; //move forward to next inferred arg
        }
        relations.push_back(args);
        args.clear();
      }
    //}
  }
  int count = 0;
  //if (doStuff) printSomething(relations, count);
  return relations;
}

vector<vector<string>> parse::doOR(vector<vector<vector<string>>> allRelationships, rule p_rule, int count) {
   cout<<"Doing OR operation"<<endl;
   //cout << p_rule.logOperator<<endl;
   //cout << count <<endl;

   //cout<<endl<<"or passed vector"<<endl;
   //printSomething3D(allRelationships,0);
   //cout<<endl<<"done"<<endl;

   vector<vector<string>> empty;

   bool allVars=true;

   vector<vector<string>> result;
   result.clear();
   unordered_map<string, vector<string>> result2;
   for (auto i = 0; i < allRelationships.size(); i++){
      int c = allRelationships[i].size();
      for (auto j = 0; j < allRelationships[i].size(); j++){
	 vector<string>vars = allRelationships[i][allRelationships[i].size()-1];
	 c--;
	 vector<string> relations;
	 int m = 0;
	 int varCount=0;
	 for (auto k = 0; k<allRelationships[i][j].size(); k++) {
	    for (auto m = 0; m<p_rule.args.size(); m++) {
	       if (vars[k]==p_rule.args[m]) {
		  relations.push_back(allRelationships[i][j][m]);
		  varCount++;
	       }
	    }
	 }

	 if (varCount != p_rule.args.size()){
	    cout<<"Free Variable Found"<<endl;
	    cout<<"varCount:"<<varCount<<" p_rule.args:"<<(p_rule.args.size())<<endl;
	    return empty;
	 }

	 //result.push_back(relations);
	 string key = "";
	 for(auto it = relations.begin(); it!=relations.end(); it++){
	    key = key + " " + *it;
	 }
	 //cout << "Key at 0: " << key <<endl;
         if (key.at(1)!='$'){
	    result.push_back(relations);
	    result2.insert({key, relations});
	 }
      }
   }

   //OLD TARGET FACT CODE
   /*for (int i = 0; i<inferParamNames.size(); i++){
      string curArg=inferParamNames[i];
      if (curArg.at(0)!='$') {
        string n = inferParamNames[i];
        result2 = searchResults(n,result2,i);
      }
   }*/
   string s = newfactname;
   // BUGGY
   //if (newfactname != "") {addFacts(result2, newfactname);}
   /*cout<<endl<<"or result2"<<endl;
   printMap(result2);
   cout<<endl<<"or result"<<endl;
   printSomething(result, 0);
   cout<<endl<<endl;*/
   result = mapToVector(result2);
   return result;
}

unordered_map<string,vector<string>> parse::vector3DToMap(vector<vector<vector<string>>> vec, bool AND) {
   unordered_map<string,vector<string>> u_map;
   /*cout<<"vec to map"<<endl;
   printSomething3D(vec,0);
   cout<<"done"<<endl;*/
   //cout<<"sizes:"<<vec.size()<<vec[0].size()<<endl;
   for (int i=0; i<vec.size(); i++){
      for (int j=0; j<vec[i].size(); j++){
	 bool print=true;
	 string key = "";
	 //vector <string> rel = vec[i][j];
	 for (int k=0; k<vec[i][j].size(); k++){
	    if (vec[i][j][k]=="") print=false;
	    key = key + vec[i][j][k];
	 }
	 //cout<<"-----------"<<endl;
	 //if (vec[i][j]!=vec[i][vec[i].size()-1]) printSomething1D(vec[i][j],0);
	 //cout<<"-----------"<<endl;
	 /*if (!nAND) {
	    if ((vec[i][j]!=vec[i][vec[i].size()-1])) u_map.insert({key, vec[i][j]});
         } else {
	    u_map.insert({key, vec[i][j]});
	 }*/
	 u_map.insert({key, vec[i][j]});
	 //if (!AND) u_map.insert({key, vec[i][j]});
	 //else if ((vec[i][j]!=vec[i][vec[i].size()-1])) u_map.insert({key, vec[i][j]});
      }
   }

   //cout<<"Print u_map"<<endl;
   //printMap(u_map);

   return u_map;
}


/*string parse::getKey(vector<vector<string>> vec) {
   string key = "";
   for (int i=0; i<vec.size(); i++){
      for (int j=0; j<vec[i].size(); j++){
	 key = vec[i][j] + " ";
      }
   }
   return key;
}*/


vector<vector<string>> parse::mapToVector(unordered_map <string,vector<string>> relations) {
   vector<vector<string>> result;
   for (auto it = relations.begin(); it != relations.end(); it ++){
      result.push_back(it->second);
   }
   return result;
}

vector<vector<string>> parse::mapToVector2(map <string,vector<string>> relations) {
   vector<vector<string>> result;
   for (auto it = relations.begin(); it != relations.end(); it ++){
      result.push_back(it->second);
   }
   return result;
}

void parse::addFacts(unordered_map <string,vector<string>> facts, string factName){
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

void parse::printMap2(map<string, vector<string>> result2){
   cout << endl << endl;
   for (auto it2 = result2.begin(); it2 !=result2.end(); it2++){
     for(auto it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
       cout << *it3 << " ";
     }
     cout << endl;
   }
}


vector<vector<string>> parse::doAND(vector<vector<vector<string>>> allRelationships, rule p_rule, int count, bool first) {
   if (first) predicates = p_rule.predicates.size();
   cout<<"Doing AND operation"<<endl;
   //cout << p_rule.logOperator<<endl;
   //cout << count <<endl;
   /*
   cout<<endl<<"passed vector"<<endl;
   printSomething3D(allRelationships,0);
   cout<<endl<<endl;
   */
   vector<vector<string>> ans;
   vector<vector<string>> result;
   vector<vector<vector<string>>> bigResult;
   map<string,vector<string>> mapResult;


   //SEG FAULT CASES
   //if a pred is empty
   for (int checkEmpty=0; checkEmpty<p_rule.predicates.size(); checkEmpty++) {
      if (allRelationships[checkEmpty].empty()){
	 cout<<"No answer, predicate "<<checkEmpty<<" returned nothing"<<endl;
	 return ans;
      }
   }
   //if there is only one pred
   if (p_rule.predicates.size()<2) {
      cout<<"Cannot do binary operation with less than two predicates, use OR if you want to do this"<<endl;
      return ans;
   }


   result.clear();
   unordered_map<string, vector<string>> result2;
   for (auto i = 0; i < allRelationships.size()-1; i++){
      int c = allRelationships[i].size();
      bool flag = false;
      //int count =0;
      // loop through middle vector of vectors
      for (auto j = 0; j < allRelationships[i].size(); j++){
         vector<string>vars = allRelationships[i][allRelationships[i].size()-1];
         c--;
         int m = 0;
	 // loop through innermost vector of strings
	 for (auto k = 0; k<allRelationships[i][j].size(); k++) {
            //cout<<allRelationships[i][allRelationships[i].size()-1][k]<<endl;
            // loop through predicates
	    for (auto z=1; (i+z)<allRelationships.size(); z++) {
	       //cout<<"Z loop " <<(z)<<endl;
	       //bool flag = false;
	       // loop through variables in each predicate vector
	       //int count=0;
	       for (auto h=0; h<allRelationships[i][j].size(); h++){
		  // check if a variable equals one in the following predicates
		  int count=0;
		  if(allRelationships[i][allRelationships[i].size()-1][k]==allRelationships[i+z][allRelationships[i+z].size()-1][h]){
		     /*
		     cout<<allRelationships[i][allRelationships[i].size()-1][k]
		     <<" pred:"<<i<<" elem:"<<k<<" equals "
		     <<allRelationships[i+z][allRelationships[i+z].size()-1][h]
		     <<" pred:"<<i+z<<" elem:"<<h<<endl;
		     */
		     // if so loop through the facts per variable by going through the columns at the first predicate
		     //bool print = false;

		     for (auto a=0; a<allRelationships[i].size(); a++) {
			//result2=(searchResults(allRelations[i][a][k], someMap, h);
			bool print = false;
			bool print1 = false;
			// loop through the facts per variable at the other predicate
			vector<string> relations;
			for (auto b=0; b<allRelationships[i+z].size(); b++) {
			   if (allRelationships[i][a][k]==allRelationships[i+z][b][h]) {
			      //cout<<allRelationships[i][a][k]<<" pred:"<<i<<" col:"<<a<<" elem:"<<k<<
			      //" equals 2 "<<allRelationships[i+z][b][h]<<" pred:"<<i+z<<" col:"<<b<<" elem:"<<h<<endl;
			      //relations.push_back(allRelationships[i][a][k]);
			      relations.push_back(allRelationships[i][a][0]);
			      for (int c=0; c<allRelationships[i+z][b].size(); c++){
				 //relations.push_back(allRelationships[i][a][0]);
				 relations.push_back(allRelationships[i+z][b][c]);
				 //for(int p=0; p<allRelationships.size(); p++){
				   // if allRelationshi

				 //cout<<"GETTING PUSHED BACK: "<<allRelationships[i+z][b][c]<<endl;
				 //relations.push_back(allRelationships[i][a][0]);
			      }

			      /*
			      auto it =relations.begin();
			      relations.insert(it,allRelationships[i][a][0]);
			      */

			      //WORKING to done
			      //relations=(allRelationships[i+z][b]);
			      //cout<<"relations pre"<<endl;
			      //printSomething1D(relations,0);
			      //int count=0;
			      //IMPORTANT
			      /*
			      cout<<"RELATIONS"<<endl;
			      printSomething1D(relations,0);
			      cout<<"DONE"<<endl;
			      auto it = relations.begin();
			      relations.insert(it,allRelationships[i][a][0]);
			      */
			      //cout<<"relations post"<<endl;
			      //printSomething1D(relations,0);
			      //DONE

			      //ALSO IMPORTANT (trying to solve predicate problem)
			      /*for (int u = 0; u<allRelationships.size()-1; u++){
				 cout<<endl<<"count:"<<count<<"element:"<<allRelationships[u][a][0]<<endl;
				 //if (relations==allRelationships
				 relations.insert(it,allRelationships[u][a][0]);
				 //relations.push_back(allRelationships[u][a][0]);
			         count++;
			      }*/

			      //cout<<"out of loop"<<endl;
			      flag = true;
			      print = true;
			      print1 = true;
			   }
			   if (print) {
			      count++;
			      //cout<<"how many times"<<endl;
			      result.push_back(relations);
			      string key = "";
			      for(auto it2 = relations.begin(); it2!=relations.end(); it2++){
          		         key = key + " " + *it2;
         		      }
			      mapResult.insert({key,relations});
			   }
			   relations.clear();
			   print = false;
			}
			//cout<<endl<<"1"<<endl;
			//if (print1) bigResult.push_back(result);
			//print1 = false;
			//if (flag) break;
		     }
		     /*cout<<endl<<"LOOP VARS"<<endl;
		     cout<<"i:"<<i<<" j:"<<j<<" k:"<<k<<" z:"<<z<<" h:"<<h<<" count:"<<count<<endl;//<<" a:"<<a<<" b:"<<b<<endl;
		     cout<<"LOOP VARS DONEZO"<<endl;
		     */
		     //auto it3=result2.end();
		     //auto it4=it3->second;
		     //result=mapToVector2(result2);
		     //bigResult.push_back(result);
		     for(int co=0;co<(count)&&i!=0;co++){
		        //cout<<"COUNT:"<<count<<endl;
			//cout<<"K:"<<k<<endl;
			//cout<<"VEC TO BE ERASED"<<endl;
			//printSomething1D(*(result.begin()),0);
			//cout<<"DONE VEC ERASE"<<endl;
			result.erase(result.begin());
			result.shrink_to_fit();
		        //cout<<"AM I HERE?"<<endl;
		     }
		     //result=mapToVector2(mapResult);
		     if (!first) {
			for (int co2=0; co2<(h*count); co2++){
			   //cout<<"VEC TO BE ERASED"<<endl;
			   //printSomething1D(*(result.begin()),0);
			   //cout<<"DONE VEC ERASE"<<endl;
			   result.erase(result.begin());
			   result.shrink_to_fit();
			}
		     }
		     result.shrink_to_fit();
		     //for (int co2=0; co2<h; co++){
		     bigResult.push_back(result);
		     bigResult.shrink_to_fit();
		     //}
		     //cout<<"What about here??"<<endl;
		     /*string key = "";
		     for (int ab = 0; ab<bigResult.size(); ab++){
			for (int bc = 0; bc<bigResult[a][b].size(); bc++) {
			   key = key + " " + *it3
			}
			bigResult2.insert({key,
		     }*/
		     //cout<<endl<<"2"<<endl;
		     //if (flag) break;
		  }
		  //cout<<endl<<"3"<<endl;
		  //if (flag) break;
		  //bigResult.push_back(result);
	       }
	       //cout<<endl<<"4"<<endl;
	       //if (flag) break;

	    }
	    //cout<<endl<<"5"<<endl;
            //OLD adds everything
            //cout<<endl<<"adding "<<allRelationships[i][j][k]<<endl;
	    //relations.push_back(allRelationships[i][j][k]);

	 }
	 //bigResult.push_back(result);
	 if (flag) break;

	 //cout<<"HERE"<<endl;
         /*result.push_back(relations);
         string key = "";
         for(auto it = relations.begin(); it!=relations.end(); it++){
            key = key + " " + *it;
         }
	 cout<<"Here 4"<<endl;
         //cout << "Key at 0: " << key <<endl;
         if (key.at(1)!='$'){
            result.push_back(relations);
            result2.insert({key, relations});
         }
	 cout<<"Here 6"<<endl;*/

      }
      //bigResult.push_back(result);
      //if (flag) break;
      //cout<<"Here 5"<<endl;
   }
   //cout<<"Here 3"<<endl;
   //result = mapToVector(result2);
   /*for (int i = 0; i<inferParamNames.size(); i++){
      string curArg=inferParamNames[i];
      if (curArg.at(0)!='$') {
        string n = inferParamNames[i];
        for (int j=0; j<result.size(); j++) {
	   vector<string> vars = result.size(
	result2 = searchResults(n,result2,i);
      }
   }*/
   //string s = newfactname;
   //if (newfactname != "") {cout<<"right"<<endl; addFacts(result2, newfactname);}

   /*
   cout<<endl<<"mapResult"<<endl;
   printMap2(mapResult);
   cout<<endl<<endl;
   */

   //result = mapToVector(result2);

   // PRINTS MAP
   //cout<<endl<<"And map result below";
   //printMap(result2);
   //cout<<endl<<"And map result above"<<endl<<endl;

   //result = mapToVector(result2);

   /*
   cout<<endl<<"bigResult pre"<<endl;
   printSomething3D(bigResult,0);
   cout<<endl<<endl<<endl;
   */

   vector<vector<string>> finalResult=bigResult[0];
   //result=bigResult[0];
   //IMPORTANT FOR MULTIPLE PREDICATES

   /*
   cout<<endl<<"finalResult pre"<<endl;
   printSomething(finalResult,0);
   cout<<endl<<endl<<endl;
   */

   //vector<vector<string>> rmNonVars;
   //rmNonVars=getSolutionAND(finalResult,p_rule);
   if (predicates>2) {
      predicates--;
      //cout<<endl<<"BigResult"<<endl;
      //printSomething3D(bigResult,0);
      //cout<<endl<<endl<<endl;
      //bigResult=
      finalResult=doAND(bigResult,p_rule,0,false);
      finalResult.shrink_to_fit();
      //rmNonVars=
   }

   /*
   cout<<endl<<"bigResult post"<<endl;
   printSomething3D(bigResult,0);
   cout<<endl<<endl<<endl;

   cout<<endl<<"finalResult post"<<endl;
   printSomething(finalResult,0);
   cout<<endl<<endl<<endl;
   */

   vector<vector<string>> rmNonVars;
   rmNonVars=getSolutionAND(finalResult,p_rule);
   rmNonVars.shrink_to_fit();
   //fuck=doOR(bigResult,p_rule,0);
   //result=doOR(bigResult,p_rule,0);
   /*vector<vector<string>> finalResult;
   for (int i = 0; i<p_rule.predicates.size(); i++){
      string curArg=p_rule.predicates[i];
      for (int a=0; a<result.size(); a++) {
	 vector<vector<string>> miniFinalResult;
	 for (int b=0; b<result[i].size(); b++) {
	    if (curArg==result[a][b]) {
	       // loop through columns above found
	       //for (int c=0; c<
	       miniFinalResult.push_back(result[a][b]);
    */

      /*if (curArg.at(0)!='$') {
        string n = inferParamNames[i];
        for (int j=0; j<result.size(); j++) {
           vector<string> vars = result.size(
        result2 = searchResults(n,result2,i);
      }
   }*/

   /*
   cout<<"rmNonVars"<<endl;
   printSomething(rmNonVars,0);
   cout<<"done"<<endl;

   cout<<"finalResult"<<endl;
   printSomething(finalResult,0);
   cout<<"done"<<endl;
   */

   //vector<vector<string>> ans;
   if (first) {
      rmNonVars.pop_back();
      ans = rmNonVars;
      //rmNonVars.pop_back();
      /*cout<<"rmNonVars"<<endl;
      printSomething(rmNonVars,0);
      cout<<"done"<<endl;*/
   } else {
      ans = finalResult;
   }
   return ans;
}

vector<vector<string>> parse::getSolutionAND(vector<vector<string>> result, rule p_rule){
   vector<vector<string>> finalResult;
   vector<vector<string>> actualFinalResult;
   vector<string> push;
   vector<string> push2;
   vector<string> vars;
   //bool print=false;
   vars = result[result.size()-1];
   for (int p=0; p<p_rule.args.size(); p++) {
      for (int v=0; v<vars.size(); v++) {
	 bool print =false;
	 if (p_rule.args[p]==vars[v]){
	    for (int r=0; r<result.size(); r++){
	       push.push_back(result[r][v]);
	    }
	    print=true;
	 }
	 if (print) finalResult.push_back(push);
         push.clear();
      }
   }

   for (int c=0; c<finalResult[0].size(); c++) {
      for (int r=0; r<finalResult.size(); r++) {
	 if (finalResult[r][c].at(0)!='$'){
	    //cout<<"!$"<<endl;
	    push2.push_back(finalResult[r][c]);
	 }
      }
      actualFinalResult.push_back(push2);
      push2.clear();
   }

   //cout<<"ANDthing result"<<endl;
   //printSomething(finalResult,0);

   return actualFinalResult;
}

//vector<vector<string>> parse::vectorSwapDimensions(vector<vector<string>> result) {


//}


   /*for(int i=0; i<result.size(); i++){
      vars = result[result.size()-1];
      for(int k=0; k<p_rule.args.size(); k++){
	 for(int j=0; j<result[i].size(); j++){
	    if (p_rule.args[k]==vars[j]) {
	       for (int a=0; a<result.size(); a++){
	          if (result[a][j].at(0) != '$')
		  push.push_back(result[a][j]);
	       }
	       cout<<"Push Vector"<<endl;
	       printSomething1D(push,0);
	       flag=true;
	    }
	    if (flag) break;
	 }
         finalResult.push_back(push);
      }
   }
   return finalResult;
   */

  /*
   vars = result[result.size()-1];
   // loop through predicates
   for (int k=0; k<p_rule.args.size(); k++){
      // loop through rows of vectors
      for (int h=0; h<result.size(); h++){
         // if a current arg in the rule does equal a var in the vector
	 if (p_rule.args[k]==vars[h])
	    //((p_rule.args[k]!=vars[h])&&(p_rule.args[k+1]!=vars[h])&&(p_rule.args[k+1]!=vars[h])){
            cout<<"var "<<vars[h]<<" found"<<endl;
            //for (auto it=
            for (int a=0; a<result.size(); a++) {
               //cout<<"ERASE->>>>"<<*(result[a].begin()+h);
               vector[a].
	       result[a].erase(result[a].begin()+h);
	       //result[a].size()=(result[a].size())-1;
            }
	    break;
         }
      }
   }
   return result;

}*/

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
}

void parse::printSomething3D(vector<vector<vector<string>>> allRelations, int count) {
   for (auto it1 = allRelations.begin(); it1 != allRelations.end(); it1++){
      cout<<"new 2d vector"<<endl;
      printSomething(*it1, count);
   }
}


void parse::drop(string input){
  int end = input.find("\n",0);
  string name=input.substr(4,end-4);
  curKB.drop(name);
  curRB.drop(name);
}

unordered_map<string, vector<string>> parse::searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position){
//vector<vector<string>> parse::searchResults(string searchName, unordered_map<string, vector<string>> searchMap, int position){
  //cout<<"Passed Map";
  //printMap(searchMap);


  unordered_map<string, vector<string>> result2;
  vector<vector<string>> result;
  string key = "";
  for (auto it = searchMap.begin(); it != searchMap.end(); it++){
    //cout<<"sup"<<endl;
    vector<string> strings = it->second;
    //cout<<"string:"<<strings[0]<<endl;
    //cout<<"position:"<<position<<endl;
    //cout<<"string:"<<strings[0]<<endl;
    if (strings[position] == searchName){
      //cout<<"yo1"<<endl;
      result.push_back(it->second);
      //cout<<"yo"<<endl;
      //cout<<"pushing back: "<<(it.second);
    }
  }
  //return result;

  for (auto it = result.begin(); it != result.end(); it++){
    for (auto it2 = it->begin(); it2 != it->end(); it2 ++){
      key = key + *it2;
    }
    result2.insert({key, *it});
  }
  return result2;
}


/*vector<string> parse::searchResultsVector(string searchName, vector<vector<string>> searchVector, int position) {
   vector<string> relation;
   for (int i=0; i<searchVector.size(); i++) {
      for (int j=0; j<searchVector[i].size(); j++) {
	 if (searchVector[i][j] == searchName) {
            //relation = searchVector[i][j];
	    return relation;
	 }
      }
   }
}*/

// int main(){
//
//   parse p;
//   cout<< "enter a command...-1 to exit"<<endl;
//   string input;
//   p.load("loadtest.sri");
//   while(getline(cin,input)&&input!="-1"){
//      p.checkLine(input);
//   }
//   return 0;
// }
