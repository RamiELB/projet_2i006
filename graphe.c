#include "graphe.h"

Graphe *creer_graphe(char *fic_netlist, char *fic_int){
    Netlist *n = lecture_netlist(fic_netlist);
    Graphe *g = malloc(sizeof(Graphe));

    int nbinter = compte_intersec(fic_int);
    int nb_seg;
    Segment **tab_seg = tab_segments_netlist(n, nb_seg);
    int nb_sommets = nb_seg + nb_points(n);
    int nb_arretes = (2 * nb_seg) + nbinter;
    g->nb_sommets = nb_sommets;
    g->nb_arretes = nb_arretes;
    int idsom=0;
    int i, j;
    g->tab_sommets = (Sommet **) malloc(nb_sommets * sizeof(Sommet *));
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

    FILE *f = fopen(fic_int, "r");
    if(f == NULL){
        fprintf(stderr, "Erreur ouverture fichier dans compte_intersec\n");
        return NULL;
    }
    char ligne[128];
    int numres1, numres2, pt11, pt 12, pt21, pt22;
    Sommet *som1, *som2;
    Seg *seg1, *seg2;
    while(fgts(ligne,128,f)){
        sscanf(ligne,"%d %d %d %d %d %d", numres1, pt11, pt12, numres2, pt21, pt22);
        seg1 = chercher_segment(n, numres1, pt11, pt12);
        seg2 = chercher_segment(n, numres2, pt21, pt22);
        som1 = chercher_sommet(seg1, g->tab_sommets);
        som2 = chercher_sommet(seg2, g->tab_sommets);
    }

}

Sommet *creer_sommet_seg(Segment *s, int id){
    Sommet *s = (Sommet *) malloc(sizeof(Sommet));
    s->id = id;
    s->p = NULL;
    s->seg = s;
    s->nb_arretes = 0;
    s->liste_arretes = NULL;
    return s;
}

Sommet *creer_sommet_pt(Point *p, int id){
    Sommet *s = (Sommet *) malloc(sizeof(Sommet));
    s->id = id;
    s->p = p;
    s->seg = NULL;
    s->nb_arretes = 0;
    s->liste_arretes = NULL;
    return s;
}

int compte_intersec(char *fic_int){
    FILE *f = fopen(fic_int, "r");
    if(f == NULL){
        fprintf(stderr, "Erreur ouverture fichier dans compte_intersec\n");
        return 0;
    }
    char[128] ligne;
    int cpt=0;
    while(fgets(ligne,128,f)){
        cpt++;
    }
    fclose(f);
    return cpt;
}