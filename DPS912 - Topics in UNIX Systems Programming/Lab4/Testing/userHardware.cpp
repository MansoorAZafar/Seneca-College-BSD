//userHardware.cpp - user level code for using a hardware device
//
// 29-Dec-20  M. Watler         Created.
//
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include "../hardwareDevice.h"

const char devFile[]="/dev/hardware";
const int  BUF_LEN=16;

using namespace std;

int main()
{
    int fd, rc=0;
    char buf[BUF_LEN];
    int  nbytes;

    fd=open(devFile, O_RDWR);
    if(fd < 0) {
        printf("Cannot open the device file...\n");
        rc=-1;
    }
    if(rc==0) {

        int status;
 
        if (ioctl(fd, HARDWARE_DEVICE_GET_STATUS, &status) == -1) {
            perror("Unable to retrieve device status");
        } else {
            cout << "Device status: "
                << (status == 1 ? "RUNNING" : "HALTED")
                << endl;
        }

        for(int i=0; i<3; ++i) {
            nbytes=read(fd, buf, BUF_LEN);
            printf("nbytes:%d = read() buf:%s\n", nbytes, buf);
            sleep(3);
        }

        printf("HARDWARE_DEVICE_HALT...\n");
        ioctl(fd, HARDWARE_DEVICE_HALT, NULL);
        if (ioctl(fd, HARDWARE_DEVICE_GET_STATUS, &status) == -1) {
            perror("Unable to retrieve device status");
        } else {
            cout << "Device status: "
                << (status == 1 ? "RUNNING" : "HALTED")
                << endl;
        }
        for(int i=0; i<3; ++i) {
            nbytes=read(fd, buf, BUF_LEN);
            printf("nbytes:%d = read() buf:%s\n", nbytes, buf);
            sleep(3);
        }
        
        printf("HARDWARE_DEVICE_RESUME...\n");
        ioctl(fd, HARDWARE_DEVICE_RESUME, NULL);
        if (ioctl(fd, HARDWARE_DEVICE_GET_STATUS, &status) == -1) {
            perror("Unable to retrieve device status");
        } else {
            cout << "Device status: "
                << (status == 1 ? "RUNNING" : "HALTED")
                << endl;
        }
        for(int i=0; i<3; ++i) {
            nbytes=read(fd, buf, BUF_LEN);
            printf("nbytes:%d = read() buf:%s\n", nbytes, buf);
            sleep(3);
        }
    }

    close(fd);

    return rc;
}