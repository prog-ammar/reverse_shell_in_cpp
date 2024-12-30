#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int check(int a,int& s)
{
    if(a==-1)
    {
        cout<<"An Error is Occured "<<endl;
        close(s);
        exit(0);
    }
    return 1;
}


int main()
{
    int server=socket(AF_INET,SOCK_STREAM,0);
    check(server,server);
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port=htons(1234);
    string ip="192.168.1.85";
    inet_pton(AF_INET,ip.c_str(),&address.sin_addr);
    int r= bind(server,(struct sockaddr*) &address,sizeof(address));
    check(r,server);
    int l=listen(server,1);
    check(l,server);
    struct sockaddr_in client;
    socklen_t clientaddsize=sizeof(client);
    int clientSocketFD=accept(server,(struct sockaddr*)&client,&clientaddsize);
    check(clientSocketFD,server);
    string buffer;
    cout<<" >>>";
    getline(cin,buffer);
    int sent=send(clientSocketFD,buffer.c_str(),buffer.size(),0);
    if(check(sent,server))
    {
        cerr<<"successfully sent"<<endl;
    }
    char output[4096];
    int recieve=recv(clientSocketFD,output,sizeof(output),0);
    if(check(recieve,server))
    {
        cout<<"Successfully recieved "<<endl;
        cout<<"Output : "<<output;
    }
    close(clientSocketFD); 
    close(server);
}
