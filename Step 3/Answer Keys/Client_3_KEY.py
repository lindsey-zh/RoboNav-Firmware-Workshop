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


with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    # Send a motor speed control setpoint request to the server 
    client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)


    # TODO 1: Listen for & receive response from server
    # Notes:
    # recvfrom(...): listens for messages from a known address
    # Parameters:
    # 1. Buffer size: when to stop reading
    server_response, server_address = client_socket.recvfrom(BUFFER_SIZE)

    # TODO 2: Print response from server
    # Notes:
    # - string.decode(...): converts utf-8-encoded bytes into a string
    # - Address/port pairs are stored as tuples in Python
    print(f"Received from {server_address[0]}:{server_address[1]}: \"{server_response.decode("utf-8")}\"")
