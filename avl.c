#include "avl.h"

int main(){
    char *nom ="Instance_Netlist/alea0500_500_90_033.net";
    Netlist *n = lecture_netlist(nom);
    intersec_balayage(n);
    sauvegarde_intersection(n,nom);
}

Noeud *Prem_Noeud_apres(ABR ab, double y){
	if(ab == NULL) return NULL;
    
    if(y < ab->y){
        ABR inf = Prem_Noeud_apres(ab->fg, y);
        if (inf != NULL){
            return inf;
        }
        /* S'il n'existe pas de noeud inférieur au noeud actuel et suppérier à y, alors
            on a le bon */
        return ab;
    }else{
        return Prem_Noeud_apres(ab->fd, y);
    }
}

Noeud *creerFeuille(Segment *seg, Netlist *n){
	Noeud *f = (Noeud *) malloc(sizeof(Noeud));
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
	majhauteur((*ab)->fd);
    majhauteur(*ab);
}

void rotationGauche(ABR *ab){
	ABR r = (*ab);
	ABR d = r->fd;

	r->fd = d->fg;
	d->fg = r;
	*ab = d;
	majhauteur((*ab)->fg);
    majhauteur(*ab);
}

void majhauteur(ABR ab){
    ab->hauteur = 1 + max(hauteur(ab->fg), hauteur(ab->fd));
}


void insererElnt_avec_eq(ABR *ab, Segment *seg, Netlist *n){
	if(*ab == NULL){
		*ab = creerFeuille(seg, n);
	}else{
        double y = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
		if( y <= (*ab)->y ){
			insererElnt_avec_eq(&((*ab)->fg), seg, n);
		}else{
			insererElnt_avec_eq(&((*ab)->fd), seg, n);
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
            if( hauteur( (*ab)->fd->fd ) < hauteur( (*ab)->fd->fg ) ){
                rotationDroite( &((*ab)->fd));
            }
            rotationGauche(ab);
	    }
    }
}

ABR coupe_max(ABR *ab){
    if((*ab)->fd == NULL){
        ABR res = (*ab);
        (*ab) = res->fg;
        return res;
    }
    return coupe_max(&((*ab)->fd));
}

void supprimer_avc_eq(ABR *ab, Segment *seg, Netlist *n){
    ABR *a = chercher_noeud(ab, seg, n);
    ABR temp = *a;
    if(temp == NULL){
        fprintf(stderr, "Erreur : le noeud à supprimer n'existe pas\n");
    }else{
        if((*a)->fg == NULL){
            *a = (*a)->fd;
        }else if((*a)->fd == NULL){
            *a = (*a)->fg;     
        }else{
            ABR r = coupe_max(&((*a)->fg));
            r->fg = (*a)->fg;
            r->fd = (*a)->fd;
            *a = r;
        }
        free(temp); 
    }
    hauteur_abr(*ab);
}

ABR *chercher_noeud(ABR *ab, Segment *seg, Netlist *n){
    if(*ab == NULL || (*ab)->seg == seg){
        return ab;
    }
    double y = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

    if(y < (*ab)->y){
        return chercher_noeud(&((*ab)->fg), seg, n);
    }
    if(y > (*ab)->y){
        return chercher_noeud(&((*ab)->fd), seg, n);
    }
    /* Il se peut qu'on ai 2 y égaux, et dans ce cas le segment peut être à droite ou à gauche à cause des rotations */
    ABR *gauche = chercher_noeud(&((*ab)->fg), seg, n);
    if((*gauche) != NULL){
        return gauche;
    }else{
        return chercher_noeud(&((*ab)->fd), seg, n);
    }
}


void hauteur_abr(ABR a){
    if(a != NULL){
        hauteur_abr(a->fg);
        hauteur_abr(a->fd);
        a->hauteur = 1 + max(hauteur(a->fg), hauteur(a->fd));
    }
}

void intersec_avl(Netlist *n){
    Echeancier *e = creer_echeancier(n);
    int i;
    ABR ab = NULL;
    double y1, y2;
    Segment *seg;
    ABR h;
    for(i=0;i<e->taille_tab;i++){
        seg = e->tab_ex[i]->PtrSeg;
        if(e->tab_ex[i]->VouGouD == 1){
            insererElnt_avec_eq(&ab, seg, n);
        }else if(e->tab_ex[i]->VouGouD == 2){
            supprimer_avc_eq(&ab, seg, n);
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
                h = Prem_Noeud_apres(ab, h->y);
            }
        }
    }
}