"""
* I used a list since there's no guarantee in the order of which the threads will finish; For example,
* if the 1st thread isn't done by the time the 5th is then if you used something like a Queue which are FIFO then,
* you wouldn't be able to remove the other threads without waiting for the 1st one to finish. With a list, you can 
* remove them in any order and still have the efficency of lists. Lists are the best ds for containing the workers. 
"""
import socket
import threading
import Shared;

class TaskServer:
    """
    * Constructor for initializing the Server-Side with a Host and Port
    * @self.workers : A list of Client Connections
      (Each worker will handle 1 task from the Client)
    * @self.lock : used to help prevent any race conditions when adding or removing Workers
    """
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.workers = []
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        self.lock = threading.Lock();
        print(f"Task server started on {self.host}:{self.port}")

    """
    * Recieve the task as a Pickled Object
    * unpickle the Task
    * grab the function and the arguments
    * call the function with its arguments
    * Send let the worker_socket/current client_connection/socket send the data back to the user
    * Close the connection by removing itself
    """
    def handle_worker(self, worker_socket, worker_address):
        try:
            while True:
                task_data = worker_socket.recv(Shared.MAX_RECV)
                if not task_data:
                    break  # If no data received, break the loop
                task_data = Shared.deserializeFiles(task_data)
                task, *args = task_data
                result = task(*args)  # Execute the task with arguments
                worker_socket.send(Shared.serializeFiles(result))
        except Exception as e:
            print(f"Error processing task: {e}")
        finally:
            print(f"Worker {worker_address} disconnected.")
            self.remove_worker(worker_socket)

    """
    * Add the current Client Connection to the "Workers" List
    * Each Task sent from the Client is assoicated to One Worker
    """
    def add_worker(self, worker_socket):
        with self.lock:
            self.workers.append(worker_socket)
            print(f"Worker {worker_socket.getpeername()} connected.")

    """
    * Remove a Client Connection from the Server 
    * Also closes the connection
    * 
    * Removed from the list of workers since it's no longer needed and it exists there 
    * (while the if condition isn't needed, it's good for scalability)
    * The lock is here to help prevent any potential race conditions
    """
    def remove_worker(self, worker_socket):
        with self.lock:
            if worker_socket in self.workers:
                self.workers.remove(worker_socket)
                worker_socket.close()

    """
    * For every client that connects, add a "worker" into the list
    * Assign a worker thread to a function to handle the clients connection and task
    * Start it 
    """
    def start(self):
        try:
            while True:
                worker_socket, worker_address = self.server_socket.accept()
                self.add_worker(worker_socket)
                worker_thread = threading.Thread(target=self.handle_worker, args=(worker_socket, worker_address))
                worker_thread.start()
        except KeyboardInterrupt:
            print("Shutting down the task server.")
            self.server_socket.close()

if __name__ == "__main__":
    # Server configuration
    SERVER_HOST = "localhost"
    SERVER_PORT = 12345

    # Start the task server
    server = TaskServer(SERVER_HOST, SERVER_PORT)
    server.start()
