# Your implementation!
# The provided code is the answer key to the previous step.
# You probably want to replace it with your code! But keep the commented steps/hints. 

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

with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    # Send a motor speed control setpoint request to the server 
    client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)


    # TODO 1: Listen for & receive response from server
    # Hints:
    # - recvfrom(...): listens for messages from a known address


    # TODO 2: Print response from server
    # Hints:
    # - string.decode(...): converts utf-8-encoded bytes into a string
