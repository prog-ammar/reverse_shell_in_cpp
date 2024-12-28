#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int server=socket(AF_INET,SOCK_STREAM,0);
    if(server==-1)
    {
        cerr<<"Socket Failed To intialize"<<endl;
        return -1;
    }
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port=htons(1234);
    string ip="192.168.1.85";
    inet_pton(AF_INET,ip.c_str(),&address.sin_addr);
    int r= bind(server,(struct sockaddr*) &address,sizeof(address));
    if(r==-1)
    {
        cerr<<"failed to bind"<<endl;
        return -1;
    }
    int l=listen(server,1);
    if(l==-1)
    {
        cerr<<"failed to listen"<<endl;
        return -1;
    }
    struct sockaddr_in client;
    socklen_t clientaddsize=sizeof(client);
    int clientSocketFD=accept(server,(struct sockaddr*)&client,&clientaddsize);
    if(clientSocketFD==-1)
    {
        cerr<<"failed to create client"<<endl;
        return -1;
    }
    string buffer;
    buffer="hi";
    int sent=send(clientSocketFD,buffer.c_str(),sizeof(buffer),0);
    if(sent==-1)
    {
        cerr<<"failed to sent"<<endl;
        return -1;
    }
    else
    {
        cerr<<"successfully sent"<<endl;
    }
    close(clientSocketFD); 
    close(server);
}
