#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_PLATEAU 9
#define MAX_PSEUDO 50
#define FICHIER_SAUVEGARDE "partie_sauvegardee.txt"

// Sauvegarde l'état actuel de la partie dans un fichier
void sauvegarderPartie(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], 
                       char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], 
                       char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU], 
                       int positions[MAX_JOUEURS][2], 
                       int nbJoueurs, 
                       char pseudos[MAX_JOUEURS][MAX_PSEUDO]) {
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        exit(1);
    }

    // Sauvegarder le nombre de joueurs
    fprintf(fichier, "%d\n", nbJoueurs);

    // Sauvegarder les pseudos des joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(fichier, "%s\n", pseudos[i]);
    }

    // Sauvegarder les positions des joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(fichier, "%d %d\n", positions[i][0], positions[i][1]);
    }

    // Sauvegarder le plateau de pions
    for (int i = 0; i < DIM_PLATEAU; i++) {
        for (int j = 0; j < DIM_PLATEAU; j++) {
            fprintf(fichier, "%c", plateau_pions[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarder les barrières verticales
    for (int i = 0; i < DIM_PLATEAU; i++) {
        for (int j = 0; j < DIM_PLATEAU-1; j++) {
            fprintf(fichier, "%c", plateau_vbarriere[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarder les barrières horizontales
    for (int i = 0; i < DIM_PLATEAU-1; i++) {
        for (int j = 0; j < DIM_PLATEAU; j++) {
            fprintf(fichier, "%c", plateau_hbarriere[i][j]);
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès !\n");
}

// Fonction pour charger une partie sauvegardée
void chargerPartie(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], 
                   char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], 
                   char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU], 
                   int positions[MAX_JOUEURS][2], 
                   int *nbJoueurs, 
                   char pseudos[MAX_JOUEURS][MAX_PSEUDO]) {
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "r");
    if (!fichier) {
        printf("Aucune partie sauvegardée trouvée.\n");
        return;
    }

    // Charger le nombre de joueurs
    fscanf(fichier, "%d", nbJoueurs);

    // Charger les pseudos des joueurs
    for (int i = 0; i < *nbJoueurs; i++) {
        fscanf(fichier, "%s", pseudos[i]);
    }

    // Charger les positions des joueurs
    for (int i = 0; i < *nbJoueurs; i++) {
        fscanf(fichier, "%d %d", &positions[i][0], &positions[i][1]);
    }

    // Charger le plateau de pions
    for (int i = 0; i < DIM_PLATEAU; i++) {
        for (int j = 0; j < DIM_PLATEAU; j++) {
            fscanf(fichier, " %c", &plateau_pions[i][j]);
        }
    }

    // Charger les barrières verticales
    for (int i = 0; i < DIM_PLATEAU; i++) {
        for (int j = 0; j < DIM_PLATEAU-1; j++) {
            fscanf(fichier, " %c", &plateau_vbarriere[i][j]);
        }
    }

    // Charger les barrières horizontales
    for (int i = 0; i < DIM_PLATEAU-1; i++) {
        for (int j = 0; j < DIM_PLATEAU; j++) {
            fscanf(fichier, " %c", &plateau_hbarriere[i][j]);
        }
    }

    fclose(fichier);
    printf("Partie chargée avec succès !\n");
}
