// Lähteenä käyettetty: https://man7.org/linux/man-pages/man3/getline.3.html

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]){

    if (argc == 1){ // Onko annettu tiedosto(ja)
        exit(0);
    }

    FILE *tied;
    char *rivi = NULL;
    size_t koko = 0;
    ssize_t lukuk;

    for (size_t i = 1; i < argc; i++){ // Käydään annetut argumentit läpi
        if ((tied = fopen(argv[i], "r")) == NULL){ // Onnistuuko tiedoston avaus
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);
        }

        while ((lukuk = getline(&rivi, &koko, tied)) != -1){ // Kirjoitetaan luettu tiedosto rivi riviltä
            fwrite(rivi, lukuk, 1, stdout);
        }

        free(rivi);
        fclose(tied);
        printf("\n");
    }
    return 0;
}