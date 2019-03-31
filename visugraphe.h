#ifndef VISUGRAPHE_H
#define VISUGRAPHE_H
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"
#include "SVGwriter.h"
#include "graphe.h"

void dessine_sommets_et_continuite(Netlist* n, Sommet* s, SVGwriter* svg);
void dessine_conflits(Netlist* n, Graphe* g, Arrete* a, SVGwriter* svg);
double x_milieu_segment(Netlist*, Segment* s);
double y_milieu_segment(Netlist*, Segment* s);

#endif /* VISUGRAPHE_H */
