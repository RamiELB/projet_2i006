#include "perf_intersec.h"


int main(){
    int i;
    int taille = 17;
    Netlist **tab_netlist = malloc(taille * sizeof(Netlist *));
    char **list_netlist = {"Instance_Netlist/alea0030_030_10_088.net",
                        "Instance_Netlist/alea0030_030_90_007.net",
                        "Instance_Netlist/alea0100_050_10_097.net",
                        "Instance_Netlist/alea0100_080_90_024.net",
                        "Instance_Netlist/alea0300_300_10_044.net",
                        "Instance_Netlist/alea0300_300_90_099.net",
                        "Instance_Netlist/alea0500_500_10_054.net",
                        "Instance_Netlist/alea0500_500_90_033.net",
                        "Instance_Netlist/c1.net",
                        "Instance_Netlist/c4.net",
                        "Instance_Netlist/c5_2.net",
                        "Instance_Netlist/c5.net",
                        "Instance_Netlist/ibm01-10000_2.net",
                        "Instance_Netlist/ibm01-1000_2.net",
                        "Instance_Netlist/ibm01_2.net",
                        "Instance_Netlist/ibm01-5000_2.net",
                        "Instance_Netlist/test.net"};
    initialize_tab_netlist(tab_netlist, list_netlist, taille);
    double tps_balayage = 0;
    double tps_naif = 0;
    double tps_avl = 0;
    for(i=0;i<taille;i++){
        tps_balayage += temps(tab_netlist[i], 'b');
    }
    free_tab_netlist(tab_netlist, taille);
    initialize_tab_netlist(tab_netlist, list_netlist, taille);
    for(i=0;i<taille;i++){
        tps_naif += temps(tab_netlist[i], 'n');
    }
    free_tab_netlist(tab_netlist, taille);
    initialize_tab_netlist(tab_netlist, list_netlist, taille);
    for(i=0;i<taille;i++){
        tps_avl += temps(tab_netlist[i], 'a');
    }
    free_tab_netlist(tab_netlist, taille);
    printf("Temps total balayage : %f \n", tps_balayage);
    printf("Temps total naif : %f \n", tps_naif);
    printf("Temps total avl : %f \n", tps_avl);
    return 0;
}


double temps(Netlist *n, char mode){
    clock_t  temps_initial;
    clock_t  temps_final;
    double temps_cpu;
    if(mode == 'b'){
        temps_initial = clock();
        intersec_balayage(n);
        temps_final = clock();
    }else if(mode == 'n'){
        temps_initial = clock();
        intersect_naif(n);
        temps_final = clock();
    }else{
        temps_initial = clock();
        intersec_avl(n);
        temps_final = clock();
    }
	temps_cpu = (( double)(temps_final  - temps_initial)*1000)/CLOCKS_PER_SEC;
    return temps_cpu;
}

void initialize_tab_netlist(Netlist **n, char** list, int taille){
    int i;
    for(i=0;i<taille;i++){
        n[i] = lecture_netlist(list[i]);
    }
}

void free_tab_netlist(Netlist **n, int taille){
    int i;
    for(i=0;i<taille;i++){
        free_netlist(n[i]);
    }
}