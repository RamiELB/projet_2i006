void test_instance(char* nom_fichier){
    Netlist* n = lecture_netlist(nom_fichier);    
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    temps_initial = clock();
    intersect_naif(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f", temps_cpu);
    
    Netlist* n = lecture_netlist(nom_fichier);
    temps_initial = clock();
    intersec_balayage(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f", temps_cpu);
    
    
    Netlist* n = lecture_netlist(nom_fichier);
    temps_initial = clock();
    intersec_avl(n);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial));
    printf("%f", temps_cpu);
    
}
