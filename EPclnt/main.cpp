/* Простое сервер-клиентское приложение на C++
Простой клиент */

#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>
#include <winSock2.h>
#include <windows.h>
#include <sys/types.h> 

class EPclient
{
	SOCKET sockClient;
	public:
	EPclient()
	{
		
	}
	~EPclient()
	{
		closesocket(sockClient);
	}
	bool Connect()
	{
		// connect server socket
		sockClient = socket(AF_INET, SOCK_STREAM, 0);
		WORD wVerisonRequested;
		WSADATA wsaData;
		wVerisonRequested = MAKEWORD(2,2);
		unsigned int err = WSAStartup( wVerisonRequested, &wsaData );
		if (err != 0)
		{
			printf("Connection failed");
			return err;
		}

		char m_strIP[14];
		char m_strPort[4];
		struct sockaddr_in addrServer;
		addrServer.sin_addr.S_un.S_addr = inet_addr(m_strIP);
		addrServer.sin_family = AF_INET;
		addrServer.sin_port = atoi(m_strPort);
		int ret = connect(sockClient, (struct sockaddr *)&addrServer, sizeof(addrServer));
		if (ret != 0)
		{
			printf("Connection failed!");
			closesocket(sockClient);
			return -1002;
		}
	}
	void query()
	{
		/// отправить сообщение
		
		/// получить сообщения
		;
	}
};


int main()
{
	
}

