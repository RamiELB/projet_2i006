#ifndef AFFICHAGEAVL_H
#define AFFICHAGEAVL_H
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"
#include "avl.h"

void affichage_avl(ABR abr);
void affichage_noeud(Noeud* n);
void affichage_avl_rec(ABR abr, int niveau);
void espace(int h);


#endif /* AFFICHAGEAVL_H */
