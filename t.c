typedef struct cell_t {
    Segment *seg;
    struct cell_t *suiv;
} Cell_t

void Inserer(Segment *s, Cell_T *T){
    
}

void Supprimer(Segment *s, Cell_T *T){
    Cell_t* ct = T;
    Cell_t* ct_precedent;
    Cell_t* ct_suivant;
    
    while(ct->seg != s || ct->suiv != NULL){
        ct_precedent = ct;
        ct = ct->suiv;
        ct_suivant = ct->suiv;
    }
    ct_precedent->suiv = ct_suivant;
}
