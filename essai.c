#include "essai.h"

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Il faut 2 arguments : le chemin du fichier .net puis le chemin du fichier .int\nExemple : ./essai Instance_Netlist/c1.net Instance_Netlist/c1.net.int\n");
                return 0;
    }
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    char* fic = argv[1];
    char* ficint = argv[2];
    Netlist* n = lecture_netlist(fic);
    Graphe* g = creer_graphe(n, ficint);
    int *S;
    printf("Temps de calcul pour attribuer une face à chaque segment\n\n\n");
    temps_initial = clock();
    S = tab_face(g);
    temps_final = clock();
    temps_cpu = 1000*((double)(temps_final - temps_initial)/ CLOCKS_PER_SEC);

    int nbvias = 0;
    int i;
    for(i=0;i<g->nb_sommets;i++){
        if(S[i] == 0){
            nbvias++;
        }
    }
    printf("Methode naive\nvias : %d, temps : %f ms\n\n", nbvias, temps_cpu);
    

    temps_initial = clock();
    S = Ajout_vias_cycle_impair(g);
    S = bicolore(g, S);
    temps_final = clock();
    temps_cpu = 1000*((double)(temps_final - temps_initial)/ CLOCKS_PER_SEC);


    nbvias = 0;
    for(i=0;i<g->nb_sommets;i++){
        if(S[i] == 0){
            nbvias++;
        }
    }
    printf("Methode cycle\nvias : %d, temps : %f ms\n", nbvias, temps_cpu);
    
    return EXIT_SUCCESS;
}
