import socket
import Shared;
HOST = "localhost"
PORT = 12345

"""
* Open the new file and dump the content into it 
"""
def saveToDisk(new_file, data):
    with open(new_file, "wb") as f:
        try:
            Shared.pickle.dump(data, f);
        except Exception as e:
            print(f'could not pickle.dump(data, f) into new file {e}')

"""
* Take input for the file the server wants to save the content from the client to
* save the file to disk with the destination file and unpicked-object of the clients response
* Send to the client that the transfer was successful
"""
def question_one(client_socket):
    print("!!! Question 1 !!!");
    server_file = input("Enter the Receiving File\n> ");
    pickled_file = client_socket.recv(Shared.MAX_RECV);
    saveToDisk(server_file, Shared.deserializeFiles(pickled_file));
    client_socket.sendall("Successful Trasnfer of files".encode())
    print("!!! Success    !!!");


if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(1)
    print(f"Server listening on {HOST}:{PORT}")

    try:
        while True:
            conn, address = server_socket.accept();
            question_one(conn);
    except:
        print(f'closing server..')
        
