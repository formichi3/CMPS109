//#include "../headers/includes.h"
#include "TCPServerSocket.h"
#include <thread>
#include <future>

using namespace std;

int threadCount = 0;


static void runSocketThread(TCPServerSocket* server, TCPSocket* socket, int threadNum){
  parse p;
  char backToClient[1024];
  vector<vector<string>> result;
  string message;
  int bufferSize = 1024;
  char * buffer = new char[bufferSize];
  int flag = 0;
  while(!flag){
    //sleep(5);
    message = "";
    cout << "Waiting for input from client thread " << threadNum << endl;
    if(socket->readFromSocket(buffer, bufferSize) > 0){
    for (int i = 0; i < strlen(buffer); i++){
      message += buffer[i];
    }
    if (message == "q" || message == "quit" || message == "exit"){
      flag = 1;
      socket->shutDown();
      delete(socket);
      cout << message << ": socket connection closed\nListening on port 8080..." << endl;
    }
    else {cout << "COMMAND RECIEVED: " << message << endl;}
    result = p.checkLine(message);
    string line = "";
    string body = "";
    for (auto it = result.begin(); it != result.end(); it++){
      line = "";
      for (auto it2 = it->begin(); it2 != it->end(); it2++){
        line += *it2 + " ";
    }
    // cout << "LINE1" << line << endl;
    body += line + "\n";
    // cout << "BODY" << body << endl;

  }
  strcpy(backToClient, body.c_str());
  socket->writeToSocket(backToClient, bufferSize);
  }
  else {cout << "Connection Lost on client " << threadNum << endl;break;};
  }

}

int main(){


  char const * IP = "127.0.0.1";
  int port = 8080;
  int backLog = 10;
  TCPServerSocket *myServer = new TCPServerSocket(IP, port, backLog);
  myServer->initializeSocket();
  char * buffer;
  string command;


  while(true){

    TCPSocket **mySocket2 = new TCPSocket *;

    cout << "Listening on port 8080..." << endl;
    *mySocket2 = myServer->getConnection(0,0,-1,-1);
    if(*mySocket2!=NULL){
      cout << "Connected!" << endl;
      thread t1(runSocketThread, myServer, *mySocket2, threadCount++);
      t1.detach();
    }
    else { cout << "Error!" << endl; }



  }






  return 0;
}
