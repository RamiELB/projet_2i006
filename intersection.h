#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "string.h"

    /* Renvoie 1 si les segments se croisent, 0 sinon */
int intersection(Netlist *n, Segment *seg1, Segment *seg2);

    /* Renvoie un tableau de tous les segments d'une netlist */
Segment **tab_segments_netlist(Netlist *n, int *taille);

    /* Renvoie 1 si le segment S n'est pas dans le tableau tab_seg de la première case à la case indice */
int seg_pas_dans_tab(Segment **tab_seg, Segment *s, int indice);



    
int ajout_seg_tab(Segment **seg_netlist, Segment *s, int indice);

    /* Remplis Lintersec des segments d'une netlist et renvoie le nombre d'intersections */
int intersect_naif(Netlist *n);

    /* Ecris les intersections d'une netlist dans un fichier .int */
void sauvegarde_intersection(Netlist *n, char *nom_fic);

    /* Ecris toutes les intersections d'un segment dans le fichier f */
void ecrire_intersec(FILE *f, Segment *s);

#endif