#include "netlist.h"

Netlist *lecture_netlist(char* nom_fichier){
    FILE *f = fopen(nom_fichier, "r");
    if(f == NULL){
        fprintf(stderr, "Erreur ouverture fichier\n");
        return NULL;
    }
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


    char ligne[30];
    fgets(ligne,30,f);
    
    for(grosseboucle=0;grosseboucle<nbres;grosseboucle++){
        lire_ligne(f,ligne,&num_reseau, &nb_pts, &nb_seg); /* lecture d'un nouveau réseau */
        r = nouveau_reseau(num_reseau, nb_pts);

            /* LECTURE DES POINTS */
        while(lire_ligne(f,ligne, &num_point,&xint,&yint) == 3){ 
            /* TANT QUE L'ON LIT 3 NOMBRES, ON LIT DES POINTS */
            x = (double) xint;
            y = (double) yint;
            p = nouveau_point(num_reseau,x,y);
            r->T_Pt[num_point] = p;
        }
        rewind_line(f);
            /* LECTURE DES SEGMENTS */
        while(lire_ligne(f,ligne, &seg_pt1,&seg_pt2,&varquisertarien) == 2){
            /* TANT QUE L'ON LIT 2 NOMBRES, ON LIT DES SEGMENTS */
            seg = nouveau_segment(seg_pt1, seg_pt2, r);
            cellseg = nouveau_cellsegment(seg);
            ajout_cellseg_pt(cellseg, r);
        }
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

    /* Pour le second point il faut faire une copie de cellseg */
    Cell_segment *cs2 = copie_cellsegment(cellseg);
    cs2->suiv = r->T_Pt[cellseg->seg->p2]->Lincid;
    r->T_Pt[cellseg->seg->p2]->Lincid = cs2;
}

int lire_ligne(FILE *f, char* ligne, int *i, int *j, int *k){
    if (fgets(ligne,30,f) != NULL){
        return sscanf(ligne,"%d %d %d", i,j,k);
    }
    return 0;
}

void rewind_line(FILE *f){
    do{
        fseek(f,-2,SEEK_CUR);
    }while((fgetc(f) != '\n'));
}






                                /* REECRITURE DE LA NETLIST */
    /* ------------------------------------------------------------------------------------- */
void ecrire_netlist(Netlist *n, char *nomfichier){
    FILE *f = fopen(nomfichier, "w");
    if(f == NULL){
        printf("Erreur ouverture fichier\n");
        return;
    }
    int i;
    fprintf(f,"%d\n", n->NbRes);

    for(i=0;i<n->NbRes;i++){
        ecrire_reseau(f,n->T_Res[i]);
    }
    fclose(f);
}

void ecrire_reseau(FILE *f, Reseau *r){
    Cell_segment **cs = malloc(sizeof(Cell_segment *));
    int nbseg = compte_seg_reseau(r, cs);
    fprintf(f,"%d %d %d\n", r->NumRes, r->NbPt, nbseg);
    ecrire_points(f, r);
    ecrire_segments(f, *cs);
    free_chaine_cs(cs);
    free(cs);
}


void ecrire_points(FILE *f, Reseau *r){
    int i;
    for(i=0;i<r->NbPt;i++){
        fprintf(f, "  %d %d %d\n", i, (int) r->T_Pt[i]->x, (int) r->T_Pt[i]->y);
    }
}


void ecrire_segments(FILE *f, Cell_segment *cs){
    Cell_segment *c = cs;
    while(c != NULL){
        fprintf(f, "  %d %d\n", c->seg->p1, c->seg->p2);
        c=c->suiv;
    }
}



    /* COMPTAGE DES SEGMENTS D'UN RESEAU */
int compte_seg_reseau(Reseau *r, Cell_segment **cs){
    *cs = (Cell_segment *) malloc(sizeof(Cell_segment));
    (*cs)->suiv = NULL;
    (*cs)->seg = NULL;
    int nb_seg = 1;
    int i=0;
    for(i=0;i<r->NbPt;i++){
        nb_seg += chainage_cell_seg(r->T_Pt[i], cs);   
    }
    return nb_seg;
}

int chainage_cell_seg(Point *p, Cell_segment **cs){
    int nb_seg_pt = 0;
        /* Première insertion */
    if((*cs)->seg == NULL){
        (*cs)->seg = p->Lincid->seg;
    }
    Cell_segment *c = p->Lincid;
    Cell_segment *nv_cs;
    while(c != NULL){
        if(seg_pas_dans_chaine(*cs, c->seg)){
            nv_cs = nouveau_cellsegment(c->seg);
            nv_cs->suiv = *cs;
            *cs = nv_cs;
            nb_seg_pt++;
        }
        c=c->suiv;
    }
    return nb_seg_pt;
}

int seg_pas_dans_chaine(Cell_segment *cs, Segment *s){
    Cell_segment *c = cs;
    while(c != NULL){
        if(c->seg == s){
            return 0;
        }
        c = c->suiv;
    }
    return 1;
}

void free_chaine_cs(Cell_segment **cs){
    Cell_segment *prec = *cs;
    while(*cs != NULL){
        *cs = (*cs)->suiv;
        free(prec);
        prec = *cs;
    }
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

void free_netlist(Netlist *n){
    int i;
    for(i=0;i<n->NbRes;i++){
        free_reseau(n->T_Res[i]);
    }
    free(n);
}

void free_reseau(Reseau *r){
    int i;
    for(i=0;i<r->NbPt;i++){
        free_chaine_cs(&(r->T_Pt[i]->Lincid));
        free(r->T_Pt[i]);
    }
    free(r);
}