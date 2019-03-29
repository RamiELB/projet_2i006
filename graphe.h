#ifndef GRAPHE_H
#define GRAPHE_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "intersection.h"

typedef struct graphe{
    int nb_sommets;
    int nb_arretes;
    Sommet **tab_sommets;
    Arrete **tab_arretes;
} Graphe;

typedef struct sommet{
    Segment *s; /* NULL si le sommet correspond à un point */
    Point *p; /* NULL si le sommet correspond à un segment */
    int id; /* correspond à l'indice du sommet dans le graphe */
    int nb_arretes;
    Elem_Arrete *liste_arretes; /* Liste des arretes du sommet */
} Sommet;

typedef struct arrete{
    int id; /* correspond à l'indice de l'arrete dans le graphe */
    int som1; /* id du sommet dans le graphe */
    int som2;
} Arrete;

typedef struct elem_arrete{
    Arrete *a;
    elem_arrete *suiv;
} Elem_Arrete;

#endif