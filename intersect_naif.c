void intersect_naif(Netlist *n, segment **tab_seg){
    int taille_tab = cpt_segments_netlist(n);
    int i;
    int j;
    for(i=0; i<taille_tab; i++){
        for(j=i; j<taille_tab; j++){
            if(intersection(n, tab_seg[i], tab_seg[j])){
                Cell_segment* new_cell = (Cell_segment*)malloc(sizeof(Cell_segment));
                new_cell->seg = tab_[j];
                if(tab_seg[i]->Lintersect == NULL){
                    tab_seg[i]->Lintersect = new_cell;
                } else{
                    Cell_segment* tete = tab_seg[i]->Lintersect;
                    new_cell->suiv = tete;
                    tab_seg[i]->Lintersect = new_cell;
                    
                }
            }
        }  
    }
    
}
