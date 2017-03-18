#include "TCPSocket.h"

// class client{
//
//   int sock;
//   string address;
//   int port;
//   string sockaddr_in server;
//
//   tcp_client();
//   ~tcp_client();
//   bool connection(string, int);
//   bool send(string command);
//   string reveive(int);
//
// };
//
// tcp_client(){
//   sock = -1;
//   port = 0;
//   address = "";
// }
// ~tcp_client(){
//
// }
// bool connection(string, int){
//   if(sock == -1){
//     sock = TCPSocket(127.0.0.1, 8080, 256, 256);
//     if(sock == -1){
//       cout << "Error creating socket\n";
//     }
//     else{
//       cout << "Client socket created\n";
//     }
//
//   }
// }
// bool send(string command);
// string reveive(int);





// int main(int argc,char ** argv){
//   int sock;
//   struct sockaddr_in serverAddr;
//   socklen_t sin_size = sizeof(struct sockaddr_in);
//
//   if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
//     cout << "Error creating socket\n";
//   }
//   else{
//     cout << "Created Socket\n";
//     memset((char *) &serverAddr, 0, sizeof(serverAddr));
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(8080);
//     struct hostent *server = gethostbyname("127.0.0.1"); // convert the host name into a network host structure
//     if ( server == NULL ) cout << "Error1"; // if failed terminate with an error message
//     // copy Server address data into server address structure
//     memcpy((char *)&serverAddr.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
//     memset(&(serverAddr.sin_zero), 0, 8); // Zero out the rest of the address structure
//     // try to connect to the server and exit with an error message if failed
//     if (connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) == -1 ) cout << "Error2";
//     send (sock,"Hello CMPS 108",strlen("Hello CMPS 109"),0); // Send a message to the server.
//     close(sock);// Close the socket
//
//
//
//
//   }
//
// }
