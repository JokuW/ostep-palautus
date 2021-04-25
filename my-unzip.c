/* Lähteenä käyettetty:
https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://stackoverflow.com/questions/9180006/how-to-use-fread-and-fwrite-functions-to-read-and-write-binary-files
https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
*/

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]){
    if (argc == 1){ // Onko argumentteja annettu
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *tied;
    int laske, kirj;

    for (size_t i = 1; i < argc; i++){  // Käydään argumentit läpi
        if ((tied = fopen(argv[i], "r")) == NULL){
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }

        while (fread(&laske, sizeof(int), 1, tied) != 0){ // Otetaan määrä
            if ((fread(&kirj, sizeof(char), 1, tied)) == 0){ // Otetaan kirjain
                fprintf(stderr, "my-unzip: error reading file\n");
                exit(1);
            }
            for (size_t i = 0; i < laske; i++){ // Puretaan
                printf("%c", kirj);
            }
        }
        fclose(tied);
        printf("\n");
    }
    return 0;
}