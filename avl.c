#include "avl.h"

Noeud *rechercherValeur(ABR ab, Segment *seg, Netlist *n){
	if(ab == NULL) return NULL;
    
	if(ab->seg == seg) return ab;

    double y = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

	if(ab->y < y) 
		return rechercherValeur(ab->fd, seg, n);
	else
		return rechercherValeur(ab->fg, seg, n);
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