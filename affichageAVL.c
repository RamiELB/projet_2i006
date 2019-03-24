#include "affichageAVL.h"

int main(){
    Noeud* n1 = (Noeud*)malloc(sizeof(Noeud));
    Noeud* n2 = (Noeud*)malloc(sizeof(Noeud));
    Noeud* n3 = (Noeud*)malloc(sizeof(Noeud));
    Noeud* n4 = (Noeud*)malloc(sizeof(Noeud));
    Noeud* n5 = (Noeud*)malloc(sizeof(Noeud));
    
    n1->y = 3.2;
    n1->hauteur = 2;
    
    n2->y = 5.4;
    n2->hauteur = 1;
    
    n3->y = 2.4;
    n3->hauteur = 1;
    
    n4->y = 5.1;
    n4->hauteur = 0;
    
    n5->y = 6.0;
    n5->hauteur = 0;
    
    n1->fg = n2;
    n1->fd = n3;
    
    n2->fg = n4;
    n2->fd = n4;
    
    n3->fg = NULL;
    n3->fd = NULL;
    
    
    
    affichage_avl(n1); 
    
    return EXIT_SUCCESS;
}


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


       
