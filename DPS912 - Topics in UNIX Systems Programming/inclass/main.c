#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <signal.h>

#include <time.h>



/* Signal handler for SIGUSR1 */

void sigusr1_handler(int sig) {

  printf("Parent received SIGUSR1 from a child process\n");

}



int main() {

  int num_children, i;

  pid_t pid;



  /* Set up SIGUSR1 handler */

  struct sigaction sa;

  sa.sa_handler = sigusr1_handler;

  sa.sa_flags = 0;

  sigemptyset(&sa.sa_mask);

  sigaction(SIGUSR1, &sa, NULL);



  /* Get number of child processes from user */

  printf("Enter the number of child processes: ");

  scanf("%d", &num_children);



  /* Seed for random sleep time */

  srand(time(NULL));



  for (i = 0; i < num_children; i++) {

    pid = fork();

    

    if (pid == -1) {

      perror("fork failed");

      exit(EXIT_FAILURE);

    }

    if (pid == 0) { // Child process

      printf("Child process created, PID: %d\n", getpid());



      /* Simulate work by sleeping for a random time */

      int sleep_time = (rand() % 5) + 1;

      sleep(sleep_time);



      /* Notify parent by sending SIGUSR1 */

      kill(getppid(), SIGUSR1);



      printf("Child PID %d exiting after %d seconds.\n", getpid(), sleep_time);

      exit(EXIT_SUCCESS);

    }

  }



  /* Parent process waits for all child processes to finish */

  for (i = 0; i < num_children; i++) {

    pid_t child_pid = wait(NULL);

    printf("Child process with PID %d has exited.\n", child_pid);

  }



  printf("Parent process (PID %d) exiting.\n", getpid());

  return 0;

}