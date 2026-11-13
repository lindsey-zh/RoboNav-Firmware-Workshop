// Your implementation!
// The provided code is the answer key to the previous step.
// You probably want to replace it with your code! But keep the commented steps/hints. 

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>


const int SERVER_PORT = 5000;
const size_t BUFFER_SIZE = 1024;
const int READABILITY_WAIT = 2;


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


    // TODO 1: Wrap server response in a forever loop to indefinitely process incoming setpoint requests
    // Notes:
    // - In reality, you'd want to set a timeout so that the program terminates at some point. 

    ssize_t bytes_received = recvfrom(server_socket_fd, buffer, BUFFER_SIZE-1, 0, (sockaddr*) &client_address, &address_len);
    
    // Error handling for if data could not be received
    if (bytes_received < 0) {
        perror("[SERVER ERROR] recvfrom()");


        // TODO 2: Skip current loop iteration if data could not be received


    }

    // Parse message for useful information
    buffer[bytes_received] = '\0';
    long rpm = std::strtol(buffer+RPM_I, nullptr, 10);
    char* client_IP = inet_ntoa(client_address.sin_addr);
    int client_port = ntohs(client_address.sin_port);

    std::cout << "\nReceived request from client " << client_IP << ":" << client_port << ": " << rpm << " RPM."  << std::endl;


    // Wait before sending server's response for better readability.
    std::this_thread::sleep_for(std::chrono::seconds(READABILITY_WAIT));


    // Respond to the client. 
    const char* server_response = "Speed is set.";
    ssize_t bytes_sent = sendto(server_socket_fd, server_response, strlen(server_response), 0, (sockaddr*) &client_address, sizeof(client_address));
    
    // Close the socket and return program success code
    close(server_socket_fd);
    return 0;
}
