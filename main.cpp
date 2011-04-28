/* 
 * File:   main.cpp
 * Author: patrik
 *
 * Created on 27. duben 2011, 17:55
 */

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstdlib>

#define PORT 0x80

#define HOST "localhost"

#define DIRSIZE 8192

using namespace std;

int main(int argc, char **argv)
{
    char hostname[100];
    
    int sd;
    
    struct sockaddr_in sin;
    struct sockaddr_in pin;
    
    struct hostent *hp;
    
    
    strcpy(hostname, HOST);
    
    if((hp = gethostbyname(hostname)) == 0) 
    {
        perror("gethostbyname error: "); // throw new error
        exit(1);
    }
        
    // socket info 
    memset(&pin, 0, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_addr.s_addr = ((struct in_addr *) (hp->h_addr))->s_addr;
    pin.sin_port = htons(PORT);
    
    // socket connection
    
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error: "); //throw new error
        exit(1);
    }
    
    
    // connect to server
    if(connect(sd, (struct sockaddr *) &pin, sizeof(pin)) == -1)
    {
        perror("connect error: "); //throw new error
        exit(1); 
    }
    
    // send some data 
    int i = 0;
    char *msg;
    
    do{
        cout << "Cekam na data: \n" << endl;
        cin >> msg;
        if(send(sd,msg, strlen(msg), 0) == -1)
        {
            perror("send error: "); 
            exit(1);
        }
        
        
        i++;
    }while(i<10);
    
    
    close(sd);
}
