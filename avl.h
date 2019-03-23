#ifndef AVL_H
#define AVL_H
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"
#include "balayage.h"


typedef struct noeud {
    Segment * seg;
    double y; /* Ordonnee du segment */
    struct noeud * fg; /* Fils gauche */
    struct noeud * fd; /* Fils droit */
    int hauteur;
} Noeud;

typedef Noeud* ABR;


Noeud *Prem_Noeud_apres(ABR ab, double y);

ABR chercher_noeud(ABR ab, Segment *seg, Netlist *n);

ABR coupe_max(ABR *ab); /* Renvoie l'ABR correspondant au max de ab et le fixe à NULL dans ab */

Noeud *creerFeuille(Segment *seg, Netlist *n);

int max(int a, int b);

int hauteur(ABR ab);

void rotationDroite(ABR *ab);

void rotationGauche(ABR *ab);

void majhauteur(ABR ab);

void insererElnt_avec_eq(ABR *ab, Segment *seg, Netlist *n);

void intersec_avl(Netlist *n);

void hauteur_abr(ABR a);

#endif /* NETLIST_H */
