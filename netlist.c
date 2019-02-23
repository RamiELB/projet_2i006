#include "netlist.h"

Netlist *lecture_netlist(char* nom_fichier){
    FILE *f = fopen(nom_fichier, "r");
    Netlist *n = malloc(sizeof(Netlist));
    int nbres;
    fscanf(f,"%d", &nbres); //le nombre de réseau est sur la toute première ligne du fichier
    n->NbRes = nbres;
    int grosseboucle;

    n->T_Res = malloc(n->NbRes * sizeof(Reseau)); //allocation du tableau de réseaux

    /* Variables utiles à la création d'un réseau */
    int num_reseau, nb_pts, nb_seg;
    Reseau *r;
    Point *p;
    int num_point;
    int xint, yint;
    double x,y;
    Segment *seg;
    int seg_pt1, seg_pt2;
    Cell_segment *cellseg;
    int varquisertarien;
    /* Tableau pour stocker les pointeurs sur cellseg */
    int i; //compteur
    Cell_segment **tab_cellseg; 

    char ligne[30];
    fgets(ligne,30,f);
    
    for(grosseboucle=0;grosseboucle<nbres;grosseboucle++){
        lire_ligne(f,ligne,&num_reseau, &nb_pts, &nb_seg); /* lecture d'un nouveau réseau */
        r = nouveau_reseau(num_reseau, nb_seg);

            /* LECTURE DES POINTS */
        while(lire_ligne(f,ligne, &num_point,&xint,&yint) == 3){ 
            /* TANT QUE L'ON LIT 3 NOMBRES, ON LIT DES POINTS */
            x = (double) xint;
            y = (double) yint;
            p = nouveau_point(num_reseau,x,y);
            r->T_Pt[num_point] = p;
        }

        rewind_line(f);
        tab_cellseg = malloc(nb_seg * sizeof(Cell_segment *));
        i = 0;
            /* LECTURE DES SEGMENTS */
        while(lire_ligne(f,ligne, &seg_pt1,&seg_pt2,&varquisertarien) == 2){
            /* TANT QUE L'ON LIT 2 NOMBRES, ON LIT DES SEGMENTS */
            seg = nouveau_segment(seg_pt1, seg_pt2, r);
            cellseg = nouveau_cellsegment(seg);
            ajout_cellseg_pt(cellseg, r);
            tab_cellseg[i] = cellseg;
            i++;
        }
        ajout_cellseg_tabseg(tab_cellseg, r, nb_seg);
        free(tab_cellseg);

        n->T_Res[num_reseau] = r; /* ajout du reseau à la netlist */
        rewind_line(f);
    }
    return n;
}

Reseau *nouveau_reseau(int num_reseau, int nb_pts){
    Reseau *r = (Reseau *) malloc(sizeof(Reseau));
    r->NumRes = num_reseau;
    r->NbPt = nb_pts;
    r->T_Pt = (Point **) malloc(nb_pts * sizeof(Point *));
    return r;
}

Point *nouveau_point(int num_reseau,double x,double y){
    Point *p = (Point *) malloc(sizeof(Point));
    p->num_res = num_reseau;
    p->x = x;
    p->y = y;
    p->Lincid = NULL;
    return p;
}

Segment *nouveau_segment(int seg_pt1, int seg_pt2, Reseau *r){
    Segment *s = malloc(sizeof(Segment));
    s->NumRes = r->NumRes;
    s->p1 = seg_pt1;
    s->p2 = seg_pt2;
    s->HouV = horizontal_ou_vertical(seg_pt1, seg_pt2, r);
    s->Lintersec = NULL;
    return s;
}

Cell_segment *nouveau_cellsegment(Segment *seg){
    Cell_segment *cs = malloc(sizeof(Cell_segment));
    cs->seg = seg;
    cs->suiv = NULL;
    return cs;
}

Cell_segment *copie_cellsegment(Cell_segment *cs){
    Cell_segment *nouveau_cs = malloc(sizeof(Cell_segment));
    nouveau_cs->seg=cs->seg;
    nouveau_cs->suiv=NULL;
    return nouveau_cs;
}

int horizontal_ou_vertical(int seg_pt1, int seg_pt2, Reseau* r){
    if (r->T_Pt[seg_pt1]->x == r->T_Pt[seg_pt2]->x){
        return 1;
    }
    return 0;
}

void ajout_cellseg_pt(Cell_segment *cellseg, Reseau *r){
    /* ajout du cellseg incident à ses points dans la liste des points en question */
    cellseg->suiv = r->T_Pt[cellseg->seg->p1]->Lincid;
    r->T_Pt[cellseg->seg->p1]->Lincid = cellseg;

    cellseg->suiv = r->T_Pt[cellseg->seg->p2]->Lincid;
    r->T_Pt[cellseg->seg->p2]->Lincid = cellseg;
}

void ajout_cellseg_tabseg(Cell_segment **tabseg, Reseau *r, int nb_seg){
    int i;
    for(i=0;i<nb_seg;i++){
        ajout_cellseg_seg(tabseg[i], r);
    }
}

void ajout_cellseg_seg(Cell_segment *cellseg, Reseau *r){
    /* ajout des cellseg incident au cellseg en question dans la structure du segment */
    Cell_segment *cs;
    Cell_segment *nouveau_cs;
    for(cs = r->T_Pt[cellseg->seg->p1]->Lincid; cs != NULL; cs=cs->suiv){

        /* POUR NE PAS RAJOUTER UN SEGMENT DANS SA PROPRE LISTE DE SEGMENTS INCIDENTS */
        if(cs != cellseg){

            /* IL EST NECESSAIRE DE CREER UNE COPIE POUR NE PAS CONFONDRE LINCID ET LINTERSEC */
            nouveau_cs = copie_cellsegment(cs);

            /* AJOUT DU NOUVEAU CELLSEG DANS LA LISTE DU SEGMENT */
            nouveau_cs->suiv = cellseg->seg->Lintersec;
            cellseg->seg->Lintersec = nouveau_cs;
        }
    }

    /* ON REFAIT L'OPERATION POUR LE SECOND POINT DU SEGMENT */
    for(cs = r->T_Pt[cellseg->seg->p2]->Lincid; cs != NULL; cs=cs->suiv){
        if(cs != cellseg){
            nouveau_cs = copie_cellsegment(cs);
            nouveau_cs->suiv = cellseg->seg->Lintersec;
            cellseg->seg->Lintersec = nouveau_cs;
        }
    }
}

int lire_ligne(FILE *f, char* ligne, int *i, int *j, int *k){
    fgets(ligne,30,f);
    return sscanf(ligne,"%d %d %d", i,j,k);
}

void rewind_line(FILE *f){
    do{
        fseek(f,-2,SEEK_CUR);
    }while((fgetc(f) != '\n'));
}