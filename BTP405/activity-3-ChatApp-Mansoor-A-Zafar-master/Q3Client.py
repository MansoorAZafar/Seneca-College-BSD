import socket
import threading
import Shared;

class ChatClient:
    """
    * A constructor to allow for the assignment of a HOST, PORT and Name;
    * @self.name: the name of the user for the current client connection
    * @recieve_thread: A thread to manage the Servers reponses (other client' messages) 
    """
    def __init__(self, host, port, name):
        self.host = host
        self.port = port
        self.name = name
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.host, self.port))
        self.receive_thread = threading.Thread(target=self.receive_messages)
        self.receive_thread.start()

    """
    * Unpickle the receiving pickled-object from the Server
    * and print it to the console
    """
    def receive_messages(self):
        try:
            while True:
                message = Shared.deserializeFiles(self.client_socket.recv(Shared.MAX_RECV))
                print(message)
        except KeyboardInterrupt:
            pass

    """
    * Send a pickled-object of the current Clients name (self.name) alongside their message
    """
    def send_message(self, message):
        try:
            self.client_socket.send(Shared.serializeFiles(f"{self.name}: {message}"))
        except:
            print("Error: Failed to send message.")

    """
    * Close the current clients connection to the server
    """
    def disconnect(self):
        self.client_socket.close()

if __name__ == "__main__":
    # Client configuration
    SERVER_HOST = "localhost"
    SERVER_PORT = 12345

    # Start a chat client
    print(f'enter "quit" to leave or CTRL + C')
    client_name = input("Enter your name: ")
    client = ChatClient(SERVER_HOST, SERVER_PORT, client_name)
    # Chat loop
    try:
        while True:
            message = input()
            if message.lower() == "quit":
                client.disconnect()
                break
            client.send_message(message)
    except KeyboardInterrupt:
        client.disconnect()
