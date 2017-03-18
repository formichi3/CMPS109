//#include "../headers/includes.h"
#include "TCPServerSocket.h"
#include <thread>
#include <future>

using namespace std;

int threadCount = 0;


static void runSocketThread(TCPServerSocket* server, TCPSocket* socket, int threadNum){
  string message;
  char * buffer = new char[256];
  int flag = 0;
  cout << "Waiting for input from thread " << threadNum << endl;
  while(!flag){
    //Sleep(5000);
    message = "";
    socket->readFromSocket(buffer, sizeof(buffer));
    for (int i = 0; i < strlen(buffer); i++){
      if(buffer[0] == '*'){
        flag = 1;
        delete(socket);
        break;
      }
      message += buffer[i];
    }
    cout << message;
  }
}

// int main(){
//
//
//   char const * IP = "127.0.0.1";
//   int port = 8080;
//   int backLog = 10;
//   TCPServerSocket *myServer = new TCPServerSocket(IP, port, backLog);
//   myServer->initializeSocket();
//   char * buffer;
//   string command;
//
//
//   while(true){
//
//     TCPSocket **mySocket2 = new TCPSocket *;
//     cout << "Listening on port 8080..." << endl;
//     *mySocket2 = myServer->getConnection(0,0,-1,-1);
//     if(*mySocket2!=NULL){
//       cout << "Connected!" << endl;
//       thread t1(runSocketThread, myServer, *mySocket2, threadCount++);
//       t1.detach();
//       //t1.join();
//       //runSocketThread(*mySocket2, threadCount++);
//     }
//     else { cout << "Error!" << endl; }
//
//
//
//   }
//
//
//
//
//
//
//   return 0;
// }
