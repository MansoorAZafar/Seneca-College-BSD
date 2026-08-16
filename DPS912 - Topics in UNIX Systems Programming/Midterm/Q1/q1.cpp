#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <unistd.h>
 
int main() {
    int fd;
    unsigned long long disk_size;
 
    fd = open("/dev/sda", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
 
    if (ioctl(fd, BLKGETSIZE64, &disk_size) == -1) {
        perror("ioctl");
        close(fd);
        return EXIT_FAILURE;
    }
 
    printf("Disk size: %llu bytes\n", disk_size);
 
    close(fd);
    return 0;
}