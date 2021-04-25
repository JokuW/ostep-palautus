#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main (int argc, char *argv[]){
    int a = 0;
    if(argc = 1){
        count(a);
        exit();
    }
    else if (argc == 2){
        char *comp = "reset";
        if (!strcmp(argv[1],comp)){
            a = 1;
            count(a);
            exit();
        }
        printf(2,"to reset: readcount reset\n");
        exit();
    }

    printf(2, "usage: readcount OR readcount reset\n");
    exit();
}