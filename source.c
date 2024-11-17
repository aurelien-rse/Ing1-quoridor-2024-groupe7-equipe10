int placerbarierre(int a_jouer,int nbrbarierre,char plateau_pions[9][9],char plateau_vbarierre[8][9], char plateau_hbarierre[9][8]) {
    printf("\nBarriere restant:\n");
    for(int i=0;i<nbrbarierre;i++) {
        printf("B ");
    }
    //coordonné
    int y1,y2,x1,x2,ortbarriere,position;//ordonnés
    char a1,a2;//abcisse
    //vérification du nombre de barierre

    if (nbrbarierre>0) {
        //demande de la position de la barriere
        printf("\nDans quel orientation voulez vous posez la barriere?");
        printf("\n1.horizontale\n2.vertical\n");
        scanf("%d",&ortbarriere);
        //printf("%d",ortbarriere);
        //Demande ou poser la barierre
        printf("\nEcrire l'abcisse de la premiere case:");
        scanf(" %c",&a1);

        printf("\nEcrire l'ordonne de la premiere case:");
        scanf(" %d",&y1);

        x1=a1;
        x1=x1-65;
        y1=y1-1;
        printf("\nEcrire l'abcisse de la deuxieme case:");
        scanf(" %c",&a2);

        printf("\nEcrire l'ordonne de la deuxieme case:");
        scanf(" %d",&y2);

        x2=a2;
        x2=x2-65;
        y2=y2-1;
        printf("\n%d %d %d %d",x1,x2,y1,y2);
        //on vérifie si les cases sont bien dans le plateau
        if(y1<0||y1>8){
            printf("\nLes coordonnees ne sont pas bonne.");
            // Savoir revenir en arriere
        }
        if (x1<0||x1>8) {
            printf("\nLes coordonnees ne sont pas bonne.");
        }
        if(y2<0||y2>8){
            printf("\nLes coordonnees ne sont pas bonne.");
        }
        if ((x2<0||x2>8)) {
            printf("\nLes coordonnees ne sont pas bonne.");
        }
        if (ortbarriere!=1 && ortbarriere!=2) {
            printf("vous n'avez pas selectionné d'orientation");
        }
        //vérification des conditions
        if (x1==x2) {
            if (y1-y2==1 || y1-y2==-1){
            // vérification de l'adjacence
            if (ortbarriere==2) {
                printf("\n1.pour mettre la barriere a droit \n2.Pour la mettre a gauche");
                scanf(" %d",&position);
                if (position!=1 && position!=2) {
                    printf("\nVous n'avez pas choisi de position");
                }
                //pose de la barrière
                if (position==2 && y1!=0){
                    if  (plateau_vbarierre[y1][x1-1]=='|' && plateau_vbarierre[y2][x2-1]!='|') {
                        plateau_vbarierre[y1][x1-1]='B';
                        plateau_vbarierre[y2][x2-1]='B';
                        nbrbarierre--;
                        return ++a_jouer;
                    }
                }
                if (position==1 && y1!=8) {
                    if  (plateau_vbarierre[y1][x1]=='|' && plateau_vbarierre[y2][x2]=='|') {
                        plateau_vbarierre[y1][x1]='B';
                        plateau_vbarierre[y2][x2]='B';
                        nbrbarierre--;
                        return ++a_jouer;
                    }
                }else {
                    printf("\nIl y a deja une barriere la");
                }
            }else {
                printf("\norientation pas bonne");
            }
        }else {
            printf("cases non adjacente");
        }
        } else if (y1==y2) {
            if (x1-x2==1 || x1-x2==-1){
                // vérification de l'adjacence
                if (ortbarriere==1) {
                    printf("\n1.pour mettre la barriere en bas\n2.Pour la mettre a haut\n");
                    scanf(" %d",&position);
                    if (position!=1 && position!=2) {
                        printf("\nVous n'avez pas choisi de position");
                    }

                    //pose de la barrière
                    if (position==2 && y1!=0) {
                        if (plateau_hbarierre[y1-1][x1]=='_' && plateau_hbarierre[y2-1][x2]=='_') {
                            plateau_hbarierre[y1-1][x1]='B';
                            plateau_hbarierre[y2-1][x2]='B';
                            nbrbarierre--;
                            return ++a_jouer;
                        }

                    }
                    if (position==1 && y1!=8) {
                        if (plateau_hbarierre[y1][x1]=='_' && plateau_hbarierre[y2][x2]=='_') {
                            plateau_hbarierre[y1][x1]='B';
                            plateau_hbarierre[y2][x2]='B';
                            nbrbarierre--;
                            return ++a_jouer;
                        }
                    }else {
                    }
                }else {
                    printf("\norientation pas bonne");
                }
            }else {
                printf("cases non adjacente");
            }
        }else {
            printf("cases non adjacente");
        }
    }else {
        printf("\nPlus de barriere disponible");
    }
}
            printf("cases non adjacente");
        }
    }else {
        printf("\nPlus de barriere disponible");
    }
}
