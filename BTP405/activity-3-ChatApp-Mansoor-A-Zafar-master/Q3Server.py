import socket
import threading
import Shared;

# Main diff between this and Q2 is that here, multiple clients join whereas in Q2
# One client joins 'multiple' times (sorta)
# In Q2 each task has its own 'thread' which is all from 1 client
# In Q3, each Client has its own thread and belongs into a List

class ChatServer:
    """
    * A constructor to allow for the Server be start-up with the Host and Port
    * @clients : A list to manage all the clients that join 
      (A list of the client client_sockets)
    """
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.clients = []
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"Chat server started on {self.host}:{self.port}")

    """
    * Send a pickled-object of the clients message to all currently connected clients (excluding themselevs)
    * If a error occurs remove the client
    """
    def broadcast_messages(self, message, sender):
        for client in self.clients:
            if client != sender:
                try:
                    client.send(Shared.serializeFiles(message))
                except:
                    self.remove_client(client)
    
    """
    * Unpickle the incoming pickled-object from the Client
    * Broadcast it to all the currently connected clients
    """
    def handle_client(self, client_socket,):
        try:
            while True:
                message = Shared.deserializeFiles(client_socket.recv(Shared.MAX_RECV))
                self.broadcast_messages(message, client_socket)
        except:
            pass #skip do nothing...

    """
    * Remove the client if they are in the List
    """
    def remove_client(self, client_socket):
        if client_socket in self.clients:
            self.clients.remove(client_socket)

    """
    * Create a thread to handle the client 
      (recieving and broadcasting their messages)
    """
    def start(self):
        try:
            while True:
                client_socket, client_address = self.server_socket.accept()
                self.clients.append(client_socket)
                print(f"Client {client_address} connected.")
                client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
                client_thread.start()
        except KeyboardInterrupt:
            print("Shutting down the server.")
            self.server_socket.close()

if __name__ == "__main__":
    # Server configuration
    SERVER_HOST = "localhost"
    SERVER_PORT = 12345

    # Start the chat server
    server = ChatServer(SERVER_HOST, SERVER_PORT)
    server.start()
