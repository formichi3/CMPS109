//#include "../fact/Fact_H.h"
#include "parsenew.h"
//#include <unordered_map>

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


// void parse::make_fact(rule p_rule){ // makes fact out of rule made of only facts
//   vector<vector<string>> new_fact;
//   int inferArgs = inferParamNames.size(); //#number of args in rule
//   if (logOperator == 0){ //OR operator
//     for(int i = 0; i < inferArgs; i++){
//       new_fact.push_back(p_rule.predicates[i]);
//     }
//     return new_fact;
//   } else if(logOperator == 1){
//     vector<string>argsv;//vector holding the args in rule
//     vector<string>temp_vec;
//     for (int i = 0; i < inferArgs; i++) {
//       for(int j = 0; j < inferArgs; j++)
//         if (p_rule.args[i] == p_rule.predicates[i].parameters[j]){
//           argsv[i] = i; //creates and intialies vector for all args that match predicate params
//           cout<< argsv[i]<< "HIII" << endl.
//         }
//         thread t(pipeline(p_rule.predicates[i]));
//     }
//   }
// }
//
// void parse::pipeline(vector<strings>preds){
//
// }
//
//     int paramSize=p_rule.predicates.paramaters.size();
//     string args1 = p_rule.args;
//     string args2 = p_rule.args;
//     for(int i = 0; i < paramSize; i++) {
//       if (p_rule.predicates[i].parameters[i] == args1)
//         thread t(pipeline(p_rule.predicates[i+1].parametes))
//       }
//
//     }
//     // loop through all facts of the same name
//     auto range = curKB.hash.equal_range(p_factName);
//     for (auto x = range.first; x!=range.second; x++){
//       bool flag = true;
//       // stores a vector of all arguments for a fact
//
//       // loop through all the paramaters of each fact
//       int paramSize=x->second.paramaters.size();
//
//
//       int counter=0;
//       if(inferArgs==paramSize){
//         // push the vector of arguments of a fact into the larger vector of all relations
//         if (flag) {
//           for( auto y = x->second.paramaters.begin(); (y != x->second.paramaters.end()&&counter<inferArgs); y++){
//             string curArg=inferParamNames[counter];//first args of inferred args
//             if(curArg.substr(0,1)=="$"){  //if args first char is $, it's a free variable. Proceed
//             args.push_back(*y);
//           }
//           else if(curArg==*y)args.push_back(*y);//check with arg of fact
//           else{                           //inferred arg isn't free and doesn't match fact arg.Stop
//             args.clear();
//             flag = false;
//             break;   //stop adding fact
//           }
//           counter++; //move forward to next inferred arg
//           }
//           relations.push_back(args);
//           args.clear();
//         }
//       }
//     }
//     int count = 0;
//     if (doStuff) printSomething(relations, count);
//     return relations;
//   }
// }
//
//



// vector<string> parse::compare_params(rule p_rule){
//   vector<string> f_fact;
//   vector<string>order;
//   vector<string> c_rule = rule_params(p_rule);
//   int inferArgs = p_rule.predicates.size();
//   for (int i =0; i < inferArgs;i++){
//     if (p_rule.predicates[i] == ){
//       //thread t(make_fact(p_rule.predicates[i]));
//       cout<<"thread here" <<endl;
//     } else {
//       f_fact = fact_params(p_rule.predicates[i]);
//       for (int j = 0; j < inferArgs; j++){
//         if (c_rule[i] == f_fact[j]){
//           order[i] = c_rule[i];
//         }
//       }
//     }
//   }
//   return order;
// }

//   int inferArgs = p_rule.predicates.size();
//   for(int i = 0; i < inferArgs){
//     if(p_rule.predicates[i] == fact){
//       fatt[i] = fact_params(p_rule.predicates[i]);
//     } else if (p_rule.predicates[i] == rule){
//       rool[i] = rule_params(p_rule.predicates[i]);
//     }
//     for (int j = 0; j < inferArgs; j++){
//       if (p_rule.predicates[i].args[j] == rool[j] || p_rule.predicates[i].args[j] == fatt[j]){
//         order[j] = 1; // if the rule argument is the same as the fact or rule parameter
//       }  else {
//         order[j] = 0;
//       }
//     }
//   }
// }
//

