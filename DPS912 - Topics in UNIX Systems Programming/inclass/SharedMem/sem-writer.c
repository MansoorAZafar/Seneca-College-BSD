#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define SHM_SIZE 1024  // Size of shared memory in bytes

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

void performSemaphoreOperation(int sem_id, int sem_num, int sem_op) {
    struct sembuf semaphore;
    semaphore.sem_num = sem_num;
    semaphore.sem_op = sem_op;
    semaphore.sem_flg = 0;

    if (semop(sem_id, &semaphore, 1) == -1) {
        perror("Semaphore operation failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Create or get the shared memory segment
    int shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create or get the semaphore
    int sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore value to 1
    union semun arg;
    arg.val = 1;
    if (semctl(sem_id, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Wait for semaphore to allow access
    performSemaphoreOperation(sem_id, 0, -1);
    // printf("Writer acquired semaphore\n");
    // sleep(20);

    sprintf(shm_ptr,
        "Message from %s. Writer PID = %d",
        "Matteo Grutta, Mansoor Zafar, John Mubeezi",
        getpid()
    );

    // Write data to shared memory
    // sprintf(shm_ptr, "Hello from the writer!");

    // printf("Writer releasing semaphore\n");
    // Release the semaphore
    performSemaphoreOperation(sem_id, 0, 1);

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
