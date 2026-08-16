#ifndef ASSIGNMENT_3_COMMONS_HPP
#define ASSIGNMENT_3_COMMONS_HPP

#include <cstdint>
#include <pthread.h>

namespace AS3 {
    constexpr uint16_t SERVER_PORT { 8080 };

    class Mutex {
    private:
        pthread_mutex_t m_lock;
        bool cleaned { true };        
    public:
        void init() { ::pthread_mutex_init(&this->m_lock, nullptr); this->cleaned = false; }
        void lock() { ::pthread_mutex_lock(&this->m_lock); }
        void unlock() { ::pthread_mutex_unlock(&this->m_lock); }
        void cleanup() { ::pthread_mutex_destroy(&this->m_lock); this->cleaned = true; };
        ~Mutex() { if(!this->cleaned) ::pthread_mutex_destroy(&this->m_lock); }    
    };
};

#endif