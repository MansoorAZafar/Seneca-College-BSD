//sysmonExec.cpp - A system monitor using fork and exec
//
// 13-Jul-20  M. Watler         Created.

#include <fcntl.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <thread>

#define SLEEP_TIME 30

using namespace std;
const int NUM=2;

int systemMonitor();
bool isRunning=true;
bool isParent = true;//Distinguishes between the parent
                     //process and the child process(es)
pid_t childPid[NUM];

char *intf[]={"lo", "ens33"};

int discardCount {0};
int bgCount {0};
void signalHandler(int signal) {
    switch(signal) {		
		// Handle Ctrl + C
		case SIGINT:
			std::cout << "ctrl-C discarded\n";
            discardCount += 3;
			break;

		// Handle Ctrl + z
		case SIGTSTP:
            bgCount += 3;
			std::cout << "ctrl-Z discarded\n";
			break;

		default:
			std::cout << "undefined signal";
	}
}

int main()
{
    struct sigaction action {};
	action.sa_handler = signalHandler;
	
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	auto safe_sigaction = [&action](int __sig, const char* prefix, struct sigaction* old = NULL) {
		if(sigaction(__sig, &action, old) == -1) {
			std::cerr << "[Sigaction]: " << prefix << "\n";
			std::exit(1);
		}
	};
	
	safe_sigaction(SIGINT,  "SIGINT ");
	safe_sigaction(SIGTSTP, "SIGTSTP");
    std::cout << "[REGISTER SIGNALS]\n";

    cout << endl << "parent:main: pid:"<<getpid()<<endl;
    for(int i=0; i<NUM & isParent; ++i) {
        childPid[i] = fork();
        if(childPid[i]==0) {//the child
            cout << "child:main: pid:"<<getpid()<<endl;
            isParent=false;
            execlp("./intfMonitor", "./intfMonitor", intf[i], NULL);
            cout << "child:main: pid:"<<getpid()<<" I should not get here!"<<endl;
	        cout<<strerror(errno)<<endl;
        }
    }
    if(isParent) {
        // sleep(10);
        std::this_thread::sleep_for(std::chrono::seconds(10));
        systemMonitor();
    }

    cout << "parent:main("<<getpid()<<"): Finished!" << endl;
    return 0;
}

int systemMonitor()//run by the parent process
{
    int status=-1;
    pid_t pid=0;
    //TODO: Send start signals to the children (SIGUSR1)
    for(const pid_t& pid : childPid) kill(pid, SIGUSR1);

    //TODO: sleep for 30 seconds
    std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));

    //TODO: Send stop signals to the children (SIGUSR2)
    for(const pid_t& pid : childPid) kill(pid, SIGUSR2);

    //Wait for children to terminate
    while(pid>=0) {
        pid=wait(&status);//blocking. waitpid() is non-blocking and
                          //waits for a specific pid to terminate
        cout << "parent:systemMonitor: status:"<<status<<". The child pid:"<<pid<<" has finished"<< endl;
    }

    return 0;
}