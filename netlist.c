#include "netlist.h"

Netlist *lecture_netlist(char* nom_fichier){
    FILE *f = fopen(nom_fichier);
    Netlist *n = malloc(sizeof(Netlist));
    n->NbRes = GetEntier(f); //le nombre de réseau est sur la toute première ligne du fichier
    n->T_res = malloc(n->NbRes * sizeof(Reseau)); //allocation du tableau de réseaux

    /* Variables utiles à la création d'un réseau */
    int num_reseau, nb_pts, nb_seg;
    Reseau *r;
    Point *p;
    int num_point;
    double x,y;
    Segment *s;
    int seg_pt1, seg_pt2;
    Cell_segment *cs;
    

    char ligne[20];
    
    while(fgets(ligne,20,f)){
        sscanf(ligne, "%d %d %d", num_reseau, nb_pts, nb_seg); //lecture d'un nouveau réseau
        r = nouveau_reseau(num_reseau, nb_seg);
        while(fscanf(f,"%d %f %f", num_point,x,y) == 3){ //lecture des points
            p = nouveau_point(num_reseau,x,y);
            r->T_Pt[num_point] = p;
        }
        /* TEST A FAIRE : QUE RENVOIE fscanf */
        while(fscanf(f,"%d %d", seg_pt1,seg_pt2) == 2){
            s = nouveau_segment(num_reseau, seg_pt1, seg_pt2, r);
        }
        n->T_res[num_reseau] = r; //ajout du reseau à la netlist
    }
}

Reseau *nouveau_reseau(num_reseau, nb_pts){
    Reseau *r = (Reseau *) malloc(sizeof(Reseau));
    r->NumRes = num_reseau;
    r->NbPt = nb_pts;
    r->T_Pt = (Point *) malloc(nb_pts * sizeof(Point));
    return r;
}

Cell_segment *nouveau_cellsegment(){
    Cell_segment *cs = malloc(sizeof(Cell_segment));
    cs->suiv = NULL;
    return cs;
}

Point *nouveau_point(num_reseau,x,y){
    Point *p = (Point *) malloc(sizeof(Point));
    p->num_res = num_reseau;
    p->x = x;
    p->y = y;
    return p;
}

Segment *nouveau_segment(num_reseau, seg_pt1, seg_pt2, Reseau *r){
    Segment *s = malloc(sizeof(Segment));
    s->NumRes = num_reseau;
    s->p1 = seg_pt1;
    s->p2 = seg_pt2;
    s->HouV = horizontal_ou_vertical(seg_pt1, seg_pt2, r);
    s->Lintersec = NULL;
    return s
}

int horizontal_ou_vertical(int seg_pt1, int seg_pt2, Reseau* r){
    if (r->T_pt[seg_pt1]->x == r->T_pt[seg_pt2]->x){
        return 1;
    }
    return 0;
}