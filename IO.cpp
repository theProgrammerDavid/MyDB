#include "pch.h"
#include "IO.h"


ClientSocket::ClientSocket() {
}


void ClientSocket:: processClient(
#ifdef _WIN32
	SOCKET passdata, SOCKADDR_IN sAddr
#elif __linux__

#endif
	,int cnum
) {

	json j;
	json ret;

#ifdef _WIN32
	//int iResult;

	cnum++;

	//char recvbuf[512];
	memset(recvbuf, NULL, sizeof(recvbuf));
	int mynumber = cnum;
	SOCKET tClient = (SOCKET)passdata;
	//char connectionMSG[52];
	printf(connectionMSG, sizeof(connectionMSG), "Client connected from: %s", inet_ntoa(sAddr.sin_addr));
	printf("Alert: %s\nClients Connected: %d\n", connectionMSG, cnum);
	//char sendmsg[50];
	printf(sendmsg, 50, "PING: Your Client Number is: %d\n", mynumber);
	int sret;
	while (true)
	{
		
		std::cout << "y";
		memset(&recvbuf[0], 0, sizeof(recvbuf));

		iResult = recv(tClient, recvbuf, sizeof(recvbuf), 0);
		std::cout << "received: " << recvbuf << "|"<<std::endl;
		//std::string str = recvbuf;
		j = json::parse(recvbuf);
		
		//std::cout << j.dump(4) << std::endl;
		//std::cout << j["type"] << std::endl;
		
		std::cout << "before\n";
		ret=TABLE.ReadProtocol(j);
		const char *s = ret.dump(1).c_str();
		std::cout << "returning" << s << std::endl;
		std::cout << "size is " << ret.dump(1).size() << std::endl;
		sret = send(tClient, s, ret.dump(1).size(), 0);
		/* Every five seconds send a ping to the client... */
		if (sret == ECONNRESET || sret == SOCKET_ERROR)
		{
			cnum -= 1;
			printf("Client from %s has disconnected...\nThere's now %d clients connected...\n", inet_ntoa(sAddr.sin_addr), cnum);
			closesocket(tClient);
			break;
		}
		//Sleep(5000);
	}
#elif __linux__

#endif


}
void IO::errorBox(char * text)
{

#ifdef _WIN32
	MessageBoxA(NULL, text, "ERROR", MB_OK | MB_ICONERROR);
#elif __linux__

#endif // _WIN32

}

IO::IO(int _port)
{
#ifdef _WIN32
	myport = _port;

	addrLen = sizeof(sAddr);
	tmpRet = WSAStartup(MAKEWORD(2, 2), &wData);

	if (tmpRet != 0) {
		errorBox((char*)"WSA Had an error. Mark 1");
		exit(EXIT_CODE_WSA_ERROR);
	}
	tmpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (tmpSocket == INVALID_SOCKET) {
		errorBox((char*)"Socket Creation had an error. Mark 2");
		exit(EXIT_CODE_SOCKET_CREATION_ERROR);
	}
	tmpRet = bind(tmpSocket, (struct sockaddr*)&server, sizeof(server));

	

	memset(&server, sizeof(server), 0);
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(myport);
	printf("Using port %d\n", myport);

	

	tmpRet = bind(tmpSocket, (struct sockaddr*)&server, sizeof(server));
	
	if (tmpRet == SOCKET_ERROR)
	{
		errorBox((char*)"Bind() has an Error (Mark 3)");
		exit(3);
}
	tmpRet = listen(tmpSocket, 1);
	if (tmpRet == SOCKET_ERROR)
	{
		errorBox((char*)"Listen() has an Error (Mark 4)");
		exit(4);
	}
	printf("Binded and listening on port %d\nWaiting for a client to connect...\r\n", myport);
	/* Simple connection loop awaiting a client to connect. */

	serverSocket = SOCKET_ERROR;

#elif __linux__


#endif 

	 
	
}

void IO::loop() {


#ifdef _WIN32
	do
	{
		serverSocket = accept(tmpSocket, (sockaddr*)&sAddr, &addrLen);
		if (serverSocket != SOCKET_ERROR)
		{
			/* New client has connected process them! */
			 //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)processClient, (void*)serverSocket, NULL, NULL);
			std::thread t(&ClientSocket::processClient,new ClientSocket(), serverSocket, sAddr,cnum);
			t.detach();
			cnum++;
		}
} while (true);
#elif __linux__

#endif
}


IO::~IO()
{
}
