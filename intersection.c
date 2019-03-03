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

Segment **tab_segments_netlist(Netlist *n, int *taille){
    *taille = nb_segment(n);
    Cell_segment *cs_res;
    Segment **seg_netlist=malloc((*taille) * sizeof(Cell_segment *));
    int indice = 0;
    int i;
    for(i=0;i<n->NbRes;i++){
        compte_seg_reseau(n->T_Res[i], &cs_res);
        indice = ajout_liste_tab(cs_res, seg_netlist, indice);
    }
    return seg_netlist;
}

int ajout_liste_tab(Cell_segment *cs_res, Segment **seg_netlist, int indice){
    Cell_segment *cs = cs_res;
    while( cs != NULL){
        seg_netlist[indice] = cs->seg;
        cs=cs->suiv;
        indice++;
    }
    return indice;
}

Segment **intersect_naif(Netlist *n, int *taille_tab){
    Segment **tab_seg = tab_segments_netlist(n, taille_tab);
    int i;
    int j;
    Cell_segment *new_cell;
    for(i=0; i<(*taille_tab); i++){
        for(j=i; j<(*taille_tab); j++){
            if(intersection(n, tab_seg[i], tab_seg[j])){
                
                new_cell = nouveau_cellsegment(tab_seg[j]);
                if(tab_seg[i]->Lintersec == NULL){
                    tab_seg[i]->Lintersec = new_cell;
                }else{
                    Cell_segment* tete = tab_seg[i]->Lintersec;
                    new_cell->suiv = tete;
                    tab_seg[i]->Lintersec = new_cell; 
                }

                /* Il faut aussi l'ajouter dans la liste du 2nd segment */
                new_cell = nouveau_cellsegment(tab_seg[i]);
                if(tab_seg[j]->Lintersec == NULL){
                    tab_seg[j]->Lintersec = new_cell;
                }else{
                    Cell_segment* tete = tab_seg[j]->Lintersec;
                    new_cell->suiv = tete;
                    tab_seg[j]->Lintersec = new_cell; 
                }
            }
        }  
    }
    return tab_seg;
}

void  sauvegarde_intersection(Netlist *n, char *nom_fic){
    int taille_tab, i;
    Segment **tab_seg = intersect_naif(n, &taille_tab);
    char *nom = malloc(100 * sizeof(char));
    nom = strcpy(nom, nom_fic);
    strcat(nom, ".int");
    FILE *f = fopen(nom, "w");
    for(i=0;i<taille_tab;i++){
        ecrire_intersec(f, tab_seg[i]);
    }
    fclose(f);
}

void ecrire_intersec(FILE *f, Segment *s){
    Cell_segment *cs = s->Lintersec;
    while(cs != NULL){
        fprintf(f, "%d %d %d %d %d %d\n", s->NumRes, s->p1, s->p2, cs->seg->NumRes, cs->seg->p1, cs->seg->p2);
        cs = cs->suiv;
    }
}