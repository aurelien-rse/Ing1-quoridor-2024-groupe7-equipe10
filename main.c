#include <stdio.h>
#include <stdlib.h>

#include "Source.c"
#include "header.h"
#include "time.h"
int nbrjoueur=2 ;
char plateau_joueur[9][9];
char plateau_vbarierre[8][9];
char plateau_hbarierre[9][8];
int a_jouer=0;
int alea2j;
int aleaj4;
int a=0,b=0,c=0,d=0;
int main(void) {
    intialisation_plateau(plateau_joueur,plateau_vbarierre,plateau_hbarierre);
    srand(time(NULL));
    if(nbrjoueur==2) {
        alea2j=rand()%2;
        if (alea2j==0) {
            printf("PP1");
            while(a==0 && b==0) {// vérifier qu'il n'y a pas de gagnant
                b=verifier_ligne2(plateau_joueur,b);
                a_jouer=menu_joue(a_jouer);
                while(a_jouer==0) {
                    printf("C'est au joueur 1 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                a=verifier_ligne1(plateau_joueur,a);
                printf("PP2");
                while(a_jouer==0) {
                    printf("C'est au joueur 2 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                b=verifier_ligne2(plateau_joueur,b);
            }
        }

        if (alea2j==1) {// vérifier qu'il n'y a pas de gagnant
            while(a==0 && b==0) {
                while(a_jouer==0) {
                    printf("C'est au joueur 2 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                a=verifier_ligne1(plateau_joueur,a);
                while(a_jouer==0) {
                    printf("C'est au joueur 1 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer =0;
                b=verifier_ligne2(plateau_joueur,b);
            }
        }
    }
    if(nbrjoueur==4) {
        aleaj4=rand()%4;
        if (aleaj4==0) {
            while(a==0 && b==0 && c==0 && d==0) {// vérifier qu'il n'y a pas de gagnant
                b=verifier_ligne2(plateau_joueur,b);
                a_jouer=menu_joue(a_jouer);
                c=verifier_colonne1(plateau_joueur,c);
                d=verifier_colonne1(plateau_joueur,d);
                while(a_jouer==0) {
                    printf("C'est au joueur 2 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                a=verifier_ligne1(plateau_joueur,a);
                while(a_jouer==0) {
                    printf("C'est au joueur 1 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                b=verifier_ligne2(plateau_joueur,b);
                while(a_jouer==0) {
                    printf("C'est au joueur 4 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                c=verifier_ligne2(plateau_joueur,c);
                while(a_jouer==0) {
                    printf("C'est au joueur 3 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                d=verifier_ligne2(plateau_joueur,d);
            }
        }
        if (aleaj4==1) {
            while(a==0 && b==0 && c==0 && d==0) {// vérifier qu'il n'y a pas de gagnant
                b=verifier_ligne2(plateau_joueur,b);
                a_jouer=menu_joue(a_jouer);
                c=verifier_colonne1(plateau_joueur,c);
                d=verifier_colonne1(plateau_joueur,d);
                while(a_jouer==0) {
                    printf("C'est au joueur 3 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                d=verifier_ligne2(plateau_joueur,d);
                while(a_jouer==0) {
                    printf("C'est au joueur 2 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                a=verifier_ligne1(plateau_joueur,a);
                while(a_jouer==0) {
                    printf("C'est au joueur 4 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                c=verifier_ligne2(plateau_joueur,c);
                while(a_jouer==0) {
                    printf("C'est au joueur 1 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                b=verifier_ligne2(plateau_joueur,b);
            }
        }
        if (aleaj4==2) {
            while(a==0 && b==0 && c==0 && d==0) {// vérifier qu'il n'y a pas de gagnant
                b=verifier_ligne2(plateau_joueur,b);
                a_jouer=menu_joue(a_jouer);
                c=verifier_colonne1(plateau_joueur,c);
                d=verifier_colonne1(plateau_joueur,d);
                while(a_jouer==0) {
                    printf("C'est au joueur 4 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                c=verifier_ligne2(plateau_joueur,c);
                while(a_jouer==0) {
                    printf("C'est au joueur 3 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                d=verifier_ligne2(plateau_joueur,d);
                while(a_jouer==0) {
                    printf("C'est au joueur 2 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                a=verifier_ligne1(plateau_joueur,a);
                while(a_jouer==0) {
                    printf("C'est au joueur 1 de jouer\n");
                    a_jouer=menu_joue(a_jouer);
                }
                a_jouer=0;
                b=verifier_ligne2(plateau_joueur,b);
            }
        }
    }if (aleaj4==3) {
        while(a==0 && b==0 && c==0 && d==0) {// vérifier qu'il n'y a pas de gagnant
            b=verifier_ligne2(plateau_joueur,b);
            a_jouer=menu_joue(a_jouer);
            c=verifier_colonne1(plateau_joueur,c);
            d=verifier_colonne1(plateau_joueur,d);
            while(a_jouer==0) {
                printf("C'est au joueur 1 de jouer\n");
                a_jouer=menu_joue(a_jouer);
            }
            a_jouer=0;
            b=verifier_ligne2(plateau_joueur,b);
            while(a_jouer==0) {
                printf("C'est au joueur 3 de jouer\n");
                a_jouer=menu_joue(a_jouer);
            }
            a_jouer=0;
            d=verifier_ligne2(plateau_joueur,d);
            while(a_jouer==0) {
                printf("C'est au joueur 2 de jouer\n");
                a_jouer=menu_joue(a_jouer);
            }
            a_jouer=0;
            a=verifier_ligne1(plateau_joueur,a);
            while(a_jouer==0) {
                printf("C'est au joueur 4 de jouer\n");
                a_jouer=menu_joue(a_jouer);
            }
            a_jouer=0;
            c=verifier_ligne2(plateau_joueur,c);
        }
    }
}
