#include "visugraphe.h"

int main(int argc, char** argv) {
    if(argc != 5){
        fprintf(stderr, "Il faut en argument le nom du fichier du graphe à créer, le nom du fichier des intersections, suivi des dimensions voulues\n");
        return 0;
    }
    char* fname = argv[1];
    char* fint = argv[2];
    int sizeX = (int) strtol(argv[3], (char **)NULL, 10);
    int sizeY = (int) strtol(argv[4], (char **)NULL, 10);
    
    Netlist *n = lecture_netlist(fname);
    if(n == NULL){
        fprintf(stderr, "Echec de la création de la netlist\n");
        return 0;
    }
    Graphe *g = creer_graphe(n, fint);
    SVGwriter svg;
    SVGinit(&svg, fname, sizeX, sizeY);
    SVGpointColor(&svg, Black);
    SVGlineColor(&svg, Black);
    int i;
    for(i=0; i<(g->nb_sommets); i++){   
        dessine_sommets_et_continuite(n, g->tab_sommets[i], &svg);
    }
    for(i=0; i<(g->nb_conflits); i++){
        SVGlineColor(&svg, Red);
        dessine_conflits(n, g, g->tab_conflits[i], &svg);
    }
    SVGfinalize(&svg);
    return EXIT_SUCCESS;
}

void dessine_sommets_et_continuite(Netlist* n, Sommet* s, SVGwriter* svg){
    if(s->seg != NULL){
        Point* p1 = n->T_Res[s->seg->NumRes]->T_Pt[s->seg->p1];
        Point* p2 = n->T_Res[s->seg->NumRes]->T_Pt[s->seg->p2];
        double x = x_milieu_segment(n, s->seg);
        double y = y_milieu_segment(n, s->seg);
        SVGpoint(svg, x, y);
        SVGline(svg, x, y, p1->x, p1->y);
        SVGline(svg, x, y, p2->x, p2->y);
    } else if(s->pt != NULL){
        SVGpoint(svg, s->pt->x, s->pt->y);
    }
    
    
}

void dessine_conflits(Netlist* n, Graphe* g, Arrete* a, SVGwriter* svg){
    Segment* seg1 = g->tab_sommets[a->som1]->seg;
    Segment* seg2 = g->tab_sommets[a->som2]->seg;
    double x1 = x_milieu_segment(n, seg1);
    double y1 = y_milieu_segment(n, seg1);
    
    double x2 = x_milieu_segment(n, seg2);
    double y2 = y_milieu_segment(n, seg2);
    SVGline(svg, x1, y1, x2, y2);
    
}

double x_milieu_segment(Netlist* n, Segment* s){
    Point* p1 = n->T_Res[s->NumRes]->T_Pt[s->p1];
    Point* p2 = n->T_Res[s->NumRes]->T_Pt[s->p2];
    
    return (p1->x + p2->x)/2.0;
}

double y_milieu_segment(Netlist* n, Segment* s){
    Point* p1 = n->T_Res[s->NumRes]->T_Pt[s->p1];
    Point* p2 = n->T_Res[s->NumRes]->T_Pt[s->p2];
    
    return (p1->y + p2->y)/2.0;
}
