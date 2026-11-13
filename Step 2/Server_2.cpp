// Your implementation!
// The provided code is the answer key to the previous step.
// You probably want to replace it with your code! But keep the commented steps/hints. 

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>


const int SERVER_PORT = 5000;
// Feel free to add other variables/constants

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
    // Hints:
    // - The recvfrom(...) method receives data on a socket and captures the client address
    // - Allocate objects to store the data, client address, and client address length



    // OPTIONAL: Add error handling for if data could not be received (how would you know?)



    // TODO 2: Parse message for motor speed setpoint and print client information & setpoint
    // Hints:
    // - strtol(...) extracts an integer from a string
    // - inet_ntoa(...) converts an address from network byte order to a string for display
    // - ntohs(...) converts from network to host byte order for correct integer conversion
    // - std::cout prints statements


    // Close the socket and return program success code
    close(server_socket_fd);
    return 0;
}
