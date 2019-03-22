#ifndef AVL_H
#define AVL_H
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"


typedef struct noeud {
    Segment * seg;
    double y; /* Ordonnee du segment */
    struct noeud * fg; /* Fils gauche */
    struct noeud * fd; /* Fils droit */
    int hauteur;
} Noeud;

typedef Noeud* ABR;




Noeud *rechercherValeur(ABR ab, Segment *seg, Netlist *n);

Noeud *creerFeuille(Segment *seg, Netlist *n);

int max(int a, int b);

int hauteur(ABR ab);

void rotationDroite(ABR *ab);

void rotationGauche(ABR *ab);

void majhauteur(ABR ab);

void insererElnt_avec_eq(ABR *ab, Segment *seg, Netlist *n);

#endif /* NETLIST_H */
