#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_PLATEAU 9
#define MAX_PSEUDO 50
#define MAX_JOUEURS 4
#define FICHIER_PSEUDOS "pseudos.txt"

// Initialisation des plateaux
void initialisation_plateau(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU]) {
    // Initialisation des pions (cases)
    for (int a = 0; a < DIM_PLATEAU; a++) {
        for (int b = 0; b < DIM_PLATEAU; b++) {
            plateau_pions[a][b] = ' ';
        }
    }

    // Initialisation des barres verticales
    for (int a = 0; a < DIM_PLATEAU; a++) {
        for (int b = 0; b < DIM_PLATEAU-1; b++) {
            plateau_vbarriere[a][b] = '|';
        }
    }

    // Initialisation des barres horizontales
    for (int a = 0; a < DIM_PLATEAU-1; a++) {
        for (int b = 0; b < DIM_PLATEAU; b++) {
            plateau_hbarriere[a][b] = '_';
        }
    }
}

// Affichage du plateau
void affiche_plateau(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU]) {
    for (int a = 0; a < DIM_PLATEAU-1; a++) {
        // Ligne des pions et barres verticales
        for (int b = 0; b < DIM_PLATEAU-1; b++) {
            printf("%c%c", plateau_pions[a][b], plateau_vbarriere[a][b]);
        }
        // Dernier pion de la ligne
        printf("%c\n", plateau_pions[a][DIM_PLATEAU-1]);

        // Ligne des barres horizontales
        for (int b = 0; b < DIM_PLATEAU; b++) {
            printf("%c ", plateau_hbarriere[a][b]);
        }
        printf("\n");
    }

    // Affichage de la dernière ligne de pions
    for (int b = 0; b < DIM_PLATEAU-1; b++) {
        printf("%c%c", plateau_pions[DIM_PLATEAU-1][b], plateau_vbarriere[DIM_PLATEAU-1][b]);
    }
    printf("%c\n", plateau_pions[DIM_PLATEAU-1][DIM_PLATEAU-1]); // Dernier pion
}

// Demande le nombre de joueurs (2 ou 4)
void demanderNombreJoueurs(int *nbJoueurs) {
    do {
        printf("Combien de joueurs vont jouer (2 ou 4) ? ");
        scanf("%d", nbJoueurs);
        if (*nbJoueurs != 2 && *nbJoueurs != 4) {
            printf("Veuillez entrer 2 ou 4.\n");
        }
    } while (*nbJoueurs != 2 && *nbJoueurs != 4);
}

// Vérifie si un pseudo existe dans le fichier
int pseudoExiste(const char *pseudo) {
    FILE *fichier = fopen(FICHIER_PSEUDOS, "r");
    if (!fichier) {
        return 0; // Le fichier n'existe pas encore
    }

    char ligne[MAX_PSEUDO];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        ligne[strcspn(ligne, "\n")] = '\0'; // Supprime le caractère '\n'
        if (strcmp(ligne, pseudo) == 0) {
            fclose(fichier);
            return 1; // Pseudo trouvé
        }
    }

    fclose(fichier);
    return 0; // Pseudo non trouvé
}

// Ajoute un nouveau pseudo dans le fichier
void ajouterPseudo(const char *pseudo) {
    FILE *fichier = fopen(FICHIER_PSEUDOS, "a");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    fprintf(fichier, "%s\n", pseudo);
    fclose(fichier);
}

// Demande et gère les pseudos des joueurs
void demanderPseudos(int nbJoueurs, char pseudos[][MAX_PSEUDO]) {
    for (int i = 0; i < nbJoueurs; i++) {
        char pseudo[MAX_PSEUDO];
        printf("Entrez le pseudo du joueur %d : ", i + 1);
        scanf("%49s", pseudo); // Limite à 49 caractères pour éviter les débordements

        if (pseudoExiste(pseudo)) {
            printf("Le pseudo '%s' existe déjà. Vous êtes associé à celui-ci.\n", pseudo);
        } else {
            printf("Le pseudo '%s' est nouveau. Il est ajouté au fichier.\n", pseudo);
            ajouterPseudo(pseudo);
        }

        strcpy(pseudos[i], pseudo);
    }
}

