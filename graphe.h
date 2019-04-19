#ifndef GRAPHE_H
#define GRAPHE_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "intersection.h"
#include "balayage.h"
#include "SVGwriter.h"


typedef struct arrete{
    int id; /* correspond à l'indice de l'arrete dans le graphe, -1 si c'est une arrete de continuite */
    int som1; /* id du sommet dans le graphe */
    int som2;
} Arrete;

typedef struct elem_arrete{
    Arrete *a;
    struct elem_arrete *suiv;
} Elem_Arrete;

typedef struct sommet{
    Segment *seg; /* NULL si le sommet correspond à un point */
    Point *pt; /* NULL si le sommet correspond à un segment */
    int id; /* correspond à l'indice du sommet dans le graphe */
    Elem_Arrete *liste_arretes; /* Liste des arretes du sommet */
} Sommet;

typedef struct graphe{
    int nb_sommets;
    //int nb_conflits;
    Sommet **tab_sommets;
    //Arrete **tab_conflits;
} Graphe;




Graphe *creer_graphe(Netlist *n, char *fic_int); 




void arretes_continu(Graphe *g, Netlist *n);

void arretes_conflits(Graphe *g, char* fic_int, Netlist *n); /* Rempli et alloue tab_conflits et nb_conflits */

Arrete *creer_arrete(int id, int som1, int som2);

void ajout_arrete(Sommet **tab_sommets, Arrete *a); /* Ajout l'arrete conflit dans les sommets correspondants */

Elem_Arrete *creer_elem_arrete(Arrete *a); 


Segment *chercher_segment(Netlist *n, int numres, int pt1, int pt2);


int chercher_sommet_seg(Segment *seg, Graphe *g); /* Renvoie l'indice du somment contenant le segment seg dans le tableau de sommets du graphe */

int chercher_sommet_pt(Netlist *n, Graphe *g, int numres, int p1ou2); /* Renvoie l'indice du somment contenant le point dans le tableau de sommets du graphe */

void sommets_graphe(Graphe *g, Netlist *n); /* Rempli et alloue tab_sommets et nb_sommets */

Sommet *creer_sommet_seg(Segment *seg, int id);

Sommet *creer_sommet_pt(Point *p, int id);

int compte_intersec(char *fic_int);

#endif
