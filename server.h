#ifndef __SERVER_H_
#define __SERVER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <set>
#include <map>
#include <functional>

#define DEFAULT_PORT "27015"


struct Client {
	int id;
	SOCKET sock;
	bool operator < (const Client &other) const {
		return id < other.id;
	}
};

class Server {
private:
	WSADATA wsaData;
	SOCKET ListenSocket;
	std::set< Client > clients;
	bool done = false;
	std::thread clientAccepter;
	std::map< int, std::thread > listeners;
	int client_id = 0;

	std::function<int(std::string, Client)> callback;
	void listener(Client c);
	void acceptClients();
	bool open(SOCKET s);
	
public:
	Server();
	Server(std::function< int (std::string, Client)>);
	~Server();

	int sendto(Client c, std::string s);
	void broadcast(std::string s);

	void setCallback(std::function< int (std::string, Client)> _callback);
};

#endif