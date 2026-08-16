#include <stdio.h>
#include <stdlib.h>
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
    // Get the shared memory segment
    int shm_id = shmget(SHM_KEY, SHM_SIZE, 0666);
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

    // Get the semaphore
    int sem_id = semget(SEM_KEY, 1, 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Wait for semaphore to allow access
    performSemaphoreOperation(sem_id, 0, -1);

    // Read data from shared memory
    printf("Data read from shared memory: %s\n", shm_ptr);

    // Release the semaphore
    performSemaphoreOperation(sem_id, 0, 1);

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
