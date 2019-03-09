#include "netlist.h"

typedef struct cell_t{
    double y; 
    Segment *seg;
    struct cell_t *suiv;
    struct cell_t *prec;
} Cell_t;


void Inserer(Segment *s, Cell_t **T, Netlist *n){
    Cell_t *nv_c = malloc(sizeof(Cell_t *));
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

Segment *Prem_segment_apres(double y, Cell_t *T){
    Cell_t *prem_seg_apres = NULL;
    Cell_t *ct = T;
    while(ct != NULL){
        if(ct->y > y){
            if(prem_seg_apres == NULL){
                prem_seg_apres = ct;
            }else{
                if(ct->y < prem_seg_apres->y){
                    prem_seg_apres = ct;
                }
            }
        }
        ct = ct->suiv;
    }
    if(prem_seg_apres == NULL){
        return NULL;
    }
    return prem_seg_apres->seg;
}

Segment *AuDessus(Cell_t *h, Cell_t **T){
    return Prem_segment_apres(h->y, T);
}