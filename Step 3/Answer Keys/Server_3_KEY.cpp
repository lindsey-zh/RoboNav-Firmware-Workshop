// Feel free to use this key for reference! Other valid implementations also exist. 

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <cstring>


const int SERVER_PORT = 5000;
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

    // Listen for messages on the server socket
    char buffer[BUFFER_SIZE];
    const size_t RPM_I = 10;
    sockaddr_in client_address;
    socklen_t address_len = sizeof(client_address);
    ssize_t bytes_received = recvfrom(server_socket_fd, buffer, BUFFER_SIZE-1, 0, (sockaddr*) &client_address, &address_len);

    // Error handling for if data could not be received
    if (bytes_received < 0) {
        perror("[SERVER ERROR] recvfrom()");
    }

    // Parse message for useful information
    buffer[bytes_received] = '\0';
    long rpm = std::strtol(buffer+RPM_I, nullptr, 10);
    char* client_IP = inet_ntoa(client_address.sin_addr);
    int client_port = ntohs(client_address.sin_port);

    std::cout << "\nReceived request from client " << client_IP << ":" << client_port << ": " << rpm << " RPM."  << std::endl;


    // TODO 1: Respond to the client. 
    // Notes: 
    // - sendto() parameters:
        // - 1. Sender socket FD
        // - 2. Data to send (memory address of buffer start)
        // - 3. Length of data in buffer (to determine where the message ends in buffer)
        // - 4. Flags; 0 is default
        // - 5 & 6. Receiving address
    // - strlen(...): length of C-string excluding null terminator
    const char* server_response = "Speed is set.";
    ssize_t bytes_sent = sendto(server_socket_fd, server_response, strlen(server_response), 0, (sockaddr*) &client_address, sizeof(client_address));


    // Close the socket and return program success code
    close(server_socket_fd);
    return 0;
}
