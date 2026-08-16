#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <unistd.h>

int main() {

  int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

  if (fd < 0) { perror("open"); return 1; }



  dup2(fd, STDOUT_FILENO);

  printf("unx511\n");

  close(fd);

  return 0;

}