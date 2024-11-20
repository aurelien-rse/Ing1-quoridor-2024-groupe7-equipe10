#include <stdio.h>

#define FICHIER_SCORES "scores.txt"

void afficherScores() {
    FILE *fichier = fopen(FICHIER_SCORES, "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier des scores (%s).\n", FICHIER_SCORES);
        return;
    }

    printf("\n    Scores finaux des joueurs    \n");
    char pseudo[50];
    int score;

    while (fscanf(fichier, "%s %d", pseudo, &score) == 2) {
        printf("%s : %d points\n", pseudo, score);
    }
    printf("                      \n");

    fclose(fichier);
}

int main() {
    afficherScores();
    return 0;
}
