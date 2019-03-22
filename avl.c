#include "avl.h"

Noeud *Prem_Noeud_apres(ABR ab, double y){
	if(ab == NULL) return NULL;
    
    if(ab->y > y){
        ABR *inf = Prem_Noeud_apres(ab->gauche, y);
        if (inf != NULL){
            return inf;
        }
        /* S'il n'éxiste pas de noeud inférieur au noeud actuel et suppérier à y, alors
            on a le bon */
        return ab;
    }else{
        return Prem_Noeud_apres(ab->fd, y);
    }
}

Noeud *creerFeuille(Segment *seg, Netlist *n){
	Noeud *f = malloc(sizeof(Noeud));
    f->y = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
	f->seg = seg;
	f->fg = NULL;
	f->fd = NULL;
	f->hauteur = 1;
	return f;
}

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int hauteur(ABR ab){
	if(ab == NULL) return 0;
	return ab->hauteur;
}

void rotationDroite(ABR *ab){
	ABR r = (*ab);
	ABR g = r->fg;

	r->fg = g->fd;
	g->fd = r;
	*ab = g;
	majhauteur(*ab);
}
void rotationGauche(ABR *ab){
	ABR r = (*ab);
	ABR d = r->fd;

	r->fd = d->fg;
	d->fg = r;
	*ab = d;
	majhauteur(*ab);
}

void majhauteur(ABR ab){
    if(ab != NULL){
        majhauteur(ab->fg);
        majhauteur(ab->fd);
        ab->hauteur= 1 + max(hauteur(ab->fg), hauteur(ab->fd));
    }
}


void insererElnt_avec_eq(ABR *ab, Segment *seg, Netlist *n){
	if(*ab == NULL){
		*ab = creerFeuille(seg, n);
	}else{
        double y = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
		if( (*ab)->y >= y){
			insererElnt_avec_eq(&((*ab)->fd), seg, n);
		}else{
			insererElnt_avec_eq(&((*ab)->fg), seg, n);
		}
        int hg = hauteur((*ab)->fg);
        int hd = hauteur((*ab)->fd);
        (*ab)->hauteur = 1 + max(hg,hd);
        if( hg - hd == 2){
            if( hauteur( (*ab)->fg->fg ) < hauteur( (*ab)->fg->fd ) ){
                rotationGauche( &((*ab)->fg));
            }
            rotationDroite(ab);
        }else if ( hg - hd == -2 ){
            if( hauteur( (*ab)->fd->fd ) < hauteur( (*ab)->fd->fd ) ){
                rotationGauche( &((*ab)->fg));
            }
            rotationGauche(ab);
	    }
    }
}


void intersec_avl(Netlist *n){
    Echeancier *e = creer_echeancier(n);
    int i;
    ABR *ab = NULL;
    double y1, y2;
    Segment *seg;
    ABR *h
    for(i=0;i<e->taille_tab;i++){
        seg = e->tab_ex[i]->PtrSeg;
        if(e->tab_ex[i]->VouGouD == 1){
            insererElnt_avec_eq(ab, seg, n);
        }else if(e->tab_ex[i]->VouGouD == 2){
            SUPPRIMERAVECELELQ
        }else{
            if(n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y < n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y){
                y1 = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y; 
                y2 = n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;
            }else{
                y2 = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y; 
                y1 = n->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;
            }
            h = Prem_Noeud_apres(ab, y1);
            while(h != NULL && h->y < y2){
                ajout_intersection(h->seg, seg);
                h = Prem_Noeud_apres(h);
            }
        }
    }
}
