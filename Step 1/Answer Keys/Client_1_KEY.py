# Feel free to use this key for reference! Other valid implementations also exist. 


# TODO 1: IMPORTS

# Note: 
# - You'll need AF_INET and SOCK_DGRAM for configuring your socket
from socket import socket, AF_INET, SOCK_DGRAM


# TODO 2: Create a UDP socket
# Note: 
# - bind(...) is optional for the client. An address/port is automatically assigned when you send the first message, which is in the next step. 
client_socket = socket(AF_INET, SOCK_DGRAM)
