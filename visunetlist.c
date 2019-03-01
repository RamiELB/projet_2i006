int main(int argc, char** argv) {
    
    char* fname = argv[1] 
    int sizeX = (int) strtol(argv[2], (char **)NULL, 10)
    int sizeY = (int) strtol(argv[3], (char **)NULL, 10)
    
    Netlist *n = lecture_netlist(fname);
    SVGwriter svg;
    SVGinit(&svg, "test.txt", sizeX, sizeY);
    SVGpointColor(&svg, Black);
    for(i=0; i<(n->NbRes); i++){   
        SVGlineRandColor(&svg); //Nouvelle couleur pour un nouveau reseau
        for(j=0; j<(n->T_Res[i]->NbPt); j++){
            SVGpoint(&svg, T_Res[i]->T_Pt[j]->x, T_Res[i]->T_Pt[j]->y);
        }
        
    }
    SVGfinalize(&svg);
}

void dessine_segments(reseau *r, SVGwriter *svg){
    Cell_Segment *cs;
    compte_seg_reseau(r, &cs);
    Cell_Segment *c;
    for(c=cs; c != NULL; c=c->suiv){
        SVGline(svg,  r->T_Pt[c->seg->p1]->x,  r->T_Pt[c->seg->p1]->y, r->T_Pt[c->seg->p2]->x, r->T_Pt[c->seg->p2]->y);
    }
}

void dessine_points(Reseau* r, SVGwriter* svg){
    for(i=0; i<(r->NbPt); i++){
        SVGpoint(svg, r->T_Pt[i]->x, r->T_Pt[i]->y);
    }
}

