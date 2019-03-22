#ifndef AVL_H
#define AVL_H
#include <stdlib.h>
#include <stdio.h>
#include <netlist.h>


typedef struct noeud {
    Segment * seg;
    double y; /* Ordonnee du segment */
    struct noeud * fg; /* Fils gauche */
    struct noeud * fd; /* Fils droit */
    int hauteur;
} Noeud;

typedef Noeud* ABR;


#endif /* NETLIST_H */
