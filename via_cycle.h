#ifndef VIA_CYCLE_H
#define VIA_CYCLE_H
#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

typedef struct cell_sommet{
    Sommet *som; 
    struct cell_sommet *suiv;
} Cell_sommet;


#endif