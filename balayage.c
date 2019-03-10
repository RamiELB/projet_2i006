#include "balayage.h"

int main(){
    Netlist *n = lecture_netlist("Instance_Netlist/test.net");
    intersec_balayage(n);
    sauvegarde_intersection(n, "Instance_Netlist/test.net");
}


        /* ECHEANCIER */
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
    tri_rapide(ec);
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
    /* TRI DE L'ECHEANCIER */
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



    

    /* SECONDE STRUCTURE */
void Inserer(Segment *s, Cell_t **T, Netlist *n){
    Cell_t *nv_c = malloc(sizeof(Cell_t));
    nv_c->y = n->T_Res[s->NumRes]->T_Pt[s->p1]->y;
    nv_c->seg = s;
    if(*T == NULL){
        nv_c->prec = NULL;
        nv_c->suiv = NULL;
        *T = nv_c;
    }else{
        Cell_t *ct = *T;
        Cell_t *c_prec;
        while(ct != NULL && ct->y < nv_c->y){
            c_prec = ct;
            ct = ct->suiv;
        }
        if(ct == *T){
            nv_c->suiv = *T;
            nv_c->prec = NULL;
            (*T)->prec = nv_c;
            *T = nv_c;
        }else if(ct == NULL){
            c_prec->suiv = nv_c;
            nv_c->prec = c_prec;
            nv_c->suiv = NULL;
        }else{
            nv_c->suiv = ct;
            ct->prec = nv_c;
            c_prec->suiv = nv_c;
        }
    }
}

void Supprimer(Segment *s, Cell_t **T){
    Cell_t *ct = *T;
    while(ct->seg != s && ct != NULL){
        ct = ct->suiv;
    }
    if(ct == NULL){
        printf("Erreur : le segment à supprimer n'est pas dans la liste\n");
    }else{
        if(ct == *T){
            *T = ct->suiv;
            if(*T != NULL){
                (*T)->prec = NULL;
            }
        }else{
            ct->prec->suiv = ct->suiv;
            if(ct->suiv != NULL){
                ct->suiv->prec = ct->prec;
            }
        }
        free(ct);
    }
}

Cell_t *Prem_segment_apres(double y, Cell_t *T){
    Cell_t *ct = T;
    while(ct != NULL){
        if(ct->y > y){
            return ct;
        }
        ct = ct->suiv;
    }
    return NULL;
}

Cell_t *AuDessus(Cell_t *h){
    return h->suiv;
}

void ajout_intersection(Segment *s1, Segment *s2){
    Cell_segment *ct;
    ct = nouveau_cellsegment(s2);
    ct->suiv = s1->Lintersec;
    s1->Lintersec = ct;

    ct = nouveau_cellsegment(s1);
    ct->suiv = s2->Lintersec;
    s2->Lintersec = ct;
}

void intersec_balayage(Netlist *n){
    Echeancier *e = creer_echeancier(n);
    int i;
    Cell_t *T;
    double y1, y2;
    Segment *seg;
    Cell_t *h;
    for(i=0;i<e->taille_tab;i++){
        seg = e->tab_ex[i]->PtrSeg;
        if(e->tab_ex[i]->VouGouD == 1){
            Inserer(seg, &T, n);
        }else if(e->tab_ex[i]->VouGouD == 2){
            Supprimer(seg, &T);
        }else{
            if(n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y < n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y){
                y1 = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y; 
                y2 = n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;
            }else{
                y2 = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y; 
                y1 = n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;
            }
            h = Prem_segment_apres(y1, T);
            while(h != NULL && h->y < y2){
                ajout_intersection(h->seg, seg);
                h = AuDessus(h);
            }
        }
    }
}