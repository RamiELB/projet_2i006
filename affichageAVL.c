#include "affichageAVL.h"

void affichage_avl(ABR abr){
    if(abr != NULL){
        affichage_avl_rec(abr, 0);
    }
}

void affichage_noeud(Noeud* n){
    printf("%f", n->y);
}

void affichage_avl_rec(ABR abr, int niveau){
    if(abr->fd != NULL){
        affichage_avl_rec(abr->fd, niveau+1);
        printf("\n");
    }
    espace(niveau);
    affichage_noeud(abr);
    printf("\n");
    if(abr->fg != NULL){
        printf("\n");
        affichage_avl_rec(abr->fg, niveau+1);
    }
}


void saut_ligne(int h){
    int i = 0;
    for(i=0; i<10*h; i++){
        printf("/n");
    }
}

void espace(int h){
    int i = 0;
    for(i=0; i<3*h; i++){
        printf("|_");
    }
}


       
