#include "via_cycle.h"

Cell_sommet *detecte_cycle_impair(Graphe *g, int *S, int *M, int *tab_peres, int i, int pere){
    if(M[i] == 0 || S[i] == 0)
        return NULL;
    
    tab_peres[i] = pere;
    if(M[i] == 1){
        /* On détecte un cycle */
        return creation_chaine_cycle(g, M, tab_peres, i, NULL, i);
    }
    M[i] = 1;
    int id_som_succ;
    Sommet *s = g->tab_sommets[i];
    Elem_Arrete *ea = s->liste_arretes;
    Cell_sommet *cs;
    while(ea != NULL){
        if(ea->a->som1 == i)
            id_som_succ = ea->a->som2;
        else
            id_som_succ == ea->a->som1;
        if(id_som_succ != pere){
            cs = detecte_cycle_impair(g, S, M, tab_peres, id_som_succ, i);
            if(cs != NULL){
                /* Si on a trouvé un cycle impair, on stop */
                return cs;
            }
        }
        ea = ea->suiv;
    }
    return NULL;
}

Cell_sommet *creation_chaine_cycle(Graphe *g, int *M, int *tab_peres, int i, Cell_sommet *chaine_sommets, int premier_appel){
    Cell_sommet *cs = nouveau_cs(g->tab_sommets[i]);
    cs->suiv = chaine_sommets;
    if(tab_peres[i] == -1){
        fprintf(stderr, "Erreur : un pere n'est pas indiqué dans le tableau\n");
        return NULL;
    }
    if(tab_peres[i] != premier_appel){
        return creation_chaine_cycle(g, M, tab_peres, i, cs, premier_appel);
    }
    return cs;
}

Cell_sommet *nouveau_cs(Sommet *s){
    Cell_sommet *cs = malloc(sizeof(Cell_sommet));
    cs->som = s;
    cs->suiv = NULL;
    return cs;
}


void Ajout_vias_cycle_impair(Graphe *g){
    int *S = malloc(g->nb_sommets * sizeof(int));
    int *M = malloc(g->nb_sommets * sizeof(int));
    int *tab_peres = malloc(g->nb_sommets * sizeof(int));
    int i;
    for(i=0;i<g->nb_sommets;i++){
        S[i] = -1;
        M[i] = -1;
        tab_peres[i] = -1;
    }
    
}