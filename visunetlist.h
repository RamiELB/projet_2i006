#ifndef VISUNETLIST_H
#define VISUNETLIST_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "SVGwriter.h"

void dessine_reseau(Reseau *r, SVGwriter *svg);
void dessine_segments(Reseau *r, SVGwriter *svg);
void dessine_points(Reseau* r, SVGwriter* svg);


#endif /* VISUNETLIST_H */
