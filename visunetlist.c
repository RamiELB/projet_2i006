

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
