#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
 
int main() {
    int fd = open("/dev/fb0", O_RDONLY);
    if (fd < 0) {
        printf("Error opening /dev/fb0: %s\n", strerror(errno));
        return 1;
    }
 
    struct fb_fix_screeninfo fix_info;
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix_info) < 0) {
        printf("Error retrieving fixed screen info: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
 
    printf("Framebuffer ID: %s\n", fix_info.id);
    printf("Memory Start: %lx\n", fix_info.smem_start);
    printf("Memory Length: %u\n", fix_info.smem_len);
    printf("Type: %u\n", fix_info.type);
    printf("Visual: %u\n", fix_info.visual);
    printf("Acceleration: %u\n", fix_info.accel);
 
    close(fd);
    return 0;
}