#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "string.h"

int intersection(Netlist *n, Segment *seg1, Segment *seg2);

int nb_segment(Netlist *n);

Segment **tab_segments_netlist(Netlist *n, int *taille);

int ajout_liste_tab(Cell_segment *cs_res, Segment **seg_netlist, int indice);

Segment **intersect_naif(Netlist *n, int *taille_tab);

void sauvegarde_intersection(Netlist *n, char *nom_fic);

void ecrire_intersec(FILE *f, Segment *s);

#endif