//
//   vector <string> rule_params;
//   vector <string> fact_params;
//   int base = 1;
//   int tail;
//   bool general;
//   string parameter = p_rule.args;
//   int end1 = p_rule.args.find("(",0);
//   int endparam = p_rule.args.find(")", 0);
//   string r_params = p_rule.args.substring(end1, (endparam-end+1));
//   while (base<token.length()){
//     tail = r_params.find(",",base);
//     if(tail == -1) tail = token.find(")",base);
//     parameter = r_params.substr(base,tail-base);
//     if(parameter[0] == '$' || parameter[1] == '$') general =true; //checks if parameter is general or specific to name
//     else general = false;
//     cout << "parameter: "<<parameter<<endl;
//     params.push_back(parameter);
//     base = tail+1;
//   }
// }



//
// vector<string>parse::fact_params(string a_fact){
//   // loop through all facts of the same name
//   auto range = curKB.hash.equal_range(a_fact);
//   for (auto x = range.first; x!=range.second; x++){
//
//
//
//   string p_fact = curKB.hash.find(a_fact).paramaters;
//   vector<string> fa_params;
//   for (int i = 0; i < p_fact.paramaters.size(); i++){
//     string current = fa_params[i];
//     int end1 = current.find("(",0);
//     int endparam = current.find(")", 0);
//     string f_params = current.substr(end1, (endparam-end1+1));
//     int base = 1;
//     int tail;
//     string parm;
//     while(base<f_params.length()) {
//       tail = f_params.find(",",base);
//       if(tail == -1) tail = f_params.find(")",base);
//       parm = f_params.substr(base,tail-base);
//       cout <<"f_params: "<< parm<<endl;
//       fa_params.push_back(parm);
//       base = tail+1;
//     }
//   }
//   return fa_params;
//
// }

// bool parse::isFact(string name){
//   if(curKB.hash.find(fact_name) != curKB.hash.end()){
//     return true;
//   } else if(curRB.hash.find(rule_name) != curRB.hash.end()){
//     return false;
//   }
// }


//I was writing this as if it were a rule that was made of two facts and would create a new fact so if you ever needed to
//check a predicate and you want it to be a fact instead of a rule just call new thread to make the fact
template<typename T>
void parse::make_pfact(rule p_rule){ //to be called by thread
  cout << "Creating thread" /*<< get_id*/ << endl;
  //static p_rule = curRB.hash.find(p_rule);
  //static vector<string> args = rule_params(p_rule); // sets rule args to vector
  //string pred_name = p_rule.predicates(p_rule);
  vector<T> temp;
  //string fact_name = p_rule.name;
  unordered_map<string,vector<string>> new_fact;
  static int inferArgs = inferParamNames.size(); //number of parameters in rule
  if (p_rule.logOperator == 0) { //if operator == or
    for (int i = 0; i < inferArgs ; i++){
      temp[i].push_back(compare_pparams(p_rule)); //vector holding facts that match rule
      cout << "temp[i] in make_fact" << endl;
    }

  } else if(p_rule.logOperator == 1){
    cout<<"ANDDD" <<endl;
  }
}
//thread t[]
//for (each pred)
//if (pred. isRule(rule name) == true)
//


//returns vector that gives the predicate paramater that matches the rule arg
vector<string> parse::compare_pparams(rule p_rule){
  string p_rule_name = p_rule.name;
  //curRB.hash.(p_rule_name);
  vector<vector<string>> preds;
  vector<string> argsv;
  vector<string> com_to = rule_params(p_rule); // the rules args
  int inferArgs = inferParamNames.size();
  for(int i = 0; i < inferArgs; i++) {
    preds[i] = p_rule.predicates[i];
    int paramSize = preds[i].size(); // checks size of vector i.e. how many paramaters
    for (int j = 0; j < paramSize; j++){ //for each parameter
      if(com_to[i] == preds[j][i]){ //if the rules args are the same as the predicates parameters
        argsv[i] = preds[j][i];//preds j is the predicate we want that matches the rule arg
      } else {
        //do nothing
      }
      cout<<"argsv" << argsv[i] <<endl;
    }
  }return argsv;

}


//creating the rule parameters to see which rule paramaters/ predicate paramaters are the same
//i.e. ($X,$Y) AND/OR ($X,$Z) ($Z,$Y)
//this definitely isnt working right but my end goal was to keep track of the rule paramaters
//then compare them to the predicate paramaters and if rule parameters matched and predicate parameters, staring a new vector
//and for any matching paramater, whether it is a rule or a fact it starts a new thread to see if they exist then return
vector<string> parse::rule_params(rule p_rule){
  //p_rule = curRB.hash.find(a_rule);
  vector <string> ru_params;
  string ruloid = p_rule.createString();
  int end1 = ruloid.find("(",0);
  int endparam = ruloid.find(")", 0);
  string r_params = ruloid.substr(end1, (endparam-end1+1));
  int base = 1;
  int tail;
  bool general;
  string parm;
  while(base<r_params.length()) {
    tail = r_params.find(",",base);
    if(tail == -1) tail = r_params.find(")",base);
    parm = r_params.substr(base,tail-base);
    cout <<"r_params: "<< parm<<endl;
    ru_params.push_back(parm);
    base = tail+1;
  }
  return ru_params;
}




