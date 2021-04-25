/* Lähteenä käyettetty:
https://man7.org/linux/man-pages/man3/getline.3.html
https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char const *argv[]){

    if (argc == 1){ // Onko argumentteja annettu
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    char *rivi = NULL;
    size_t koko = 0;
    ssize_t  lukuk;

    if (argc == 2){ // Vain hakusana
        lukuk = getline(&rivi, &koko, stdin);

        if (strstr(rivi, argv[1]) != NULL){ // Löytyykö hakusana
            fwrite(rivi, lukuk, 1, stdout);
        }
    }

    else if (argc > 2){ // Tiedostoista etsintä
        
        FILE *tied;

        for (size_t i = 2; i < argc; i++){
            if ((tied = fopen(argv[i], "r")) == NULL){
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            }

            while ((lukuk = getline(&rivi, &koko, tied)) != -1){
                if(strstr(rivi, argv[1]) != NULL){  // Löytyykö hakusana
                    fwrite(rivi, lukuk, 1, stdout);
                }
            }
            printf("\n");
            free(rivi);
            fclose(tied);
        }
    }

    return 0;
}