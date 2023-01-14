#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#define buffer 256
#define fn "bulletin.txt"

// ADD FOPEN VERIFIER

typedef struct etudiant {
	int code;
	char nom[buffer], prenom[buffer];
	float noteE, noteO;
}etudiant;

bool verif_code(int code);
int ajouter();
void afficher();
void modifier();
// void supprimer();
// void moyenne_classe();
// void liste_admis();

int main() {

	int op;

	do {
		// system("CLS");
		printf("\n\n\n\n--------Menu de Gestion des Notes--------\n");
		printf("1. Nouvel etudiant\n2. Afficher bulletin\n3. Modifier le nom d\'un etudiant\n4. Supprimer un etudiant\n5. Afficher la moyenne de la class\n6. Liste des admis\n0. Fin du traitement\nChoix: ");
		scanf("%d", &op);

		switch(op) {
			case 1: ajouter();
			break;
			case 2: afficher();
			break;
			case 3: modifier();
			break;
			// case 4: supprimer();
			// break;
			// case 5: moyenne_classe();
			// break;
			case 0: printf("Fin du traitement"); continue;
			break;
			default: printf("Erreur 404.\nChoix Invalide.");
			break;
		}
	}while(op);

	return 0;
}

bool verif_code(int code) {
	FILE*fp=fopen(fn, "r");
	int temp_code;
	char new_line_finder;
	while(fscanf(fp, "%d", &temp_code) && !feof(fp)) {
		if(temp_code==code) {
			return false;
		}
		while((new_line_finder=fgetc(fp))!='\n') fseek(fp, 1, SEEK_CUR);
	}
	return true;
}

int ajouter() {

	etudiant profil;
	printf("\nNouvel etudiant\nInput du profil\n");
	printf("Code: ");
	scanf("%d", &profil.code);
	
	if(!verif_code(profil.code)) {printf("Code existant.\n"); return 1;}

	printf("Nom: ");
	scanf("%s", profil.nom);
	printf("Prenom: ");
	scanf("%s", profil.prenom);
	printf("Note de l\'ecrit: ");
	scanf("%.2f", &profil.noteE);
	printf("Note de l\'oral: ");
	scanf("%.2f", &profil.noteO);
	FILE*fp=fopen(fn, "a");
	fprintf(fp, "%d | %s | %s | %f | %f\n", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
	fclose(fp);
	printf("Profil ajoute.");
	return 0;
}

void afficher() {
	FILE*fp=fopen(fn, "r");
	etudiant profil;
	int code;
	char new_line_finder;
	printf("\nEntrez le code a afficher: ");
	scanf("%d", &code);
	
	while(!feof(fp)) {
		fscanf(fp, "%d", &profil.code);
		if(profil.code==code) {
			fscanf(fp, " | %s | %s | %f | %f\n", profil.nom, profil.prenom, &profil.noteE, &profil.noteO);
			printf("L\'etudiant ayant le code %d est %s %s, ses notes sont %f et %f.", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
			return;
		} else {
			while(fgetc(fp)!=EOF && (new_line_finder=fgetc(fp))!='\n') {
				fseek(fp, 1, SEEK_CUR);
			}
		}
	}
	printf("Code inexistant.\n");
}
