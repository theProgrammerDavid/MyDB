#include "pch.h"
#include "server.h"
#include <future>
#include <thread>
#include <chrono>

bool Server::open(SOCKET s) {
	char error[16];
	socklen_t len = sizeof(error);
	int retval = getsockopt (s, SOL_SOCKET, SO_KEEPALIVE, error, &len);
	// look, just accept that the code works and move on
	return (error[0] == '\0');
}

void Server::listener(Client c) {
	int iResult = 1;
	char recvbuf[512];
	do {
	    iResult = recv(c.sock, recvbuf, 512, 0);
	    if (iResult > 0) {
	        callback(std::string(recvbuf), c);	
	    } else if (iResult == 0) {
	        if (open(c.sock)) {
	        	printf("Connection to client %d closed\n", c.id);
		        clients.erase(c);
				closesocket(c.sock);
			}
			return;
	    } else {
			if (open(c.sock)) {
				printf("recv failed: %d, closing connection to client %d", WSAGetLastError(), c.id);
				clients.erase(c);
				closesocket(c.sock);
			}
			return;
	    }
	} while (!done && iResult > 0);		
}

void Server::acceptClients() {
	do {	
		std::future<SOCKET> future = std::async(std::launch::async, [&]() -> SOCKET {
       		return accept(ListenSocket, NULL, NULL);
    	});

		std::future_status status = std::future_status::deferred;
		while (status != std::future_status::ready) {
			if (done) {
				break;
			}
			status = future.wait_for(std::chrono::milliseconds(100));
		}
		if (status == std::future_status::ready) {
			SOCKET ClientSocket = future.get();
			if (ClientSocket != INVALID_SOCKET) {
				Client newClient = {client_id++, ClientSocket};
				clients.insert(newClient);
				listeners[newClient.id] = std::thread(&Server::listener, this, newClient);
				sendto(newClient, "Connection accepted");
			}
		}
	} while (!done);
}

int Server::sendto(Client c, std::string s) {
	int res = send(c.sock, s.c_str(), s.length(), 0);
	if (res == SOCKET_ERROR) {
		clients.erase(c);
		closesocket(c.sock);
		printf("send failed: %d\n", WSAGetLastError());
	}
	return res;
}

void Server::broadcast(std::string s) {
	for (auto c : clients) {
		int res = sendto(c, s);
	}
}

void Server::setCallback(std::function<int(std::string, Client)> _callback) {
	callback = _callback;
}

Server::Server() {
	int iResult;

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
	    printf("WSAStartup failed: %d\n", iResult);
	    return;
	}
	
	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
	    printf("getaddrinfo failed with error: %d\n", iResult);
	    WSACleanup();
	    return;
	}

	ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
	    printf("Error at socket(): %ld\n", WSAGetLastError());
	    freeaddrinfo(result);
	    WSACleanup();
	    return;
	}
	   
	iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
	    printf("Listen failed with error: %ld\n", WSAGetLastError());
	    closesocket(ListenSocket);
	    WSACleanup();
	    return;
	}

	clientAccepter = std::thread(&Server::acceptClients, this);		
}

Server::Server(std::function< int (std::string, Client)> _callback) : callback(_callback) {
	Server();
}

Server::~Server() {
	done = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	closesocket(ListenSocket);
	clientAccepter.join();
	for (auto c : clients) {
		closesocket(c.sock);
		if (listeners[c.id].joinable())
			listeners[c.id].join();
	}
	WSACleanup();
}