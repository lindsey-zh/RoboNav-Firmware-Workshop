# Feel free to use this key for reference! Other valid implementations also exist. 

from socket import socket, AF_INET, SOCK_DGRAM
import time

# Create socket
client_socket = socket(AF_INET, SOCK_DGRAM)

# Define server address
SERVER_IP = '127.0.0.1'
SERVER_PORT = 5000
SERVER_ADDR = (SERVER_IP, SERVER_PORT)

# Define request message information

# TODO 1: Change speed setpoint to a list (stream) of setpoints
# - In reality, the input stream would be provided from an input device instead (i.e. joystick control)


speed_setpoints = [ 50*i for i in range(5) ]
BUFFER_SIZE = 1024

# Define time-out & max # of retries
TIMEOUT = 2
MAX_RETRIES = 3
READABILITY_WAIT = 2
client_socket.settimeout(TIMEOUT)

with client_socket:
    print(f"[CLIENT INFO] Drivetrain speed control client configured!")

    # TODO 2: Iterate through each motor setpoint

    for speed in speed_setpoints:
        client_request = f"Requesting {speed} RPM from client."

        for attempt in range(MAX_RETRIES):
            print(f"\n[CLIENT INFO] Attempt {attempt+1}/{MAX_RETRIES} of sending to {SERVER_ADDR[0]}:{SERVER_ADDR[1]}: {client_request}")

            # Pause between messages for readability.
            time.sleep(READABILITY_WAIT)

            # Send a motor speed control setpoint request to the server
            client_socket.sendto(client_request.encode("utf-8"), SERVER_ADDR)

            # Use a try-except block to handle an unresponsive server
            try:
                # Listen for & receive response from server
                server_response, server_address = client_socket.recvfrom(BUFFER_SIZE)
                # Print response from server
                print(f"Received from {server_address[0]}:{server_address[1]}: \"{server_response.decode("utf-8")}\"")
                break
            except TimeoutError:
                print(f"[CLIENT INFO] Server response timed out.")
