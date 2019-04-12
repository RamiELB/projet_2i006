#include "via_naif.h"

int *tab_face(Graphe *g){
    int i;
    int id_premier_sommet;
    int id_sommet_actuel;
    Elem_Arrete *premiere_arrete;
    Elem_Arrete *arr_cour;
    int *tab_face = malloc(g->nb_sommets * sizeof(int));
    for(i=0;i<g->nb_sommets;i++){
        if(g->tab_sommets[i]->pt == NULL){
            //le sommet est un segment
            tab_face[i] = g->tab_sommets[i]->seg->HouV + 1;
        }else{
            tab_face[i] = 3;
            premiere_arrete = g->tab_sommets[i]->liste_arretes;
            if(premiere_arrete->a->som1 != i)
                id_premier_sommet = premiere_arrete->a->som1;
            else
                id_premier_sommet = premiere_arrete->a->som2;

            arr_cour = premiere_arrete->suiv;

            while (arr_cour != NULL){
                if(arr_cour->a->som1 != i)
                    id_sommet_actuel = arr_cour->a->som1;
                else
                    id_sommet_actuel = arr_cour->a->som2;

                if (g->tab_sommets[id_premier_sommet]->seg->HouV != g->tab_sommets[id_sommet_actuel]->seg->HouV)
                    tab_face[i] = 0;
                arr_cour = arr_cour->suiv;
            }
        }
    }
    return tab_face;
}
