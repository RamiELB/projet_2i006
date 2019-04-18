#ifndef VISUVIACYCLE_H
#define VISUVIACYCLE_H
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"
#include "intersection.h"
#include "SVGwriter.h"
#include "graphe.h"
#include "via_cycle.h"

void affiche_solution_cycle(char* fic, Netlist* n, Graphe* g, int x, int y, int* S);


#endif /* VISUVIACYCLE_H */
