#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h> //toupper()
#define buffer 256
#define fn "bulletin.txt"

// ADD FOPEN VERIFIER
// ADD TOUPPER

typedef struct etudiant {
	int code;
	char nom[buffer], prenom[buffer];
	float noteE, noteO;
}etudiant;

bool verif_code(int code);
int ajouter();
void afficher();
void modifier();
void supprimer();
void moyenne_classe();
void liste_admis();
// void envelope_structure(FILE*fp, etudiant*profil);

int main() {

	int op;

	do {
		// system("CLS");
		printf("\n\n\n\n--------Menu de Gestion des Notes--------\n");
		printf("1. Nouvel etudiant\n2. Afficher bulletin\n3. Modifier le nom d\'un etudiant\n4. Supprimer un etudiant\n5. Afficher la moyenne de la class\n6. Liste des admis\n0. Fin du traitement\nChoix: ");
		scanf("%d", &op);

		FILE*fp=fopen(fn, "a");
		fclose(fp);

		switch(op) {
			case 1: ajouter();
			break;
			case 2: afficher();
			break;
			case 3: modifier();
			break;
			case 4: supprimer();
			break;
			case 5: moyenne_classe();
			break;
			case 6: liste_admis();
			break;
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
	fclose(fp);
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
	scanf("%f", &profil.noteE);
	printf("Note de l\'oral: ");
	scanf("%f", &profil.noteO);

	FILE*fp=fopen(fn, "a");
	fprintf(fp, "%d | %s | %s | %.2f | %.2f\n", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
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
	
	while(fscanf(fp, "%d", &profil.code) && !feof(fp)) {
		printf("---%d---\n", ftell(fp));
		printf("%d\n", profil.code);
		if(profil.code==code) {
			fscanf(fp, " | %s | %s | %f | %f\n", profil.nom, profil.prenom, &profil.noteE, &profil.noteO);
			printf("L\'etudiant ayant le code %d est %s %s, ses notes sont %f et %f.", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
			return;
		} else {
			while((new_line_finder=fgetc(fp))!='\n') {
				fseek(fp, 1, SEEK_CUR);
			}
		}
	}
	printf("Code inexistant.\n");
}

void modifier() {
	char fn_target[]="bulletin_target.txt";
	FILE*fp=fopen(fn, "r");
	FILE*fp_target=fopen(fn_target, "a");
	int code_a_chercher, i;
	etudiant profil;

	printf("Entrez le code de l\'etudiant a modifier: ");
	scanf("%d", &code_a_chercher);

	while(fscanf(fp, "%d | %s | %s | %f | %f", &profil.code, profil.nom, profil.prenom, &profil.noteE, &profil.noteO) && !feof(fp)) {
		if(code_a_chercher==profil.code) {
			printf("Le nom de l\'etudiant est %s. Entrez le nouveau nom: ", profil.nom);
			scanf("%s", profil.nom);
		}
		fprintf(fp_target, "%d | %s | %s | %.2f | %.2f\n", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
	}

	fclose(fp);
	fclose(fp_target);
	remove(fn);
	rename(fn_target, fn);
}

void supprimer() {
	char fn_target[]="bulletin_target.txt";
	FILE*fp=fopen(fn, "r");
	FILE*fp_target=fopen(fn_target, "a");
	int code_a_chercher, i;
	etudiant profil;

	printf("Entrez le code de l\'etudiant a supprimer: ");
	scanf("%d", &code_a_chercher);

	while(fscanf(fp, "%d | %s | %s | %f | %f", &profil.code, profil.nom, profil.prenom, &profil.noteE, &profil.noteO) && !feof(fp)) {
		if(code_a_chercher!=profil.code) {
			fprintf(fp_target, "%d | %s | %s | %.2f | %.2f\n", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
		}
	}

	fclose(fp);
	fclose(fp_target);
	remove(fn);
	rename(fn_target, fn);
}

void moyenne_classe() {
	FILE*fp=fopen(fn, "r");
	etudiant profil;
	float total=0;
	int i=0;

	while(fscanf(fp, "%d | %s | %s | %f | %f", &profil.code, profil.nom, profil.prenom, &profil.noteE, &profil.noteO) && !feof(fp)) {
		total+=profil.noteE+profil.noteO;
		i+=2;
	}

	printf("La moyenne de la classe est %.2f.", total/i);
	fclose(fp);
}

void liste_admis() {
	FILE*fp=fopen(fn, "r");
	etudiant profil;
	bool admis=false;

	printf("Liste des admis:\n");
	while(fscanf(fp, "%d | %s | %s | %f | %f", &profil.code, profil.nom, profil.prenom, &profil.noteE, &profil.noteO) && !feof(fp)) {
		if((profil.noteE+profil.noteO)/2>=10) {
			printf("%d | %s | %s\n", profil.code, profil.nom, profil.prenom);
			admis=true;
		}
	}

	if(!admis) {printf("Personne.\n");}

	fclose(fp);
}