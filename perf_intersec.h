#ifndef PREF_INTERSEC_H
#define PREF_INTERSEC_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "netlist.h"
#include "balayage.h"
#include "avl.h"

double temps(Netlist *n, char mode);

void initialize_tab_netlist(Netlist **n, char** list, int taille);

void free_tab_netlist(Netlist **n, int taille);

#endif