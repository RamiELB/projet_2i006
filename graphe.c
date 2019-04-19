#include "graphe.h"

/*
int main(){
    char*name = "Instance_Netlist/c1.net";
    Netlist *n = lecture_netlist(name);
    intersect_naif(n);
    sauvegarde_intersection(n, name);
    Graphe *g = creer_graphe(n, "Instance_Netlist/c1.net.int");
}
*/

Graphe *creer_graphe(Netlist *n, char *fic_int){
    //printf("Création du graphe...\n");
    if(n == NULL){
        fprintf(stderr, "Netlist NULL, impossible de créer le graphe\n");
        return NULL;
    }
    Graphe *g = malloc(sizeof(Graphe));

    sommets_graphe(g, n); /* Rempli et alloue tab_sommets et nb_sommets */

    arretes_conflits(g, fic_int, n); /* Rempli et alloue tab_conflits et nb_conflits */

    arretes_continu(g, n); /* Rempli les arretes de continuite */

    //printf("Graphe crée avec succès\n");
    return g;
}

void arretes_continu(Graphe *g, Netlist *n){
    int i, idpoint;
    Arrete *a;
    for(i=0;i<g->nb_sommets;i++){
        if(g->tab_sommets[i]->seg != NULL){
            idpoint = chercher_sommet_pt(n, g, g->tab_sommets[i]->seg->NumRes, g->tab_sommets[i]->seg->p1);
            a = creer_arrete(-1, i, idpoint);
            ajout_arrete(g->tab_sommets, a);

            idpoint = chercher_sommet_pt(n, g, g->tab_sommets[i]->seg->NumRes, g->tab_sommets[i]->seg->p2);
            a = creer_arrete(-1, i, idpoint);
            ajout_arrete(g->tab_sommets, a);
        }
    }
}

void arretes_conflits(Graphe *g, char* fic_int, Netlist *n){
    //g->nb_conflits = compte_intersec(fic_int);
    //g->tab_conflits = (Arrete **) malloc(g->nb_conflits * sizeof(Arrete *));
    FILE *f = fopen(fic_int, "r");
    if(f == NULL){
        fprintf(stderr, "Erreur ouverture fichier dans arretes_conflits\n");
        return;
    }
    char ligne[128];
    int numres1, numres2, pt11, pt12, pt21, pt22;
    int som1, som2;
    Segment *seg1, *seg2;
    Arrete *a;
    int id=0;
    while(fgets(ligne,128,f)){
        sscanf(ligne,"%d %d %d %d %d %d", &numres1, &pt11, &pt12, &numres2, &pt21, &pt22);
        seg1 = chercher_segment(n, numres1, pt11, pt12);
        seg2 = chercher_segment(n, numres2, pt21, pt22);
        som1 = chercher_sommet_seg(seg1, g);
        som2 = chercher_sommet_seg(seg2, g);
        a = creer_arrete(id, som1, som2);
        //g->tab_conflits[id] = a;
        ajout_arrete(g->tab_sommets, a);
        id++;
    }
    fclose(f);
}

void ajout_arrete(Sommet **tab_sommets, Arrete *a){
        /* Ajout dans le premier sommet */
    Elem_Arrete *ea = creer_elem_arrete(a);
    ea->suiv = tab_sommets[a->som1]->liste_arretes;
    tab_sommets[a->som1]->liste_arretes = ea;

        /* Ajout dans le second sommet */
    ea = creer_elem_arrete(a);
    ea->suiv = tab_sommets[a->som2]->liste_arretes;
    tab_sommets[a->som2]->liste_arretes = ea;
}

Elem_Arrete *creer_elem_arrete(Arrete *a){
    Elem_Arrete *ea = malloc(sizeof(Elem_Arrete));
    ea->a = a;
    return ea;
}

Arrete *creer_arrete(int id, int som1, int som2){
    Arrete *a = (Arrete *) malloc(sizeof(Arrete));
    a->id = id;
    a->som1 = som1;
    a->som2 = som2;
    return a;
}

Segment *chercher_segment(Netlist *n, int numres, int pt1, int pt2){
    Cell_segment *cs = n->T_Res[numres]->T_Pt[pt1]->Lincid;
    while(cs != NULL){
        if((cs->seg->p1 == pt1 && cs->seg->p2 == pt2) || (cs->seg->p2 == pt1 && cs->seg->p1 == pt2)){
            return cs->seg;
        }
        cs = cs->suiv;
    }
    fprintf(stderr,"Le segment recherché n'éxiste pas\n");
    return NULL;
}

int chercher_sommet_seg(Segment *seg, Graphe *g){
    int i;
    for(i=0;i<g->nb_sommets;i++){
        if(g->tab_sommets[i]->seg == seg){
            return i;
        }
    }
    fprintf(stderr,"Le sommet recherché n'existe pas\n");
    return 0;
}

int chercher_sommet_pt(Netlist *n, Graphe *g, int numres, int p1ou2){
    Point *p = n->T_Res[numres]->T_Pt[p1ou2];
    int i;
    for(i=0;i<g->nb_sommets;i++){
        if (g->tab_sommets[i]->pt == p){
            return i;
        }
    }
    fprintf(stderr, "Le point recherché n'a pas été trouvé");
    return -1;
}

void sommets_graphe(Graphe *g, Netlist *n){
    int nb_seg;
    Segment **tab_seg = tab_segments_netlist(n, &nb_seg); //va stocker le nombre de segments dans nb_seg
    g->nb_sommets = nb_seg + nb_points(n);


    int idsom=0;
    int i, j;
    g->tab_sommets = (Sommet **) malloc(g->nb_sommets * sizeof(Sommet *));
    for(i=0;i<nb_seg;i++){
        g->tab_sommets[idsom] = creer_sommet_seg(tab_seg[i], idsom);
        idsom++;
    }
    for(i=0;i<n->NbRes;i++){
        for(j=0;j<n->T_Res[i]->NbPt;j++){
        g->tab_sommets[idsom] = creer_sommet_pt(n->T_Res[i]->T_Pt[j], idsom);
        idsom++;
        }
    }
}

Sommet *creer_sommet_seg(Segment *seg, int id){
    Sommet *s = (Sommet *) malloc(sizeof(Sommet));
    s->id = id;
    s->seg = seg;
    s->pt = NULL;
    s->liste_arretes = NULL;
    return s;
}

Sommet *creer_sommet_pt(Point *p, int id){
    Sommet *s = (Sommet *) malloc(sizeof(Sommet));
    s->id = id;
    s->seg = NULL;
    s->pt = p;
    s->liste_arretes = NULL;
    return s;
}

int compte_intersec(char *fic_int){
    FILE *f = fopen(fic_int, "r");
    if(f == NULL){
        fprintf(stderr, "Erreur ouverture fichier dans compte_intersec\n");
        return 0;
    }
    char ligne[128];
    int cpt=0;
    while(fgets(ligne,128,f)){
        cpt++;
    }
    fclose(f);
    return cpt;
}
