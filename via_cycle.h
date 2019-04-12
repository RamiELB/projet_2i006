#ifndef VIA_CYCLE_H
#define VIA_CYCLE_H
#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

typedef struct cell_sommet{
    Sommet *som; 
    struct cell_sommet *suiv;
} Cell_sommet;

int *Ajout_vias_cycle_impair(Graphe *g);
int *bicolore(Graphe *g, int *S);


int alterne(int a);
int autre_sommet(Elem_Arrete *ea, int sommet);
Cell_sommet *detecte_cycle_impair(Graphe *g, int *S, int *M, int *tab_peres, int i, int pere, int alternance);
Cell_sommet *creation_chaine_cycle(Graphe *g, int *M, int *tab_peres, int i, Cell_sommet *chaine_sommets, int premier_appel);
Cell_sommet *nouveau_cs(Sommet *s);
void ajout_via_cycle(Cell_sommet *cycle_impair, int *S, int *M);
void ajout_faces_rec(Graphe *g, int *S, Sommet *som, int face);

#endif