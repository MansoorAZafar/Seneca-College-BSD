import socket
import Shared

class TaskClient:
    """
    Initialize the Client Connection with the Port and Host 
    """
    def __init__(self, host, port):
        self.host = host
        self.port = port

    """
    * Connect the server with this Client
    * Get a Pickled object of the task
    * Send it to the Server
    * Get the Pickled object and unpickle it
    * Print it to the console
    * 
    """
    def send_task(self, task):
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
                server_socket.connect((self.host, self.port))
                serialized_task = Shared.serializeFiles(task)
                server_socket.send(serialized_task)
                result = Shared.deserializeFiles(server_socket.recv(Shared.MAX_RECV))
                print("Result:", result)
        except Exception as e:
            print(f"Error processing task: {e}")

if __name__ == "__main__":
    # Client configuration
    SERVER_HOST = "localhost"
    SERVER_PORT = 12345

    # Create a task client
    task_client = TaskClient(SERVER_HOST, SERVER_PORT)

    # Example tasks
    queue = [(Shared.add, 5, 10), (Shared.multiply, 5, 10)]
    # Every task will conenct to the Server under a different worker
    for job in queue:
        task_client.send_task(job)
