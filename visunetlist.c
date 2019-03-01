#include "visunetlist.h"

int main(int argc, char** argv) {
    
    char* fname = argv[1];
    int sizeX = (int) strtol(argv[2], (char **)NULL, 10);
    int sizeY = (int) strtol(argv[3], (char **)NULL, 10);
    
    Netlist *n = lecture_netlist(fname);
    SVGwriter svg;
    SVGinit(&svg, fname, sizeX, sizeY);
    SVGpointColor(&svg, Black);
    int i;
    for(i=0; i<(n->NbRes); i++){   
        dessine_reseau(n->T_Res[i], &svg);
    }
    SVGfinalize(&svg);
}

void dessine_reseau(Reseau *r, SVGwriter *svg){
    SVGpointColor(svg, Black);
    dessine_points(r,svg);
    dessine_segments(r,svg);
    SVGlineRandColor(svg);
}

void dessine_segments(Reseau *r, SVGwriter *svg){
    Cell_segment *cs;
    compte_seg_reseau(r, &cs);
    Cell_segment *c;
    for(c=cs; c != NULL; c=c->suiv){
        SVGline(svg,  r->T_Pt[c->seg->p1]->x,  r->T_Pt[c->seg->p1]->y, r->T_Pt[c->seg->p2]->x, r->T_Pt[c->seg->p2]->y);
    }
}

void dessine_points(Reseau* r, SVGwriter* svg){
    int i;
    for(i=0; i<(r->NbPt); i++){
        SVGpoint(svg, r->T_Pt[i]->x, r->T_Pt[i]->y);
    }
}

