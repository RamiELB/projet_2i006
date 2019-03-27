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


Noeud *Prem_Noeud_apres(ABR ab, double y); /* Renvoie le premier noeud d'ordonnée > à y */

ABR *chercher_noeud(ABR *ab, Segment *seg, Netlist *n); /* Renvoie le noeud correspondant au segment seg */

ABR coupe_max(ABR *ab); /* Renvoie l'ABR correspondant au max de ab et le fixe à NULL dans ab */

Noeud *creerFeuille(Segment *seg, Netlist *n); /* Alloue et crée un noeud */

int max(int a, int b);

int hauteur(ABR ab); /* Renvoie la hauteur de ab, 0 si NULL */

void majhauteur(ABR ab); /* Mets à jour le noeud ABR en fonction de ses fils */

void hauteur_abr(ABR a); /* Mets à jour toutes les hauteurs d'un ABR */

void rotationDroite(ABR *ab);

void rotationGauche(ABR *ab);

void rotations(ABR *ab); /* Fais les tests et effectue les rotations nécéssaires */

void supprimer_avc_eq(ABR *ab, Segment *seg, Netlist *n);

void insererElnt_avec_eq(ABR *ab, Segment *seg, Netlist *n);

void intersec_avl(Netlist *n);


#endif /* NETLIST_H */