// vector<string> parse::compare_params(rule p_rule){
//   int inferArgs = inferParamNames.size();
//   vector<string> comp_to = rule_params(p_rule); // sets rule parameters for main rule
//   vector<vector<strings>> order;
//   for (int i = 0; i<inferArgs; i++){ //for each arg in the rule
//     if (curRB.hash.find(p_rule.predicates[i]) != curRB.hash.end()) { // if predicate is a rule
//        vector<string> rule_co = rule_params(p_rule.predicates[i]);
//        for (int j = 0; j < rule_co.size(); j++){
//          if (comp_to[i] = rule_co[j]){
//
//          }
//        }
//     } else if(curKB.hash.find(p_rule.predicates[i]) != curKB.hash.end()){ //else if its a fact
//
//     }
//   }
// }

// void parse::infer(string input){
//   int inferSpace = input.find(" " , 0);
//   int end1 = input.find("(" , 0);
//   int money = input.find("$", 0);
//   // query holds the name of the rule being inferenced
//   string query=input.substr(inferSpace+1,(end1-inferSpace-1));
//
//   //cout<<"inference: "<<query<<endl;
//   int endr = input.find("(", inferSpace+1);
//   int endparam=input.find(")", 0);
//   // token holds the name
//   string token=input.substr(end1, (endparam-end1+1));
//   cout<<"testing token "<<token<<endl;
//   string newfactname="";
//   int end=input.find(")" , 0);
//   int zerocheck=0;
//   for(int i=end+1;i<inputSize;i++){
//     if(input.substr(i,1)!=" ")zerocheck=1;
//   }
//
//   if(zerocheck==1){
//     int space2=input.find(" ",end);
//     while(input.substr(space2,1)==" ")space2++;
//     int end2=input.find(" ",space2+1);
//     if(end2==-1) end2=input.find("\n",space2);
//     // newfactname stores an newname if used
//     newfactname=input.substr(space2,end2-space2);
//     cout<<"new fact name "<<newfactname<<"---"<<endl;
//   }
//
//   vector<vector<vector<string>>> big;
//   // if query is a fact...
//   if (curKB.hash.find(query) != curKB.hash.end()) {
//      inferFact(query,newfactname,true);
//      big.clear();
//   }
//   // if query is a rule...
//   else if (curRB.hash.find(query) != curRB.hash.end()) {
//     // split rules into indices of a vector call one by one
//     vector <rule> rules_to_be_inferred;
//     rules_to_be_inferred = curRB.traverseRule(query);
//     for (auto it=rules_to_be_inferred.begin(); it!=rules_to_be_inferred.end(); it++){
//       rule newRule = it->substitute(inferParamNames);
//       //vector<vector<vector<string>>> big;
//       int count = 0;
//       inferRule(*it,newfactname, big, count);
//       big.clear();
//     }
//     // if query is neither a rule or fact...
//   } else { cout<<query<<" is not a fact or rule."<<endl; }
// }
//


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
  cout<<"testing token "<<token<<endl;

  vector <string> params; // params is a vector of parameters
  string parameter; // parameter holds the current parameter
  int base=1;
  int tail;
  bool general;
  inferParamNames.clear();
  while(base<token.length()){
    tail=token.find(",",base);
    if(tail==-1)tail=token.find(")",base);
    parameter = token.substr(base,tail-base);
    if(parameter[0]=='$' || parameter[1] == '$') general = true; // checks if parameter is general token or not
    else general = false;
    cout<<"parameter: "<<parameter<<endl;
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

  if(curKB.hash.find(query) != curKB.hash.end())
    inferFact(query,newfactname,true);
  }
  else if (curRB.hash.find(query) != curRB.hash.end()){
    vector<string> rule_names = rule_params(query);
    cout << rule_names <<endl;
    vector<rule> rules_to_be_inferred;
    rules_to_be_inferred = curRB.traverseRule(query); // returns vector of rules
    vector<string> v_rule;
    vector<string>preds;
    int counter = 0;
    // for(auto i = rules_to_be_inferred.begin(); i!= rules_to_be_inferred.end();i++){ //pointing to each fure in vector
    //   string cur_rule = (*i).name; //gives string current rule name
    //   v_rule =  curRB.hash.find(cur_rule);// assign the rule with that name to
    //
    // }

    for(auto i = rules_to_be_inferred.begin(); i != rules_to_be_inferred.end(); i++){ // pointing to all the rules that need to be inferred
      //argsv.push_back(*i); //vector for each rule, argsv is made up of current rule.
      string cur_rule = (*i).name; //give string current rule name
      v_rule.push_back(i->createString());
      int inferArgs = v_rule.size(); //-> want this to be number of predicates
      for (int j = 0; j < inferArgs; j++){ //each predicate of current rule
        preds[j] = v_rule[j];
        //preds[j]= argsv[i].predicates;
        //argsv[j].predicates = preds[j];
        string predi = preds[j];
        if (curRB.hash.find(predi) != curRB.hash.end()){ //if it's a rule make a fact with threads
          //thread with mutex lock so the rule doesnt return until every other rule is done making facts
          //thread t(make_fact(preds[i]));
          //t.join();
          cout << "is a rule" <<endl;
          cout<< "preds" << preds[j] <<endl;

        } else if(curKB.hash.find(query) != curKB.hash.end()){
          cout << "is a fact" << endl;
          cout << "preds" << preds[j] <<endl;
        } else {
          cout<<query<<" is not a fact or rule."<<endl;
        }
      }
    }
  }
}



  // vector<vector<vector<string>>> big;
  // // if query is a fact...
  // if (curKB.hash.find(query) != curKB.hash.end()) {
  //    inferFact(query,newfactname,true);
  //    big.clear();
  // }
  // // if query is a rule...
  // else if (curRB.hash.find(query) != curRB.hash.end()) {
  //   // split rules into indices of a vector call one by one
  //   vector <rule> rules_to_be_inferred;
  //   rules_to_be_inferred = curRB.traverseRule(query);
  //   for (auto it=rules_to_be_inferred.begin(); it!=rules_to_be_inferred.end(); it++){
  //     rule newRule = it->substitute(inferParamNames);
  //     //vector<vector<vector<string>>> big;
  //     int count = 0;
  //     inferRule(*it,newfactname, big, count);
  //     big.clear();
  //   }
  //   // if query is neither a rule or fact...


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
  int sizee = p_rule.predicates.size();
  vector<string> test = rule_params(p_rule);
  for (int i = 0; i < sizee; i++){
    cout <<"test" << test[i] << endl;
  }
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
          if(curArg.substr(0,1)=="$"){  //if args first char is $, it's a free variable. Proceed
          args.push_back(*y);
        }
        else if(curArg==*y)args.push_back(*y);//check with arg of fact
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
   //printSomething3D(allRelationships, count);
   vector<vector<string>> result;
   unordered_map<string, vector<string>> result2;
   for (auto i = 0; i < allRelationships.size(); i++){
      int c = allRelationships[i].size();
      //int c = count+1;
      //bool flag = false;
      //if (c>=count+1) flag=true;
      for (auto j = 0; j < allRelationships[i].size(); j++){
	 vector<string>vars = allRelationships[i][allRelationships[i].size()-1];
	 //if (c>=count+1) flag=true;
	 //else flag = false;
	 c--;
	 //allRelationships[i][allRelationships[i].size()-1].pop_back();
	 vector<string> relations;
	 int m = 0;
	 //for (auto k = 0; k<allRelationships[i][j].size(); k++) {
	    if (vars[0]==p_rule.args[0]) relations.push_back(allRelationships[i][j][0]);
	    else if(vars[0]==p_rule.args[1]) relations.push_back(allRelationships[i][j][1]);
	    if (vars[1]==p_rule.args[1]) relations.push_back(allRelationships[i][j][1]);
	    else if (vars[1]==p_rule.args[0]) relations.push_back(allRelationships[i][j][0]);
	    //if (c>=count) flag=true;
	    //else flag = false;
	    //if (flag)
	    //else m++;
	    //for (int m=0; m<p_rule.args.size(); m++) {
	    //   if (vars[k]==p_rule.args[m])
	    //cout << p_rule.args[0] << ": " << allRelationships[i][j][k] <<" ";
	    //cout << p_rule.args[0] << ": " << allRelationships[i][j][k] <<" ";
	    //}
	 //}
	 //if (flag)
	 //cout << endl;
      result.push_back(relations);
      string key = "";
      for(auto it = relations.begin(); it!=relations.end(); it++){
        key = key + *it;
      }
    //   if (key.at(0)!='$'){
    //   result2.insert({key, relations});
    // }
    result2.insert({key, relations});

      }
   }

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


/**** also if your calling a function through a thread it has to be a static method ***/



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
