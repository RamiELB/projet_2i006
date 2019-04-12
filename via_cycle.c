#include "via_cycle.h"

int main(){
    Netlist *n = lecture_netlist("Instance_Netlist/test.net");
    intersec_balayage(n);
    Graphe *g = creer_graphe(n, "Instance_Netlist/test.net.int");
    int *S = Ajout_vias_cycle_impair(g);
    S = bicolore(g, S);
}


Cell_sommet *detecte_cycle_impair(Graphe *g, int *S, int *M, int *tab_peres, int i, int pere, int alternance){
    if(M[i] == 0 || S[i] == 0)
        return NULL;
    
    tab_peres[i] = pere;
    if(M[i] == M[pere]){
        /* On détecte un cycle impair*/
        return creation_chaine_cycle(g, M, tab_peres, i, NULL, i);
    }
    M[i] = alternance;
    int id_som_succ;
    Sommet *s = g->tab_sommets[i];
    Elem_Arrete *ea = s->liste_arretes;
    Cell_sommet *cs;
    while(ea != NULL){
        id_som_succ = autre_sommet(ea, i);
        if(id_som_succ != pere){
            cs = detecte_cycle_impair(g, S, M, tab_peres, id_som_succ, i, alterne(alternance));
            if(cs != NULL){
                /* Si on a trouvé un cycle impair, on stop */
                return cs;
            }
        }
        ea = ea->suiv;
    }
    return NULL;
}

int autre_sommet(Elem_Arrete *ea, int sommet){
    if(ea->a->som1 == sommet)
        return ea->a->som2;
    return ea->a->som1;
}

int alterne(int a){
    if(a == 1)
        return 2;
    return 1;
}

Cell_sommet *creation_chaine_cycle(Graphe *g, int *M, int *tab_peres, int i, Cell_sommet *chaine_sommets, int premier_appel){
    Cell_sommet *cs = nouveau_cs(g->tab_sommets[i]);
    cs->suiv = chaine_sommets;
    if(tab_peres[i] == -1){
        fprintf(stderr, "Erreur : un pere n'est pas indiqué dans le tableau\n");
        return NULL;
    }
    if(tab_peres[i] != premier_appel){
        return creation_chaine_cycle(g, M, tab_peres, i, cs, premier_appel);
    }
    return cs;
}

Cell_sommet *nouveau_cs(Sommet *s){
    Cell_sommet *cs = malloc(sizeof(Cell_sommet));
    cs->som = s;
    cs->suiv = NULL;
    return cs;
}


int *Ajout_vias_cycle_impair(Graphe *g){
    int *S = malloc(g->nb_sommets * sizeof(int));
    int *M = malloc(g->nb_sommets * sizeof(int));
    int *tab_peres = malloc(g->nb_sommets * sizeof(int));
    int i, j;
    for(i=0;i<g->nb_sommets;i++){
        S[i] = -1;
        M[i] = -1;
        tab_peres[i] = -1;
    }
    Cell_sommet *cycle_impair = NULL;
    for(i=0;i<g->nb_sommets;i++){
        if(M[i] == -1){
            do{
                cycle_impair = detecte_cycle_impair(g, S, M, tab_peres, i, 0, 1);
                ajout_via_cycle(cycle_impair, S, M);
                for(j=0;j<g->nb_sommets;j++){
                    M[j] = -1;
                    tab_peres[j] = -1;
                }
            } while(cycle_impair != NULL) ;
        }
    }
    return S;
}

void ajout_via_cycle(Cell_sommet *cycle_impair, int *S, int *M){
    Cell_sommet *cs = cycle_impair;
    Cell_sommet *prec = cs;
    while(cs != NULL){
        if(cs->som->pt != NULL){
            S[cs->som->id] = 0;
            M[cs->som->id] = 0;
        }else{
            S[cs->som->id] = M[cs->som->id];
        }
        free(cs);
        cs = prec->suiv;
        prec = cs;
    }
}

int *bicolore(Graphe *g, int *S){
    int i;
    for(i=0;i<g->nb_sommets;i++){
        if(S[i] == -1){
            ajout_faces_rec(g, S, g->tab_sommets[i], 1);
        }
    }
    return S;
}

void ajout_faces_rec(Graphe *g, int *S, Sommet *som, int face){
    Elem_Arrete *ea;
    int id_som_succ;
    if (S[som->id] == -1){
        S[som->id] = face;
        for(ea = som->liste_arretes; ea != NULL ; ea=ea->suiv){
            id_som_succ = autre_sommet(ea, som->id);
            ajout_faces_rec(g, S, g->tab_sommets[id_som_succ], alterne(face));
        }
    }
}