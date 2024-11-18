#include <stdio.h>


typedef struct {
    int x; // Coordonnée horizontale
    int y; // Coordonnée verticale
} Position;


void deplacerJoueur(Position *joueur) {
    char direction;
    printf("Entrez une direction ('z': haut, 's': bas, 'q': gauche, 'd': droite) : ");
    scanf(" %c", &direction); 

    switch (direction) {
        case 'z': 
            joueur->y -= 1;
        break;
        case 's': 
            joueur->y += 1;
        break;
        case 'q': 
            joueur->x -= 1;
        break;
        case 'd': 
            joueur->x += 1;
        break;
        default:
            printf("Commande invalide !\n");
        return;
    }

    
    printf("Nouvelle position : (%d, %d)\n", joueur->x, joueur->y);
}

int main() {
   
    Position joueur = {0, 0};

    printf("Position initiale : (%d, %d)\n", joueur.x, joueur.y);

    
    deplacerJoueur(&joueur);

    return 0;
}
