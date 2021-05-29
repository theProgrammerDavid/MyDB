#pragma comment (lib, "ws2_32.lib")

#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <Windows.h>
#include "IO.h"

int cnum = 0;
int myport;
SOCKADDR_IN sAddr;




void errorBox(char *text)
{
	MessageBoxA(NULL, text, "ERROR", MB_OK | MB_ICONERROR);
}

void processClient(SOCKET passdata)
{
	int mynumber = cnum;
	int sret;
	int iResult;
	char recvbuf[512];
	SOCKET tClient = (SOCKET)passdata;
	//json j,ret;
	memset(recvbuf, NULL, sizeof(recvbuf));
	
	printf("Client connected from: %s", inet_ntoa(sAddr.sin_addr));
	printf("\nClients Connected: %d\n", cnum);
	printf("PING: Your Client Number is: %d\n", mynumber);

	while (true)
	{

		try {
			memset(&recvbuf[0], 0, sizeof(recvbuf));
			iResult = recv(tClient, recvbuf, sizeof(recvbuf), 0);
			std::cout << "received: " << recvbuf <<'|'<< '\n';
			sret = send(tClient, recvbuf, sizeof(recvbuf), 0);
			
			json j = json::parse(recvbuf);
			json ret = TABLE.ReadProtocol(j);
			
			const char* s = ret.dump(1).c_str();
			std::cout << "returning buffer with size " << strlen(s) << "with data " << s << "\n";

			/* Every five seconds send a ping to the client... */
			if (sret == ECONNRESET || sret == SOCKET_ERROR)
			{
				cnum--;
				printf("Client from %s has disconnected...\nThere's now %d clients connected...\n", inet_ntoa(sAddr.sin_addr), cnum);
				closesocket(tClient);
				break;
			}
		}
		catch (const std::exception& e) {
			std::cout << "exception occured here1";
			std::cout << e.what();
			std::cout << "Client Disconnected";
			return;
		}
		//Sleep(5000);
	}
}

void test() {
	printf("What port: ");
	scanf("%d", &myport);
	WSADATA wData;
	SOCKET tmpSocket, serverSocket;
	struct sockaddr_in server;
	int addrLen = sizeof(sAddr);



	int tmpRet = WSAStartup(MAKEWORD(2, 2), &wData);
	if (tmpRet != 0)
	{
		errorBox((char*)"WSA Had an Error (Mark 1)");
		exit(1);
	}
	tmpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tmpSocket == INVALID_SOCKET)
	{
		errorBox((char*)"Socket() had an Error (Mark 2)");
		exit(2);
	}


	/* Fill our server structure */
	memset(&server, sizeof(server), 0);
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(myport);
	printf("Using port %d\n", myport);



	/* Set up the actual socket (bind and listen) */
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
	//ClientSocket cs;
	serverSocket = SOCKET_ERROR;
	do
	{
		try {
			serverSocket = accept(tmpSocket, (sockaddr*)&sAddr, &addrLen);
			
			if (serverSocket != SOCKET_ERROR)
			{
				/* New client has connected process them! */
				// CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)processClient, (void*)serverSocket, NULL, NULL);
				std::thread t(processClient, serverSocket);
				t.detach();
				
				cnum++;
			}
		}
		catch (const std::exception& e) {
			std::cout << "exception occured here2";
			std::cout << e.what();
		}
	} while (true);
	getchar();
}

int main() {
	SetConsoleTitleA("HasherDB");
	//IO io(27015);
	//io.loop();
	test();
	return 0;
}