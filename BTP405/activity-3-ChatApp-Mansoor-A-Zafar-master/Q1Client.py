import socket
import Shared;
HOST = "localhost"
PORT = 12345

"""
* Let the client enter what file they're sending over
* Send a pickled-object of the file 
* Recieve the Server's reponse that it was sent
"""
def question_one(client_socket):
    print(f'!!! Question 1 !!!');
    file = input("Enter the file name\n> ");
    pickled_file = Shared.serializeFiles(file, True);
    client_socket.send(pickled_file);
    print(f'{client_socket.recv(Shared.MAX_RECV).decode()}');

if __name__ == "__main__":
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))
    question_one(client_socket);
    
