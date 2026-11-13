// Your implementation!
// Some boilerplate code has been provided for you. 


// TODO 1: Add the necessary headers
// Many common C++ utilties (ex. print, multi-threading, lists) are provided by the C++ standard library. Similarly, most networking capabilities can be found via C++ headers that interface with OS APIs. Use your resources to figure out which are useful. 
// Enable these libraries and headers for this program with #include [header name]

// Hints: 
// - <sys/socket.h> defines many network socket function calls and constants


int main() {   
    // TODO 2: Create a socket for the server
    // Hints:
    // - socket(...) (from sys/socket)


    // OPTIONAL: Error handling & debug statements (what if the kernel API failed to establish a socket?)
    // Hints:
    // - perror(...) (from cstdio)


    // TODO 3: Define an IP address & port for this process & bind the socket to it
    // Hints: 
    // - sockaddr_in (struct that holds an IPv4 address+port)
    // - bind(...) (from sys/socket)


    // OPTIONAL: Add a debug statement once the socket is successfully bound to the address


    // TODO 3: Clean up resources & exit

    
}
