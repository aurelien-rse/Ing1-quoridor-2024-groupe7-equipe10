#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PSEUDO 50
#define MAX_JOUEURS 4
#define FICHIER_PSEUDOS "pseudos.txt"

void demanderNombreJoueurs(int *nbJoueurs) {
    do {
        printf("Combien de joueurs vont jouer (2 ou 4) ? ");
        scanf("%d", nbJoueurs);
        if (*nbJoueurs != 2 && *nbJoueurs != 4) {
            printf("Veuillez entrer 2 ou 4.\n");
        }
    } while (*nbJoueurs != 2 && *nbJoueurs != 4);
}

int pseudoExiste(char *pseudo) {
    FILE *fichier = fopen(FICHIER_PSEUDOS, "r");
    if (!fichier) {
        return 0;
    }

    char ligne[MAX_PSEUDO];
    while (fgets(ligne, MAX_PSEUDO, fichier)) {
        ligne[strcspn(ligne, "\n")] = '\0';
        if (strcmp(ligne, pseudo) == 0) {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}

void ajouterPseudo(char *pseudo) {
    FILE *fichier = fopen(FICHIER_PSEUDOS, "a");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    fprintf(fichier, "%s\n", pseudo);
    fclose(fichier);
}

void demanderPseudos(int nbJoueurs, char pseudos[][MAX_PSEUDO]) {
    for (int i = 0; i < nbJoueurs; i++) {
        char pseudo[MAX_PSEUDO];
        printf("Entrez le pseudo du joueur %d : ", i + 1);
        scanf("%s", pseudo);

        if (pseudoExiste(pseudo)) {
            printf("Le pseudo '%s' existe déjà. Vous êtes associé à celui-ci.\n", pseudo);
        } else {
            printf("Le pseudo '%s' est nouveau. Il est ajoute au fichier.\n", pseudo);
            ajouterPseudo(pseudo);
        }

        strcpy(pseudos[i], pseudo);
    }
}

void afficherJoueurs(int nbJoueurs, char pseudos[][MAX_PSEUDO]) {
    printf("\nListe des joueurs :\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("Joueur %d : %s (Insigne : %d)\n", i + 1, pseudos[i], i + 1);
    }
}

int main() {
    int nbJoueurs;
    char pseudos[MAX_JOUEURS][MAX_PSEUDO];

    demanderNombreJoueurs(&nbJoueurs);
    demanderPseudos(nbJoueurs, pseudos);
    afficherJoueurs(nbJoueurs, pseudos);

    return 0;
}
