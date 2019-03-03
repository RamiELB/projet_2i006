#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"

int intersection(Netlist *n, Segment *seg1, Segment *seg2);

int nb_segment(Netlist *n);

int cpt_segments_netlist(Netlist *n);

Cell_segment **tab_segments_netlist(Netlist *n);

int ajout_liste_tab(Cell_segment *cs_res, Cell_segment **cs_netlist, int indice);

void intersect_naif(Netlist *n, Segment **tab_seg);

#endif