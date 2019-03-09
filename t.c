#include "netlist.h"

typedef struct cell_t{
    double y; 
    Segment *seg;
    struct cell_t *suiv;
} Cell_t;

void Inserer(Segment *s, Cell_t **T){
    Cell_t *nv_c = malloc(sizeof(Cell_t *));
    nv_c->seg = s;
    nv_c->suiv = *T;
    *T = nv_c;
}

void Supprimer(Segment *s, Cell_t **T){
    Cell_t* ct = *T;
    Cell_t* ct_precedent;
    
    while(ct->seg != s && ct->suiv != NULL){
        ct_precedent = ct;
        ct = ct->suiv;
    }
    if(ct == NULL){
        printf("Erreur, le segment à supprimer n'est pas dans la liste\n");
    }else{
        if(ct == *T){
            *T = ct->suiv;
        }else{
            ct_precedent->suiv = ct->suiv;
        }
        free(ct);
    }
}

Segment *Prem_segment_apres(double y, Cell_t *T){

}