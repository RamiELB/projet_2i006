#ifndef BALAYAGE_H
#define BALAYAGE_H
#include "netlist.h"
#include "intersection.h"

typedef struct extremite {
    double x; /* Ordonnee du point */
    int VouGouD; /* 0 si segment V / 1 si pt gauche d’un segment H / 2 si pt droit d’un segment H */
    Segment *PtrSeg; /* Pointeur sur le segment correspondant a l’extremite */
    int NumPt; /* si segment H: numero du point correspondant */
} Extremite;

typedef struct echeancier {
    Extremite **tab_ex; 
    int taille_tab;
} Echeancier;

typedef struct cell_t{
    double y; 
    Segment *seg;
    struct cell_t *suiv;
    struct cell_t *prec;
} Cell_t;

Echeancier *creer_echeancier(Netlist *n);

int compte_ev(Segment **tab_seg, int taille);

int ajout_extremite(Segment *s, Extremite **tab_ex, int indice, Netlist *n);

Extremite *crea_ext_h(Segment *s, Netlist *n, int GouD, int numpt);

Extremite *crea_ext_v(Segment *s, Netlist *n);



    /* FONCTIONS SERVANT AU TRI DE LECHEANCIER */
void tri_rapide(Echeancier *e);

void tri_rapide_rec(Extremite **tab_ex, int d, int f);

int partition(Extremite **tab_ex, int d, int f);

void swap(Extremite **tab_ex, int i, int f);


    /* MANIPULATION DE LA SECONDE STRUCTURE */
void Inserer(Segment *s, Cell_t **T, Netlist *n);

void Supprimer(Segment *s, Cell_t **T);

Cell_t *Prem_segment_apres(double y, Cell_t *T);

Cell_t *AuDessus(Cell_t *h);

void ajout_intersection(Segment *s1, Segment *s2);

void intersec_balayage(Netlist *n);



#endif /* BALAYAGE_H */
