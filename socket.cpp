#include "pch.h"
#include "socket.h"

int Socket::send(std::string msg) {
	if (done)
		return SOCKET_ERROR;

	int iResult = ::send(ConnectSocket, msg.c_str(), (int) msg.length(), 0);
	if (iResult == SOCKET_ERROR) {
	    printf("send failed with error: %d\n, closing socket", WSAGetLastError());
	    close();
	}
	return iResult;
}

void Socket::setCallback(std::function<int(std::string)> _callback)	 {
	callback = _callback;
	for (int i = 0; i < callbackStack.size(); i++) {
		callback(callbackStack[i]);
	}
	callbackStack.clear();
}

void Socket::listener() {
	char recvbuf[512];
	do {
	    int iResult = recv(ConnectSocket, recvbuf, 512, 0);
	    if (iResult > 0) {
	        recvbuf[iResult] = '\0';
	        if (callback != nullptr) {
	        	callback(std::string(recvbuf));
	        } else {
	        	callbackStack.push_back(std::string(recvbuf));
	        }
	    } else if (iResult == 0) {
	        printf("connection with server closed, closing socket\n");
	        close();
	    } else {
	        printf("recv failed with error %d, closing socket\n", WSAGetLastError());
	        close();
	        break;
	    }
	} while (!done);
}

void Socket::close() {
	done = true;
}

Socket::Socket(std::string ip, std::function<int(std::string)> _callback) {	
	callback = _callback;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
	    printf("WSAStartup failed: %d\n", iResult);
	    close();
	}

	struct addrinfo *result = NULL,
		            *ptr = NULL,
        	         hints;

	printf("%s\n", ip.c_str());
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
	    printf("getaddrinfo failed: %d\n", iResult);
	    close();
	    return;
	}


	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;

	
	// Create a SOCKET for connecting to server
	ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
	    ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
	    printf("Error at socket(): %ld\n", WSAGetLastError());
	    freeaddrinfo(result);
	    close();
	    return;
	}

	// Connect to server.
	iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("Unable to connect to server!\n");
	    close();
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message
	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
	    printf("Unable to connect to server!\n");
	    close();
	}

	if (!closed())
		listenerHandler = std::thread(&Socket::listener, this);
};

Socket::~Socket() {
	done = true;
	if (listenerHandler.joinable())
		listenerHandler.join();
	closesocket(ConnectSocket);
	WSACleanup();
};