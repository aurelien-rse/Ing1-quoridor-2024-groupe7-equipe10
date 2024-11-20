#include <stdio.h>

void afficherAide() {
    printf("\n    Aide : Regles du jeu Quoridor     \n");
    printf("1. Le but est d'atteindre en premier la ligne opposee au point de depart.\n");
    printf("2. Les joueurs jouent chacun leur tour, avec comme possibilite :\n");
    printf("   - Deplacer son pion d’une case (avant, arrière, gauche, droite).\n");
    printf("   - Poser une barriere pour ralentir les adversaires.\n");
    printf("3. Les barrieres ne doivent pas bloquer totalement les chemins.\n");
    printf("4. Le premier a atteindre la ligne en face gagne 5 points.\n");
    printf("5. En cas de blocage total, il n’y a pas de gagnant.\n");
    printf("6. Chaque partie met à jour les scores des joueurs.\n");
    printf("7. Le deplacement ne peut pas traverser une barrière ou sortir du plateau.\n");
}
