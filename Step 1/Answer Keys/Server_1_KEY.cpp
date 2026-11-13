// Feel free to use this key for reference! Other valid implementations also exist. 

// TODO 1: 
// <sys/socket.h> includes definitions for socket(...), AF_INET, and SOCK_DGRAM, which are needed for networking
// Note: This is not part of the C++ standard library (the std:: namespace) because socket implementation differs by OS (ex. Windows vs. Linux)
#include <sys/socket.h>
// <netinet/in.h> defines the sockaddr_in struct used for setting an address+port for the program
#include <netinet/in.h>
// Header for POSIX resource management (ex. close socket)
#include <unistd.h>

// Optional library to use perror for error handling
#include <cstdio>
// Optional library to use cout for printing debug messages
#include <iostream>


// CONSTANTS
// You choose a port number for your server socket. The client program will use this port when sending messages. 
// On Linux, port numbers < 1024 are privileged and should generally be avoided. 
const int SERVER_PORT = 5000;


int main() {   
    // TODO 2:
    // Create a socket for the server
    // Notes:
    // - "FD" stands for file descriptor. Linux handles a socket as a file descriptor (represented by an int).
    // - AF_INET: specifies the IPv4 address family (vs. IPv6)
    // - SOCK_DGRAM: specifies datagram (UDP) vs. stream (TCP)
    // - 0: default protocol (choose using AF_INET + SOCK_DGRAM)

    int server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);


    // OPTIONAL: Error handling & debug statements (what if the kernel API failed to establish a socket?)
    if (server_socket_fd < 0) {
        perror("[SERVER ERROR] socket()");
        return 1;
    }
    std::cout << "[SERVER INFO] Socket created." << std::endl;


    // TODO 3: BIND

    // Define an IP address & port for this process

    // Notes:
    // - sockaddr_in: C++ struct (kind of like an object) to specify an address + port
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    // - INADDR_LOOPBACK: listen on localhost
    // - htons(...)/htonl(...): converts port number from host byte order to network order (big-endian); expected by the sockaddr_in struct
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(SERVER_PORT);

    // Bind the socket that you made to this address/port

    // Notes: 
    // - bind(...): "binds" the address+port you defined to the socket file descriptor you created earlier
    // - (const struct sockaddr *): casts from sockaddr_in to the more general type that bind(...) expects
    // - &: address-of operator, gets the memory address pointer of server_address (which bind(...) expects)   
    // - sizeof(...): size of the address struct
    bind(server_socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));


    // OPTIONAL: Add a debug statement once the socket is successfully bound to the address
    std::cout << "[SERVER INFO] Address 127.0.0.1:" << SERVER_PORT << " bound to socket." << std::endl;

    // Close the socket and return program success code
    close(server_socket_fd);
    return 0;
}
