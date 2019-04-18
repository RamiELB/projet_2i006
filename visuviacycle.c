#include "visuviacycle.h"

int main(int argc, char** argv){
    
        if(argc != 5){
        fprintf(stderr, "Il faut en argument le nom du fichier du graphe à créer, le nom du fichier des intersections, suivi des dimensions voulues\n");
        return 0;
    }
    
    char* fic = argv[1];
    char* ficint = argv[2];
    int x = (int) strtol(argv[3], (char **)NULL, 10);
    int y = (int) strtol(argv[4], (char **)NULL, 10);
    Netlist *n = lecture_netlist(fic);
    Graphe *g = creer_graphe(n, ficint);
    int *S = Ajout_vias_cycle_impair(g);
    S = bicolore(g, S);
    affiche_solution_cycle(fic, n, g, x, y, S);
    
    return EXIT_SUCCESS;
}


void affiche_solution_cycle(char* fic, Netlist* n, Graphe* g, int x, int y, int* S){
    SVGwriter svg;
    SVGinit(&svg, fic, x, y);
    SVGpointColor(&svg, Black);
    int i;
    for(i=0; i<g->nb_sommets; i++){
        if(S[i]==0){
            Point* pt = g->tab_sommets[i]->pt;
            SVGpoint(&svg, pt->x, pt->y);
        } else if(S[i]==1 && g->tab_sommets[i]->pt == NULL){
            SVGlineColor(&svg, RoyalBlue);
            Point* pt1 = n->T_Res[g->tab_sommets[i]->seg->NumRes]->T_Pt[g->tab_sommets[i]->seg->p1];
            Point* pt2 = n->T_Res[g->tab_sommets[i]->seg->NumRes]->T_Pt[g->tab_sommets[i]->seg->p2];
            SVGline(&svg, pt1->x, pt1->y, pt2->x, pt2->y);

        } else if(S[i]==2 && g->tab_sommets[i]->pt == NULL){
            SVGlineColor(&svg, Red);
            Point* pt1 = n->T_Res[g->tab_sommets[i]->seg->NumRes]->T_Pt[g->tab_sommets[i]->seg->p1];
            Point* pt2 = n->T_Res[g->tab_sommets[i]->seg->NumRes]->T_Pt[g->tab_sommets[i]->seg->p2];
            SVGline(&svg, pt1->x, pt1->y, pt2->x, pt2->y);
            
        }
    }  
    SVGfinalize(&svg);
}

