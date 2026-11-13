# Your implementation!
# The provided code is the answer key to the previous step.
# You probably want to replace it with your code! But keep the commented steps/hints. 

from socket import socket, AF_INET, SOCK_DGRAM

# Create socket
client_socket = socket(AF_INET, SOCK_DGRAM)

# Example setpoint request message
speed_setpoint = 50
client_request = f"Requesting {speed_setpoint} RPM from client."

# TODO 1: Send a motor speed control setpoint request to the server 
# Hints:
# - The server's address/port is known from Server.cpp
# - The `with` keyword can be used for socket memory management
# - socket.sendto(...) sends a message to a known address
