#include "balayage.h"

Extreminte **creer_echeancier(Netlist *n){
    int taille, i;
    Segment **tab_seg = tab_segments_netlist(Netlist *n, int *taille);
    Echeancier *prems = NULL;
    Echeancier *dernier;
    Echeancier *e;
    int nb_ec = 0;
    for(i=0;i<taille;i++){
        if(tab_seg[i]->HouV == 1){
            nb_ec++:
            e = creer_echeancier_v(n, tab_seg[i]);
            if(prems == NULL){
                prems = e;
                dernier = e;
            }else{
                dernier->suiv = e;
                dernier = e;
            }
        }else{
            nb_ec +=2;
            e = creer_echeancier_h(tab_seg[i]);
            if(prems == NULL){
                prems = e;
                dernier = e->suiv;
            }else{
                dernier->suiv = e;
                dernier = e->suiv;
            }
        }
        
    }
    return prems;
}

Echeancier *creer_echeancier_v(Netlist *n, Segment *s){
    Extremite *e = malloc(sizeof(Extremite));
    e->x = n[s->NumRes]->T_Pt[s->p1];
    e->VouGouD = 0;
    Echeancier *ec = malloc(sizeof(Echeancier));
    ec->e = e;
    ec->suiv = NULL;
    return e;
}

Echeancier *creer_echeancier_h(Netlist *n, Segment *s){
    Extremite *e1 = malloc(sizeof(Extremite));
    Extremite *e2 = malloc(sizeof(Extremite));
    e1->x = n[s->NumRes]->T_Pt[s->p1];
    e2->x = n[s->NumRes]->T_Pt[s->p2];
    e1->NumpPt = s->p1;
    e2->NumpPt = s->p2;
    if(e1->x < e2->x){
        e1->VouGouD = 1;
        e2->VouGouD = 2;
    }else{
        e1->VouGouD = 2;
        e2->VouGouD = 1;
    }
    Echeancier *ec1 = malloc(sizeof(Echeancier));
    Echeancier *ec2 = malloc(sizeof(Echeancier));
    ec1->e = e1;
    ec1->suiv = ec2;
    ec2->e = e2;
    ec2->suiv = NULL;
    return ec1;
}

void trirapide(Echeancier *e, int nb_ec){
    trirapide_rec(e, e, nb_ec-1);
}

void trirapide_rec(Echeancier *e, Echeancier *d, int f){
    if(d<fin){
        Echeancier *m = partition(e, d, f);
        trirapide_rec(t,d,m);
        trirapide_rec(t,d,m)
    }
}

Echeancier *partition(Echeancier *e, Echeancier *d, int f){
    Echeancier *separateur = d->suiv;
    Echeancier *actuel = separateur->suiv;
    Echeancier *prec_sep = d;
    Echeancier *prec_act = separateur;
    Echeancier *temp;
    int i;
    for(i=0;i<f;i++){
        if (actuel->e->x < d->e->x){
            prec_sep->suiv = actuel->e;
            temp=actuel->
        }
    }
}