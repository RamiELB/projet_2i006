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

typdef struct echeancier {
    Extremite *e;
    struct echeancier *suiv;
} Echeancier;

#endif /* BALAYAGE_H */
