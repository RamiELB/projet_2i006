#include "via_cycle.h"

Cell_sommet *detecte_cycle_impair(Graphe *g, int **tab_faces, int *M, int i, int pere){
    Cell_sommet *cs = NULL;
    int id_som_succ;
    Sommet *s = g->tab_sommets[i];
    Elem_Arrete *a = s->liste_arretes;
    while(a != NULL){
        if(a->id != -1){ // si l'arrete est une intersection
            if(a->som1 == i)
                id_som_succ = a->som2;
            else
                id_som_succ == a->som1;
            
        }
    }
}

void Ajout_vias_cycle_impair(Graphe *g){
    int *tab_faces = malloc(g->nb_sommets * sizeof(int));
    int *M = malloc(g->nb_sommets * sizeof(int));
    int i;
    for(i=0;i<g->nb_sommets;i++){
        tab_faces[i] = -1;
        M[i] = -1;
    }
    
}