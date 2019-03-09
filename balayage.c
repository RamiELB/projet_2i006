#include "balayage.h"

Echeancier *creer_echeancier(Netlist *n){
    int taille;
    Segment **tab_seg = tab_segments_netlist(n, &taille);

    int nb_ev = compte_ev(tab_seg, taille);
    Echeancier *ec= malloc(sizeof(Echeancier));
    ec->tab_ex = malloc(nb_ev * sizeof(Extremite *));
    ec->taille_tab = nb_ev;
    int i;
    int indice = 0;
    for(i=0;i<taille;i++){
        indice = ajout_extremite(tab_seg[i], ec->tab_ex, indice, n);
    }
    return ec;
}

int compte_ev(Segment **tab_seg, int taille){
    int cpt = 0;
    int i;
    for(i=0;i<taille;i++){
        if(tab_seg[i]->HouV == 1){
            cpt ++;
        }else{
            cpt+=2;
        }
    }
    return cpt;
}

int ajout_extremite(Segment *s, Extremite **tab_ex, int indice, Netlist *n){
    Extremite *e;
    if(s->HouV == 0){
        if(n->T_Res[s->NumRes]->T_Pt[s->p1]->x < n->T_Res[s->NumRes]->T_Pt[s->p2]->x){
            e = crea_ext_h(s, n, 1, s->p1);
            tab_ex[indice] = e;
            indice++;

            e = crea_ext_h(s, n, 2, s->p2);
            tab_ex[indice] = e;
            indice++;
        }else{
            e = crea_ext_h(s, n, 2, s->p1);
            tab_ex[indice] = e;
            indice++;

            e = crea_ext_h(s, n, 1, s->p2);
            tab_ex[indice] = e;
            indice++;
        }
    }else{
        e = crea_ext_v(s, n);
        tab_ex[indice] = e;
        indice++;
    }
    return indice;
}

Extremite *crea_ext_h(Segment *s, Netlist *n, int GouD, int numpt){
    Extremite *e = malloc(sizeof(Extremite));
    e->VouGouD = GouD;
    e->PtrSeg = s;
    e->NumPt = numpt;
    e->x = n->T_Res[s->NumRes]->T_Pt[numpt]->x;
    return e;
}


Extremite *crea_ext_v(Segment *s, Netlist *n){
    Extremite *e = malloc(sizeof(Extremite));
    e->VouGouD = 0;
    e->PtrSeg = s;
    e->NumPt = -1;
    e->x = n->T_Res[s->NumRes]->T_Pt[s->p1]->x;
    return e;
}

void tri_rapide(Echeancier *e){
    tri_rapide_rec(e->tab_ex, 0, e->taille_tab - 1);
}

void tri_rapide_rec(Extremite **tab_ex, int d, int f){
    if(d<f){
        int m = partition(tab_ex, d, f);
        tri_rapide_rec(tab_ex, d, m);
        tri_rapide_rec(tab_ex, m+1, f);
    }
}

int partition(Extremite **tab_ex, int d, int f){
    int i;
    int m = d+1;
    while(tab_ex[m]->x <= tab_ex[d]->x && m<f){
        m++;
    }
    for(i=m+1;i<=f;i++){
        if(tab_ex[i]->x <= tab_ex[d]->x){
            swap(tab_ex, i, m);
            m++;
        }
    }
    if(tab_ex[d]->x > tab_ex[m]->x){
        swap(tab_ex, d, m);
    }
    return m-1;
}

void swap(Extremite **tab_ex, int i, int f){
    Extremite *tmp = tab_ex[f];
    tab_ex[f] = tab_ex[i];
    tab_ex[i] = tmp;
}