// Affiche la liste des joueurs
void afficherJoueurs(int nbJoueurs, char pseudos[][MAX_PSEUDO]) {
    printf("\nListe des joueurs :\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("Joueur %d : %s (Insigne : J%d)\n", i + 1, pseudos[i], i + 1);
    }
}

// Déplacer le pion
int deplacerPion(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], int positions[2], int dx, int dy) {
    int xNouveau = positions[0] + dx;
    int yNouveau = positions[1] + dy;

    // Vérifier si le déplacement est dans les limites
    if (xNouveau < 0 || xNouveau >= DIM_PLATEAU || yNouveau < 0 || yNouveau >= DIM_PLATEAU) {
        printf("Déplacement invalide : hors limites !\n");
        return 0;  // Hors limites
    }

    // Vérifier que la case est vide
    if (plateau_pions[xNouveau][yNouveau] != ' ') {
        printf("Déplacement invalide : case occupée !\n");
        return 0;  // Case occupée
    }

    // Déplacer le pion (on suppose que le pion est représenté par un caractère comme 'X')
    plateau_pions[xNouveau][yNouveau] = 'X';  // Nouveau pion
    plateau_pions[positions[0]][positions[1]] = ' ';  // Case précédente vide

    // Mettre à jour la position du joueur
    positions[0] = xNouveau;
    positions[1] = yNouveau;

    return 1;  // Déplacement réussi
}

int main() {
    int nbJoueurs;
    char pseudos[MAX_JOUEURS][MAX_PSEUDO];
    char plateau_pions[DIM_PLATEAU][DIM_PLATEAU];
    char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1];
    char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU];

    // Initialisation du plateau
    initialisation_plateau(plateau_pions, plateau_vbarriere, plateau_hbarriere);

    // Demande du nombre de joueurs
    demanderNombreJoueurs(&nbJoueurs);

    // Demande des pseudos
    demanderPseudos(nbJoueurs, pseudos);

    // Affichage des joueurs
    afficherJoueurs(nbJoueurs, pseudos);

    // Position initiale des joueurs (ici, au centre)
    int positions[MAX_JOUEURS][2];
    for (int i = 0; i < nbJoueurs; i++) {
        positions[i][0] = DIM_PLATEAU / 2;
        positions[i][1] = DIM_PLATEAU / 2;
    }

    // Boucle principale de jeu
    char mouvement;
    int joueurActuel = 0;
    while (1) {
        // Affichage du plateau
        affiche_plateau(plateau_pions, plateau_vbarriere, plateau_hbarriere);

        // Demande à l'utilisateur de choisir un déplacement
        printf("\nJoueur %d (%s), entrez votre mouvement (z = haut, s = bas, q = gauche, d = droite, e = quitter) : ", joueurActuel + 1, pseudos[joueurActuel]);
        scanf(" %c", &mouvement);  // L'espace avant %c permet d'ignorer les retours à la ligne

        if (mouvement == 'e') {
            printf("Fin de la partie.\n");
            break;
        }

        int dx = 0, dy = 0;
        if (mouvement == 'z') dx = -1;  // Déplacement vers le haut
        else if (mouvement == 's') dx = 1;  // Déplacement vers le bas
        else if (mouvement == 'q') dy = -1;  // Déplacement vers la gauche
        else if (mouvement == 'd') dy = 1;  // Déplacement vers la droite

        // Essayer de déplacer le pion
        if (deplacerPion(plateau_pions, positions[joueurActuel], dx, dy)) {
            // Changer de joueur
            joueurActuel = (joueurActuel + 1) % nbJoueurs;
        }
    }

    return 0;
}
