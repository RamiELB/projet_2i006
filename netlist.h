#ifndef NETLIST_H
#define NETLIST_H
#include <stdlib.h>
#include <stdio.h>

struct segment;

typedef struct cell_segment{
    struct segment* seg;
    struct cell_segment* suiv;
} Cell_segment;

typedef struct segment{

    int NumRes;  /* Numero du reseau auquel appartient ce segment*/
    int p1, p2; /* Numero des points aux extremites du segment */
                  /* En utilisant la numerotation de T_Pt */
                  /* p1 est le point en bas a gauche par rapport a p2*/
                  
    int HouV;    /* 0 si Horizontal et 1 si Vertical */
    struct cell_segment* Lintersec; /* Liste des segments en intersection */
} Segment;

typedef struct point{
    double x, y; /* Coordonnees du point */
    int num_res; /* Numero du reseau contenant ce point = Index du tableau T_res*/
    Cell_segment* Lincid; /* Liste des segments incidents a ce point */
} Point;

typedef struct reseau{
    int NumRes; /* Numero du reseau = Indice dans le tableau T_Res */
    int NbPt;   /* Nombre de points de ce reseau */
    Point** T_Pt; /* Tableau de pointeurs sur chaque point de ce reseau */
} Reseau;

typedef struct netlist{
    int NbRes; /* Nombre de reseaux */
    Reseau** T_Res; /* Tableau pointant sur chaque reseau*/
} Netlist;






    /* Fonction principale qui va permettre de créer la Netlist */
Netlist *lecture_netlist(char* nom_fichier);



        /* FONCTIONS PERMETTANTS D'ALLOUER UNE NOUVELLE STRUCTURE ET 
                    DE RENVOYER LEURS ADRESSES                     */
Reseau *nouveau_reseau(int num_reseau, int nb_pts);

Point *nouveau_point(int num_reseau,double x,double y);

Segment *nouveau_segment(int seg_pt1, int seg_pt2, Reseau *r);

Cell_segment *nouveau_cellsegment(Segment *seg);



    /* Crée une copie d'un cellseg en lui allouant une nouvelle adresse 
                 Ne copie pas le champ suiv                          */
Cell_segment *copie_cellsegment(Cell_segment *cs);


    /* Renvoie 1 si le segment est verticale, 0 s'il est horizontal */
int horizontal_ou_vertical(int seg_pt1, int seg_pt2, Reseau* r);


    /* Ajout d'un cellseg dans la liste des points auxquels il est incident */
void ajout_cellseg_pt(Cell_segment *cellseg, Reseau *r);


    /* Fait appel à ajout_cell_seg pour chaque élément d'un tableau de cellseg */
void ajout_cellseg_tabseg(Cell_segment **tabseg, Reseau *r, int nb_seg);
    /* Ajout d'un cellseg dans la liste des segments auxquels il est incident */
void ajout_cellseg_seg(Cell_segment *cellseg, Reseau *r);


        /* FONCTIONS DE LECTURE DE FICHIER */
    /* Lis une ligne, stocke jusqu'à 3 entiers lus et renvoie le nombre d'entiers lus */
int lire_ligne(FILE *f, char* ligne, int *i, int *j, int *k);
    /* Replace le curseur au début de la ligne précédente */
void rewind_line(FILE *f); /* /!\ NE FONCTIONNE PAS EN DEBUT DE FICHIER /!\ */



    /* FONCTIONS POUR L'AFFICHAGE DE LA NETLIST */
void ecrire_netlist(Netlist *n, char *nomfichier);
void ecrire_reseau(FILE *f, Reseau *r);

    /* Compte les segments d'un réseau et rend la liste chainée de ces segments par effet de bord */
int compte_seg_reseau(Reseau *r, Cell_segment **cs);

int chainage_cell_seg(Point *p, Cell_segment **cs);
int seg_pas_dans_chaine(Cell_segment *cs, Segment *s);
void ecrire_points(FILE *f, Reseau *r);
void ecrire_segments(FILE *f, Cell_segment *cs);
void free_chaine_cs(Cell_segment **cs);

#endif /* NETLIST_H */