#ifndef __SOCKET_H_
#define __SOCKET_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_PORT "27015"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#include <functional>
#include <vector>
#include <thread>

class Socket {
private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	std::function<int(std::string)> callback;
	std::vector< std::string > callbackStack;
	std::thread listenerHandler;
	bool done = false;

	void listener();

public:
	Socket(std::string ip, std::function<int(std::string)> _callback = nullptr);
	~Socket();

	int send(std::string msg);
	bool closed() { return done; }
	
	void close();
	void setCallback(std::function<int(std::string)> _callback);
};

#endif