#include "via_cycle.h"

int main(){
    Netlist *n = lecture_netlist("Instance_Netlist/c4.net");
    intersec_balayage(n);
    Graphe *g = creer_graphe(n, "Instance_Netlist/c4.net.int");
    int *S = Ajout_vias_cycle_impair(g);
    S = bicolore(g, S);
}


int detecte_cycle_impair(Graphe *g, int *S, int *M, int *tab_peres, int i, int pere, int alternance){
    //printf("Appel sur S[%d] = %d, M = %d, pere : M[%d] = %d, alternance = %d\n", i, S[i], M[i],  pere, M[pere], alternance);
    if(M[i] == 0 || S[i] == 0)
        return -1;
    //printf("%d appel %d\n", pere, i);
    if(i == pere){
        tab_peres[i] = i;
    }else if(M[i] == M[pere] && pere != tab_peres[pere] /* Pour le premier appel on a i qui est son propre père*/){
        /* On détecte un cycle impair*/
        tab_peres[i] = pere;
        printf("Cycle impair trouvé en %d\n", i, pere);
        return i;
    }
    
    if(M[i] == -1){    
        M[i] = alternance;
        int id_som_succ;
        Sommet *s = g->tab_sommets[i];
        Elem_Arrete *ea = s->liste_arretes;
        int indice_cycle;
        while(ea != NULL){
            id_som_succ = autre_sommet(ea, i);
            if(pere != id_som_succ){
                indice_cycle = detecte_cycle_impair(g, S, M, tab_peres, id_som_succ, i, alterne(alternance));
                if(indice_cycle != -1){
                    /* Si on a trouvé un cycle impair, on stop */

                    if(i != indice_cycle /* Pour ne pas écraser le cycle */){
                        tab_peres[i] = pere;
                    }
                    return indice_cycle;
                }
            }
            ea = ea->suiv;
        }
    }
    return -1;
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

    if(i == tab_peres[i]){
        fprintf(stderr, "Erreur lors de la remontée dans le tab_peres, echec de l'ajout du via (%d)\n", i);
        return NULL;
    }
    if(i == -1)
        return NULL;


        /* Chainage du sommet */
    Cell_sommet *cs = nouveau_cs(g->tab_sommets[i]);
    cs->suiv = chaine_sommets;



    /* Il y a certains cas où le cycle impair est trouvé en un sommet qui ne fait aucun appel récursif, mais qui se fait lui
        même appelé par 2 sommets différents. Dans ce cas là il est impossible de le retrouver à partir de tab_peres, il faut
        dont faire une recherche dans les voisins direct de chaque sommet */
    Elem_Arrete *ea = g->tab_sommets[i]->liste_arretes;
    int id_som_succ;
    while(ea != NULL){
        id_som_succ = autre_sommet(ea, i);
        if (id_som_succ == premier_appel && tab_peres[i] != id_som_succ)
            return cs;
        ea = ea->suiv;
    }

    //printf("i = %d, premier appel = %d, pere : %d\n", i, premier_appel, tab_peres[i]);
    if(tab_peres[i] == -1){
        fprintf(stderr, "Erreur : un pere n'est pas indiqué dans le tableau\n");
        return NULL;
    }
    if(tab_peres[i] != premier_appel){
        return creation_chaine_cycle(g, M, tab_peres, tab_peres[i], cs, premier_appel);
    }else{
        return cs;
    }
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
    int res = 0;
    Cell_sommet *cycle_impair = NULL;
    for(i=0;i<g->nb_sommets;i++){
        if(M[i] == -1){
            do{
                res = detecte_cycle_impair(g, S, M, tab_peres, i, i, 1);
                cycle_impair = creation_chaine_cycle(g, M, tab_peres, res, NULL, res);
                ajout_via_cycle(cycle_impair, S, M, 0);
                for(j=0;j<g->nb_sommets;j++){
                    //if(M[j] != 0)
                    //    M[j] = -1;
                    tab_peres[j] = -1;
                }
            } while(res != -1) ;
        }
    }
    return S;
}

void ajout_via_cycle(Cell_sommet *cycle_impair, int *S, int *M, int via){
    Cell_sommet *cs = cycle_impair;
    Cell_sommet *prec = cs;
    while(cs != NULL){
        if(cs->som->pt != NULL && via == 0){
            via = 1;
            S[cs->som->id] = 0;
            M[cs->som->id] = 0;
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
    }else if(S[som->id] == 0){
        S[som->id] = alterne(face);
        for(ea = som->liste_arretes; ea != NULL ; ea=ea->suiv){
            id_som_succ = autre_sommet(ea, som->id);
            ajout_faces_rec(g, S, g->tab_sommets[id_som_succ], face);
        }
    }
}
