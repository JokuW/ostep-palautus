/* Lähteenä käyettetty:
https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://stackoverflow.com/questions/9180006/how-to-use-fread-and-fwrite-functions-to-read-and-write-binary-files
*/

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]){
    if (argc == 1){ // Onko argumentteja annettu
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    FILE *tied;
    int nyk, seur;

    for (size_t i = 1; i < argc; i++){ // Käydään argumentit läpi
        if ((tied = fopen(argv[i], "r")) == NULL){
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }

        int laske = 0;
        while ((nyk = fgetc(tied)) != EOF){ // Luetaan tiedosto kirjain kerrallaan
            if (seur == nyk){laske++;} // Sama kirjain
            else if (laske == 0){seur = nyk; laske++;} // Ei kirjainta
            else {     // Kirjain vaihtuu
                fwrite(&laske, sizeof(int), 1, stdout); // Monta, 4 byte
                fwrite(&seur, sizeof(char), 1, stdout); // Mitä, 1 byte
                laske = 1;
                seur = nyk;
            }
        }
        fclose(tied);
        printf("\n");
    }

    return 0;
}