#include <stdio.h>
void intialisation plateau(char plateau_pions[9][9],char plateau_vbarierre[8][9], char plateau_hbarierre[9][8]) {
    char plateau_pions[9][9];
    char plateau_vbarierre[8][9];
    char plateau_hbarierre[9][8];

    // Initialisation du plateau
    for(int a=0; a<9;a++) {
        for(int b=0;b<9; b++) {
            plateau_pions[a][b]='a';
        }
    }
    for(int a=0; a<9;a++) {
        for(int b=0;b<8; b++) {
            plateau_vbarierre[a][b]='|';
        }
    }
    for(int b=0; b<9;b++) {
        for(int a=0;a<8; a++) {
            plateau_hbarierre[a][b]='_';
        }
    }
    //plateau_pions[1][8]='a';
}
void affciche_plateau(char plateau_pions[9][9],char plateau_vbarierre[8][9], char plateau_hbarierre[9][8]){ // Affichage du plateau
    for(int a=0; a<8;a++) {
        for(int b=0;b<9;b++) {
            if (b==8){
                printf("%c", plateau_pions[a][b]);
            }else{
                printf("%c%c",plateau_pions[a][b],plateau_vbarierre[a][b]);
            }
        }
        printf("\n");
        for(int c=0; c<9; c++) {
            printf("%c ",plateau_hbarierre[a][c]);
        }printf("\n");
    }
    for(int b=0;b<8;b++) {
        printf("%c%c",plateau_pions[8][b],plateau_vbarierre[8][b]);
    }
    printf("%c",plateau_pions[8][8]);

}
