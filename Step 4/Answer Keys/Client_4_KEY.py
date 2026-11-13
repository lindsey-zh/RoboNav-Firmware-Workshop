# Feel free to use this key for reference! Other valid implementations also exist. 

from socket import socket, AF_INET, SOCK_DGRAM

# OPTIONAL: Use the time library to pause between messages for readability.
import time

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
# Notes:
# - socket.settimeout(...): socket throws an error if it blocks (waits) for longer than a set duration
TIMEOUT = 2
MAX_RETRIES = 3
READABILITY_WAIT = 2
client_socket.settimeout(TIMEOUT)

with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    # TODO 2: Wrap previous code for sending into a retry loop & log retry number
    for attempt in range(MAX_RETRIES):
        print(f"\n[CLIENT INFO] Attempt {attempt+1}/{MAX_RETRIES} of sending to {SERVER_ADDR[0]}:{SERVER_ADDR[1]}: {client_request}")

        # OPTIONAL: Use time.sleep(...) to pause between messages for readability.
        # - Note: sleep(...) uses seconds, not ms
        time.sleep(READABILITY_WAIT)

        # Send a motor speed control setpoint request to the server
        client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)

        # TODO 3: Use a try-except block to handle an unresponsive server (wrap previous code inside try)
        # Notes:
        # - Try-except blocks catch and handle runtime errors (socket timeout raises a TimeoutError)
        try:
            # Listen for & receive response from server
            server_response, server_address = client_socket.recvfrom(BUFFER_SIZE)
            # Print response from server
            print(f"Received from {server_address[0]}:{server_address[1]}: \"{server_response.decode("utf-8")}\"")
            break
        except TimeoutError:
            print(f"[CLIENT INFO] Server response timed out.")
