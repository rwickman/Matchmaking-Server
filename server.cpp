// Server side C/C++ program to demonstrate Socket programming
#include <iostream>
//#include <stdio.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> // constants and structures needed for internet domain addresses 
#include <string.h> 

#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket_fd, valread; 
    struct sockaddr_in address; // Contains an internet address 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    std::string hello = "Hello from server"; 
       
    // Creating socket file descriptor using IPV4 and TCP 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
	std::cerr << "socket failed" << std::endl; 
        exit(EXIT_FAILURE); 
    } 
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
	std::cerr << "setsockopt" << std::endl; 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; // Set the IP address 
    address.sin_port = htons(PORT); // convert PORT from host byte order to network byte order
       
    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
	std::cerr << "bind failed" << std::endl; 
        exit(EXIT_FAILURE); 
    }

    // Listen on this server for connections and allow for a backlog of 5
    if (listen(server_fd, 5) < 0) 
    { 
	std::cerr << "listen" << std::endl; 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket_fd = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
	std::cerr << "accept" << std::endl;
        exit(EXIT_FAILURE); 
    }

    valread = read(new_socket_fd, buffer, 1024);
    std::cout << buffer << std::endl;
    send(new_socket_fd, hello.c_str() , hello.size() , 0);
    std::cout << "Hello message sent" << std::endl;
}
