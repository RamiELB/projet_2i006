#include "benchmarking.h"

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Il faut en argument le nom du fichier de l'instance\n");
        return 0;
    }
    test_instance(argv[1]);
    return EXIT_SUCCESS;
}


void test_instance(char* nom_fichier){
    Netlist* n = lecture_netlist(nom_fichier);    
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    temps_initial = clock();
    intersect_naif(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f\n", temps_cpu);
    
    n = lecture_netlist(nom_fichier);
    temps_initial = clock();
    intersec_balayage(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f\n", temps_cpu);
    
    
    n = lecture_netlist(nom_fichier);
    temps_initial = clock();
    intersec_avl(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f\n", temps_cpu);
    
}
