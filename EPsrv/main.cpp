/* Простое сервер-клиентское приложение на C++
Простой сервер */

#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>
#include <winSock2.h>
#include <windows.h>
#include <sys/types.h>  

char message[] = "Hello there!\n";

class server{

    int sock;
    sockaddr_in addr;

    public:
    server()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(3425);
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }
    }
    void Listen()
    {
        send(sock, message, sizeof(message), 0);
    }
    void Reply()
    {
        char buf[sizeof(message)];
        recv(sock, buf, sizeof(message), 0); 
        printf(buf);
    }
    ~server()
    {
        closesocket(sock);
    }

};

int main()
{
    
    
    return 0;
}