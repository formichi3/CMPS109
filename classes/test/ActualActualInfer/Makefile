all: server Client

server: server/headers/
	g++ -std=c++11 server/headers/*.cpp
	./a.out

client: client/headers/
	g++ -std=c++11 client/headers/*.cpp
	./a.out
