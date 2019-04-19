#include "essai.h"

int main(){
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    char* fic = "Instance_Netlist/c1.net";
    char* ficint = "Instance_Netlist/c1.net.int";
    Netlist* n = lecture_netlist(fic);
    Graphe* g = creer_graphe(n, ficint);
    
    printf("Temps de calcul pour attribuer une face à chaque segment\n");
    temps_initial = clock();
    tab_face(g);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("Methode naive : %f\n", temps_cpu);
    
    temps_initial = clock();
    int *S = Ajout_vias_cycle_impair(g);
    S = bicolore(g, S);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("Methode cycle : %f\n", temps_cpu);
    
    return EXIT_SUCCESS;
}
