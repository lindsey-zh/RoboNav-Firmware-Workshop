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


# TODO 1: Set a time-out constant for how long to wait before resending a message & max # of retries before exiting the program
# Hints:
# - You might want to make the timeout and # of max retries variables.
# - socket.settimeout(...): socket throws an error if it blocks (waits) for longer than a set duration



with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    # TODO 2: Wrap previous code for sending into a retry loop & print current retry iteration
    # Hints:
    # - Use a for loop that repeats until max # of retries is reached



    # OPTIONAL: Use time.sleep(...) to pause between messages for readability in terminal output.



    # Send a motor speed control setpoint request to the server
    client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)

    # TODO 3: Use a try-except block to handle an unresponsive server (wrap previous code inside try)
    # Hints:
    # - Remember to break out of the for loop once a message's been received
    # - TimeoutError: raised when recvfrom(...) blocks for longer than the set timeout

    

    # Listen for & receive response from server
    server_response, server_address = client_socket.recvfrom(BUFFER_SIZE)
    # Print response from server
    print(f"Received from {server_address[0]}:{server_address[1]}: \"{server_response.decode("utf-8")}\"")
