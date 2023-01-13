#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define buffer 256

typedef struct etudiant {
    int code;
    char nom[buffer], prenom[buffer];
    float noteE, noteO;
}etudiant;

void ajouter(FILE*fp);
void afficher(FILE*fp, int code);
void modifier(FILE*fp, int code, char*nom);
void supprimer(FILE*fp, int code);
void moyenne_classe(FILE*fp);
void liste_admis(FILE*fp);

int main() {

    int op;
    FILE*fp=fopen("bulletin.txt", "w");

    do {
        // system("CLS");
        printf("\n\n\n\n--------Menu de Gestion des Notes--------\n");
        printf("1. Nouvel etudiant\n2. Afficher bulletin\n3. Modifier le nom d\'un etudiant\n4. Supprimer un etudiant\n5.Afficher la moyenne de la class\n6. Liste des admis\n0. Fin du traitement\nChoix: ");
        scanf("%d", &op);

        switch(op) {
            case 1: printf("Entrez le profil");
            break;

            default: printf("Erreur 404.\nChoix Invalide.");
            break;
        }
    }while(op);

    return 0;
}

void ajouter(FILE*fp) {
    etudiant profil;
    printf("\nNouvel etudiant\nInput du profil:\n");
    printf("Code: ");
    scanf("%d", &profil.code);
    printf("Nom: ");
    gets(profil.nom);
    printf("Prenom: ");
    gets(profil.prenom);
    printf("Note de l\'ecrit: ");
    scanf("%f", &profil.noteE);
    printf("Note de l\'oral: ");
    scanf("%f", &profil.noteO);
    fprintf(fp, "%d | %s | %s | %f | %f", profil.code, profil.nom, profil.prenom, profil.noteE, profil.noteO);
}