/* Lähteenä käyetty:
https://man7.org/linux/man-pages/man3/getline.3.html
https://www.tutorialspoint.com/c_standard_libary/c_funtion_strtok.htm
https://stackoverflow.com/questions/13000047/function-to-remove-newline-has-no-effect
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct lista {		// Määritetään linkitetty lista
	char *data;
	struct lista *edellinen;
};
typedef struct lista linkitetty;

void manual();		// Määritetään käytetyt aliohjelmat
void yksi(char const *argv[]);
void kaksi(char const *argv[]);

int main(int argc, char const *argv[]) {	// Määritetään mitä aliohjelmaa käytetään argumenttien määrän perusteella

	if (argc == 1){
		manual(argv);
		exit(0);
	}

	if (argc == 2){
		yksi(argv);
		exit(0);
	}

	if (argc == 3){
		if (!strcmp(argv[1], argv[2])){		// Tarkastetaan ettei ole samat tiedostot
		fprintf(stderr, "ERROR: Input and output file must differ\n");
		exit(1);
		}
		else {
			kaksi(argv);
			exit(0);
		}
	}

	if (argc > 3) {	// Virhe viesti jos yli 3 argumenttia
		fprintf(stderr, "USAGE: reverse <input> <output>\n");
		exit(1);
	}

	return 0;
}

void manual(){ // Luetaan inputista käännettävä teksti
	char *rivi = NULL, *jako, *temp;
	size_t len = 0;
	ssize_t lukuk;
	linkitetty *ptr = NULL, *ptrVanha = NULL;

	printf("Write the text you want to reverse, diveded by spaces:\n");

	if ((lukuk = getline(&rivi, &len, stdin)) == -1) {
		fprintf(stderr, "ERROR: Reading input failed\n");
		exit(1);
	}

	if (rivi[lukuk - 1] == '\n'){
		rivi[lukuk - 1] = '\0';
		--lukuk;
	}

	jako = strtok(rivi, " ");

	while (jako != NULL){
		if ((ptr = (linkitetty *)malloc(sizeof(linkitetty))) == NULL) {
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		if ((temp = (char *)malloc(lukuk * sizeof(char))) == NULL){
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		strcpy(temp,jako);		// Laitetaan input linkitettyyn listaan
		ptr->data = temp;
		ptr->edellinen = ptrVanha;
		ptrVanha = ptr;
		jako = strtok(NULL, " ");
	}

	printf("\n");
	while (ptr != NULL) {		//Luetaan lista läpi lopusta alkaen
		printf("%s\n", ptr->data);
		free(ptr->data);
		ptr = ptr->edellinen;
		free(ptrVanha);
		ptrVanha = ptr;
	}
	free(rivi);
	printf("\n");
}

void yksi(char const *argv[]){	// Käännetään tiedostossa oleva teksti terminaaliin
	FILE *stream;
	char *rivi = NULL, *temp;
	size_t len = 0;
	ssize_t lukuk;
	linkitetty *ptr = NULL, *ptrVanha = NULL;

	stream = fopen(argv[1], "r");
	if (stream == NULL){
		fprintf(stderr, "ERROR: Cannot open file '%s*\n", argv[1]);
		exit(1);
	}

	while ((lukuk = getline(&rivi, &len, stream)) != -1){
		if (rivi[lukuk - 1] == '\n'){
            rivi[lukuk - 1] = '\0';
            --lukuk;
    	}

		if ((ptr = (linkitetty *)malloc(sizeof(linkitetty))) == NULL){
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		if ((temp = (char*)malloc(lukuk * sizeof(char))) == NULL){
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		strcpy(temp, rivi);	// Luetaan tiedosto linkitettyyn listaan
		ptr->data = temp;
		ptr->edellinen = ptrVanha;
		ptrVanha = ptr;	
	}
	free(rivi);
	fclose(stream);

	while( ptr != NULL){		// Tulostetaan linkitettylista terminaaliin
		printf("%s\n", ptr->data);
		free(ptr->data);
		ptr = ptr->edellinen;
		free(ptrVanha);
		ptrVanha = ptr;
	}
}

void kaksi(char const *argv[]){	// Kirjoitetaan käännettynä tiedostosta tiedostoon

	FILE *streamIN, *streamOUT;
	char *rivi = NULL, *temp;
	size_t len = 0;
	ssize_t lukuk;
	linkitetty *ptr = NULL, *ptrVanha = NULL;

	streamIN = fopen(argv[1], "r");
	if (streamIN == NULL){
		fprintf(stderr, "ERROR: Cannot open file '%s*\n", argv[1]);
		exit(1);
	}

	streamOUT = fopen(argv[2], "w");
	if (streamOUT == NULL){
		fprintf(stderr, "ERROR: Cannot open file '%s*\n", argv[2]);
		exit(1);
	}

	while ((lukuk = getline(&rivi, &len, streamIN)) != -1){
		if (rivi[lukuk - 1] == '\n'){
            rivi[lukuk - 1] = '\0';
            --lukuk;
    	}

		if ((ptr = (linkitetty *)malloc(sizeof(linkitetty))) == NULL){
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		if ((temp = (char*)malloc(lukuk * sizeof(char))) == NULL){
			fprintf(stderr, "ERROR: Malloc failed\n");
			exit(1);
		}

		strcpy(temp, rivi);		// Luetaan eka tiedosto linkitettyynlistaan
		ptr->data = temp;
		ptr->edellinen = ptrVanha;
		ptrVanha = ptr;
	}
	free(rivi);
	fclose(streamIN);

	while (ptr != NULL){
		fprintf(streamOUT, "%s\n", ptr->data);	// Kirjoitetaan linkitettylista toiseen tiedostoon
		free(ptr->data);
		ptr = ptr->edellinen;
		free(ptrVanha);
		ptrVanha = ptr;
	}
	fclose(streamOUT);
}