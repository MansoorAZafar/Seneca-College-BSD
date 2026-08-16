// client.h - Header file for shared memory
//
// 23-Jul-20  M. Watler         Created.
//
#ifndef CLIENT_H
#define CLIENT_H

const char MEMNAME[] { "MemDispatch" };
constexpr int SEM_KEY { 5678 };
constexpr int BUF_LEN { 1024 };
constexpr int NUM_MESSAGES { 30 };

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

struct Memory {
    int            packet_no;
    unsigned short srcClientNo;
    unsigned short destClientNo;
    char           message[BUF_LEN];
    bool           begin_processing {false};
};

void *recv_func(void *arg);
namespace L10 {

    constexpr unsigned short MUTEX_SEM { 0 };
    constexpr unsigned short READY_SEM  { 1 };
    constexpr unsigned short DONE_SEM { 2 };
    constexpr int SEM_COUNT { 3 };

    class Semaphore {
    private:
        int id;
        void performSemaphoreOperation(int sem_num, int sem_op) {
            struct sembuf semaphore;
            semaphore.sem_num = sem_num;
            semaphore.sem_op = sem_op;
            semaphore.sem_flg = 0;
        
            if (semop(this->id, &semaphore, 1) == -1) {
                perror("Semaphore operation failed");
                exit(EXIT_FAILURE);
            }
        }
    
    public:
        Semaphore(const key_t& key = 9999, const int nsems = SEM_COUNT, const int flag = IPC_CREAT | IPC_EXCL | 0666)
            : id(::semget(key, nsems, flag)) {
                if(this->id != -1) {
                    // MUTEX, READY, DONE SEM
                    unsigned short values[SEM_COUNT] { 1, 0, 0 };
                    const semun arg { .array = values };

                    this->setSemnum(arg);
                } else if (errno != EEXIST) throw std::system_error(errno, std::system_category(), "semget");
                else {
                    this->id = ::semget(key, nsems, 0666);
                    if (id == -1) throw std::system_error(errno, std::system_category(), "semget existing");
                }
            }
        
        void setSemnum(const semun& arg) {
            if (semctl(this->id, 0, SETALL, arg) == -1 ) throw std::system_error(errno, std::system_category(), "semctl");
        }
        
        void cleanup() { ::semctl(this->id, 0, IPC_RMID); };
        void acquire(const unsigned short& sem_num) { this->performSemaphoreOperation(sem_num, -1); }
        void release(const unsigned short& sem_num) { this->performSemaphoreOperation(sem_num, +1); }
    };
};



#endif//CLIENT_H