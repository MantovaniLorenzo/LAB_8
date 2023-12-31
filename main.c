// VERSIONE 4 DEL PROGRAMMA CON COMPLESSITA' IN PIU'

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct nomi {
	char nome[20];
	char cognome[20];
	char mobile[20];
	char fisso[20];
}Nomi;

int main(void) {

	printf("Il programma gestisce una rubrica di utenti, massimo 100.Inserendo un nominativo, se questo e' gia' presente in rubrica si puo' scegliere di aggiornare i numeri oppure di eliminare il nominativo, mentre se non e' presente, e la rubrica ha spazio, e' possibile aggiungere l'utente. Il programma termina se viene effettuato un errore oppure quando l'utente digita EOF.\n");

	FILE* fp;
	int i= 0, flag = 0, dim, tmp;
	char nome_file[21], str[20];
	Nomi* v;

	// ALLOCAZIONE PER IL VETTORE DI STRUTTURE (CIOè LA RUBRICA)
	v = (Nomi*)malloc(N * sizeof(Nomi));
	if (v == NULL) {
		printf("Errore di allocazione.\n");
		exit(EXIT_FAILURE);
	}


	// APERTURA FILE
	printf("\nInserire il nome del file di input: ");
	scanf("%s", nome_file);

	fp = fopen(nome_file, "r");
	if (fp == NULL) {
		printf("ERRORE di apertura.\n");
		exit(EXIT_FAILURE);
	}


	//LETTURA DA FILE
	while (i < N && fscanf(fp, "%s%s%s%s", v[i].nome, v[i].cognome, v[i].mobile, v[i].fisso) != EOF) {
		i++;
	}

	dim = i; // Nel caso l'utente non abbia utilizzato tutti i 100 posti disponibili in rubrica

	// GESTIONE ELEMENTI
	
	// L'utente inserisce una serie di nominativi, se il nome è presente può decidere di aggiornare i dati oppure eliminare il nominativo
	// la richiesta termina quando l'utente digita EOF

	printf("\nInserire un nominativo: ");

	while (scanf("%s", str)!= EOF) {
		flag = 0;

		for (i = 0; i < dim && flag == 0; i++) {
			if (strcmp(v[i].nome, str) == 0) {
				flag = 1;
				printf("\nInserire 1 se si vuole aggiornare nominativo altrimenti 0 se si vuole eliminare:");
				scanf("%d", &tmp);
				if (tmp == 0 && dim != 0) {   // eliminazione elemento
					for (int j = i; j < dim; j++) {
						v[j] = v[j + 1];
				  }
					dim--;
				}
				else if (tmp == 1) { // aggiornamento elemento 
					printf("\nInserire numero di telefono mobile aggiornato:");
					scanf("%s", v[i].mobile);
					printf("\nInserire numero di telefono fisso aggiornato:");
					scanf("%s", v[i].fisso);
				}
				else {
					printf("FORMATO NON RISPETTATO.\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		// se è arrivato qua non è presente quindi faccio inserimento in coda a tutti gli elementi
		if (flag == 0) {
			if (dim < N) {
				strcpy(v[dim].nome, str);
				printf("\nInserire il cognome:");
				scanf("%s", v[dim].cognome);
				printf("\nInserire numero di telefono mobile:");
				scanf("%s", v[dim].mobile);
				printf("\nInserire numero di telefono fisso:");
				scanf("%s", v[dim].fisso);
				dim++;

			}
			else printf("RUBRICA PIENA IMPOSSIBILE INSERIRE NUOVO NOMINATIVO.\n");

		}

		printf("\nInserire un nominativo:");
	}

	// stampa elementi 

	for (i = 0; i < dim; i++) {
		printf("%s %s %s %s.\n", v[i].nome, v[i].cognome, v[i].mobile, v[i].fisso);
	}

	return 0;
}
