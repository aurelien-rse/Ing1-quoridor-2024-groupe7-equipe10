#include <stdio.h>
void affiche_menu( int menu) {
    printf("1.Lancer une partie \n");
    printf("2.Reprendre une partie \n");
    printf("3.Affiche aide \n");
    printf("4.Afficher scores et jouueurs\n");
    printf("5.Quitter \n");
    scanf(" %d",&menu);
    switch(menu){
        case 1:
            printf("1.Lancer une partie \n");
        break;
        case 2:
            printf("2.Reprendre une partie \n");
        break;
        case 3:
            printf("3.Affiche aide \n");
        break;
        case 4:
            printf("4.Afficher scores et jouueurs \n");
        break;
        case 5:
            break;
    }
}
