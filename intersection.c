#include "intersection.h"

int intersection(Netlist *n, Segment *seg1, Segment *seg2){
    /* 0 : Les segments ne se coupent pas.
       1 : Les segments sont en intersection. */
    if(seg1->HouV == seg2->HouV){
        return 0;
    }
    Segment *s1;
    Segment *s2;
    if(seg2->HouV == 1){
        s1 = seg2;
        s2 = seg1;
    }else{
        s1 = seg1;
        s2 = seg2;
    }
    int xs1 = n->T_Res[s1->NumRes]->T_Pt[s1->p1]->x;
    int x1s2 = n->T_Res[s2->NumRes]->T_Pt[s2->p1]->x;
    int x2s2 = n->T_Res[s2->NumRes]->T_Pt[s2->p2]->x;
    if((xs1 < x1s2 && xs1 > x2s2) || (xs1 > x1s2 && xs1 < x2s2)){
        int ys2 = n->T_Res[s2->NumRes]->T_Pt[s2->p1]->y;
        int y1s1 = n->T_Res[s1->NumRes]->T_Pt[s1->p1]->y;
        int y2s1 = n->T_Res[s1->NumRes]->T_Pt[s1->p2]->y;
        if((ys2 < y1s1 && ys2 > y2s1) || (ys2 > y1s1 && ys2 < y2s1)){
            return 1;
        }
        return 0;
    }
    return 0;
}

int nb_segment(Netlist *n){
    Cell_segment *cs;
    int cpt = 0;
    int i;
    for(i=0;i<n->NbRes;i++){
        cpt += compte_seg_reseau(n->T_Res[i], &cs);
        free_chaine_cs(&cs);
    }
    return cpt;
}

int cpt_segments_netlist(Netlist *n){
    /* Fonction servant uniquement à compter les segments d'une netlist */
    int i, j;
    int cpt = 0;
    Cell_segment *cs;
    for(i=0;i<n->NbRes;i++){
        for(j=0;j<n->T_Res[i]->NbPt;j++){
            cs = n->T_Res[i]->T_Pt[j]->Lincid;
            while(cs != NULL){
                cpt++;
                cs=cs->suiv;
            }
        }
    }
    cpt = cpt / 2; /* On a compté chaque segment 2 fois */
    return cpt;
}

Cell_segment **cs tab_segments_netlist(Netlist *n){
    int taille = nb_segment(n);
    Cell_segment *cs_res;
    Cell_segment **cs_netlist=malloc(taille * sizeof(Cell_segment *));
    int indice = 0;
    int i;
    for(i=0;i<n->NbRes;i++){
        nb_seg_res = compte_seg_reseau(n->T_Res[i], &cs_res);
        indice = ajout_liste_tab(cs_res, cs_netlist, indice);
    }
}

int ajout_liste_tab(Cell_segment *cs_res, Cell_segment **cs_netlist, int indice){
    Cell_segment *cs = cs_res;
    while( cs != NULL){
        cs_netlist[indice] = cs;
        cs=cs->suiv;
        indice++;
    }
    return indice;
}
