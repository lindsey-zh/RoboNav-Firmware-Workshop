# Feel free to use this key for reference! Other valid implementations also exist. 

from socket import socket, AF_INET, SOCK_DGRAM

# Create socket
client_socket = socket(AF_INET, SOCK_DGRAM)

# Define server address
SERVER_IP = '127.0.0.1'
SERVER_PORT = 5000
SERVER_ADDR = (SERVER_IP, SERVER_PORT)

# Define request message information
speed_setpoint = 50
BUFFER_SIZE = 1024
client_request = f"Requesting {speed_setpoint} RPM from client."


# TODO 1: Send a motor speed control setpoint request to the server 
# Notes: 
# - `with` handles resource management of the socket for you. It releases the socket when the code block exists/raises an exception
# - string.encode("utf-8"): converts string to bytes
# - socket.sendto(...): sends a message to a known address
with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)
