#include "creationint.h"

int main(int argc, char** argv){
    
    if(argc != 2){
        fprintf(stderr, "Il faut en argument le nom du fichier de l'instance\n");
        return 0;
    }
    Netlist *n = lecture_netlist(argv[1]);
        intersec_balayage(n);
        
        sauvegarde_intersection(n, argv[1]);
}
