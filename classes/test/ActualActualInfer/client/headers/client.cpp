#include "TCPSocket.h"

int main(int argc,char ** argv){
  int sock;
  struct sockaddr_in serverAddr;
  socklen_t sin_size = sizeof(struct sockaddr_in);

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    cout << "Error creating socket\n";
  }
  else{
    cout << "Created Socket\n";
    memset((char *) &serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    struct hostent *server = gethostbyname("127.0.0.1"); // convert the host name into a network host structure
    if ( server == NULL ) cout << "Error1"; // if failed terminate with an error message
    // copy Server address data into server address structure
    memcpy((char *)&serverAddr.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
    memset(&(serverAddr.sin_zero), 0, 8); // Zero out the rest of the address structure
    // try to connect to the server and exit with an error message if failed
    if (connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) < 0 ) cout << "Error2";
    else{
      cout << "connected to server!\nPlease enter command: " << endl;
      //send (sock,"Hello CMPS 109\n",strlen("Hello CMPS 109"),0);
      while(true){
        cout << "Enter a command:" << endl;
        char message[1024];
        string input;
        getline(cin, input);
        strcpy(message, input.c_str());
        send(sock,message,strlen(message),0);
        if (input == "q" || input == "quit" || input == "exit"){
          cout << "Goodbye!\n";
          return 0;
        }
      }
    }
  }
  return 0;
}
