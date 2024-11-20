#include <stdio.h>
#include <stdlib.h>

#define DIM_PLATEAU 9
#define MAX_PSEUDO 50
#define MAX_JOUEURS 4

// Déclaration des sous-programmes (en supposant qu'ils sont déjà définis ailleurs)
void initialisation_plateau(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], 
                             char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], 
                             char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU]);

void affiche_plateau(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], 
                     char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], 
                     char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU]);

void demanderNombreJoueurs(int *nbJoueurs);
void demanderPseudos(int nbJoueurs, char pseudos[][MAX_PSEUDO]);

// Sous-programme pour lancer la partie
void lancerPartie(char plateau_pions[DIM_PLATEAU][DIM_PLATEAU], 
                  char plateau_vbarriere[DIM_PLATEAU][DIM_PLATEAU-1], 
                  char plateau_hbarriere[DIM_PLATEAU-1][DIM_PLATEAU], 
                  int positions[MAX_JOUEURS][2], 
                  int *nbJoueurs, 
                  char pseudos[MAX_JOUEURS][MAX_PSEUDO]) {
    char reponse;

    // Demander à l'utilisateur s'il veut lancer la partie
    printf("Voulez-vous lancer la partie ? (O/N) : ");
    scanf(" %c", &reponse);  // Le " " avant %c pour ignorer les espaces et sauts de ligne

    if (reponse == 'O' || reponse == 'o') {
        // Initialiser le nombre de joueurs et leurs pseudos
        demanderNombreJoueurs(nbJoueurs);
        demanderPseudos(*nbJoueurs, pseudos);

        // Initialisation du plateau
        initialisation_plateau(plateau_pions, plateau_vbarriere, plateau_hbarriere);

        // Affichage du plateau
        affiche_plateau(plateau_pions, plateau_vbarriere, plateau_hbarriere);

        // Initialiser les positions des joueurs (par exemple, positions initiales)
        for (int i = 0; i < *nbJoueurs; i++) {
            positions[i][0] = 4; // Exemple de position initiale (en X)
            positions[i][1] = 4; // Exemple de position initiale (en Y)
        }

        printf("La partie a démarré !\n");
    } else {
        printf("La partie n'a pas été lancée.\n");
    }
}
