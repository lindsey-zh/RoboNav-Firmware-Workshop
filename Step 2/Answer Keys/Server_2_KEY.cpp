// Feel free to use this key for reference! Other valid implementations also exist. 

#include <sys/socket.h>
#include <netinet/in.h>
// Header that makes inet_ntoa(...) available
#include <arpa/inet.h>

#include <unistd.h>
#include <cstdio>
#include <iostream>



const int SERVER_PORT = 5000;
// Size of the buffer that stores received messages
const size_t BUFFER_SIZE = 1024;


int main() {
    // Create a socket for the server
    int server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // Error handling & debug statements
    if (server_socket_fd < 0) {
        perror("[SERVER ERROR] socket()");
        return 1;
    }
    std::cout << "[SERVER INFO] Socket created." << std::endl;

    // Define an IP address & port for this process
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(SERVER_PORT);

    // Bind the socket that you made to this address/port
    bind(server_socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));

    // Add a debug statement once the socket is successfully bound to the address
    std::cout << "[SERVER INFO] Address 127.0.0.1:" << SERVER_PORT << " bound to socket." << std::endl;


    // TODO 1: Listen for messages on the server socket

    // Notes:
    // - Why store messages in a char array? Network data is stored in bytes; C++ chars are guaranteed to be 1 byte long.
    // - Why store each message in a buffer? Prevents allocating new memory for each message on the network. 
    // - Create the structs and vars to store client info before the recvfrom() call because recvfrom() expects them as out variables. Out variables allow a function to "return" multiple variables by modifying input placeholder variables' data for the caller to later use. 
    char buffer[BUFFER_SIZE];
    // Index of the RPM data in the client request message
    const size_t RPM_I = 10;
    sockaddr_in client_address;
    socklen_t address_len = sizeof(client_address);

    // Notes: 
    // - recvfrom(...) vs. recv(...): recvfrom(...) is used for UDP, since it captures the sender's address. recv(...) already has sender information because TCP is a connection-based protocol.
    // - recvfrom(...) parameters:
    //  - 1. The server socket file descriptor
    //  - 2. The buffer to store incoming data (out variable)
    //  - 3. Maximum buffer size (discard excess)
    //  - 4. Flags: 0 is default
    //  - 5 & 6: Client address information (out variable)
    // - Returns # of bytes received. Will be useful for managing the buffer and error checking. 
    ssize_t bytes_received = recvfrom(server_socket_fd, buffer, BUFFER_SIZE-1, 0, (sockaddr*) &client_address, &address_len);

    // OPTIONAL: Add error handling for if data could not be received (how would you know?)
    // Notes: 
    // - recvfrom(...) returns -1 if something failed
    if (bytes_received < 0) {
        perror("[SERVER ERROR] recvfrom()");
    }

    // TODO 2: Parse message for useful information
    // Notes:
    // - Null-terminate the data with the \0 character to identify where the message ends in the buffer
    // - strtol(...) extracts an integer from a string
    buffer[bytes_received] = '\0';
    long rpm = std::strtol(buffer+RPM_I, nullptr, 10);
    
    // Notes:
    // - inet_ntoa(...) converts from network byte order to string
    char* client_IP = inet_ntoa(client_address.sin_addr);
    int client_port = ntohs(client_address.sin_port);

    std::cout << "\nReceived request from client " << client_IP << ":" << client_port << ": " << rpm << " RPM."  << std::endl;

    // Close the socket and return program success code
    close(server_socket_fd);
    return 0;
}
