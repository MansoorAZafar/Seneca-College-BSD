// client3.cpp - An exercise with named semaphores and shared memory
//
// 23-Jul-20  M. Watler         Created.
//
#include <thread>
#include <chrono>
#include <errno.h>
#include <iostream>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <system_error>
#include <condition_variable>
#include <unistd.h>
#include "client.h"

constexpr int CLIENT_NO { 3 };
bool is_running { true };

static void sigHandler(int sig) {
    switch(sig) {
        case SIGINT:
            is_running=false;
            break;
    }
}

int main(void) {
    key_t          ShmKey;
    int            ShmID;
    struct Memory  *ShmPTR;

    //Intercept ctrl-C for controlled shutdown
    struct sigaction action;
    action.sa_handler = sigHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    //key_t ftok(const char *pathname, int proj_id);
    //
    //The ftok() function uses the identity of the file named by the given pathname
    //and the least significant 8 bits of proj_id (which must be nonzero) to
    //generate a key_t type suitable for use with msgget(2), semget(2), or shmget(2).
    ShmKey = ftok(MEMNAME, 65);

    //int shmget(key_t key, size_t size, int shmflg);
    //
    //shmget() returns the identifier of the shared memory segment associated with
    //the value of the argument key.
    //struct Memory {
    //    int           packet_no;
    //    unsigned char sourceIP[4];
    //    unsigned char destIP[4];
    //    char          message[BUF_LEN];
    //};

    ShmID = shmget(ShmKey, sizeof(struct Memory), IPC_CREAT | 0666);
    if (ShmID < 0) {
        std::cout << "client3: shmget() error\n";
        std::cout << strerror(errno) << "\n";
        return -1;
    }

    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //
    //shmat() attaches the shared memory segment identified by shmid to the
    //address space of the calling process. The attaching address is specified
    //by shmaddr. If shmaddr is NULL, the system chooses a suitable (unused)
    //page-aligned address to attach the segment.
    ShmPTR = (struct Memory *) shmat(ShmID, NULL, 0);
    if (ShmPTR == (void *)-1) {
        std::cout << "client3: shmat() error\n";
        std::cout << strerror(errno) << "\n";
        return -1;
    }

    L10::Semaphore semaphore { SEM_KEY };
    std::cout << "[Client 3]: Waiting for Semaphore\n";
    semaphore.acquire(L10::MUTEX_SEM);
    
    //Client 3 starts everything
    ShmPTR->srcClientNo=CLIENT_NO;
    ShmPTR->destClientNo=1;
    
    memset(ShmPTR->message, 0, BUF_LEN);
    sprintf(ShmPTR->message, "This is message 0 from client %d\n", CLIENT_NO);
    ShmPTR->begin_processing = true;

    std::cout << "[Client 3]: Releasing Semaphore\n";
    semaphore.release(L10::MUTEX_SEM);
    // 2 clients, so we release twice
    // semaphore.release(L10::READY_SEM);
    // semaphore.release(L10::READY_SEM);

    for(int i=0; i<NUM_MESSAGES && is_running; ++i) {
        std::cout << "[Client 3]: Waiting for Semaphore\n";
        semaphore.acquire(L10::MUTEX_SEM);
        std::cout << "[Client 3]: Successfully Got Semaphore\n";
        std::cout << "[Client 3]: Accessing Shared Memory\n";
        if(ShmPTR->destClientNo==CLIENT_NO) {
            std::cout << "Client "<< CLIENT_NO << " has received a message from client " << ShmPTR->srcClientNo << ":\n";
            std::cout << ShmPTR->message << "\n";
            
            //Send a message to client 1 or 2
            ShmPTR->srcClientNo=CLIENT_NO;
            ShmPTR->destClientNo=1+i%2;//send a mzessage to client 1 or 2
            
            memset(ShmPTR->message, 0, BUF_LEN);
            sprintf(ShmPTR->message, "This is message %d from client %d\n", i+1, CLIENT_NO);
        }

        std::cout << "[Client 3]: Releasing Semaphore\n";
        semaphore.release(L10::MUTEX_SEM);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Once both clients are done
    semaphore.acquire(L10::DONE_SEM);
    semaphore.acquire(L10::DONE_SEM);

    shmdt((void *)ShmPTR);
    shmctl(ShmID, IPC_RMID, NULL);
    
    semaphore.cleanup();
    std::cout << "client3: DONE\n";

    return 0;
}