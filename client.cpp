
// Client side C/C++ program to demonstrate Socket programming 
#include <iostream>
//#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    std::string hello = "Hello from client";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
	std::cout << "\n Socket creation error" << std::endl; 
        return -1;
    }

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
       std::cout << "\nInvalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "\nConnection Failed \n" << std::endl;
        return -1;
    }
    send(sock, hello.c_str() , hello.length() , 0);
    std::cout << "Hello message sent\n" << std::endl;
    valread = read( sock , buffer, 1024);
    std::cout << buffer << std::endl;
    return 0;
} 

