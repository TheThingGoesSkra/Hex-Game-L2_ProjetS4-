#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graphe.h"
#include "Plateau.h"
#include "Groupe.h"
#include "Const.h"
#include "Pont.h"

typedef struct hexsommet{
	int val;
	Liste l; //Liste des voisins
	Liste lcase; //Liste des cases du plateau correspondant au sommet
}sommet_int;

Sommet creer_sommet(int i, int j){
	Sommet aux=(Sommet)malloc(sizeof(sommet_int));
	assert(aux!=NULL);
	aux->val=0;
	aux->l=creer_liste();
	if(i>=0 && j>=0){
		aux->lcase=creer_liste();
		ajouter_elem_groupe(i,j,aux->lcase);
	}else
		aux->lcase=NULL;
	return aux;
}

/* On lie les sommets entre eux au fur et à mesure qu'ils sont créés 
   (donc on ne lie pas les sommets situés à droite et en bas du sommet en cours) */
void init_voisin(int i, int j){
	if(j-1>=0)
		lier_sommet(get_case_sommet(i,j),get_case_sommet(i,j-1));
	if(i-1>=0){
		lier_sommet(get_case_sommet(i,j),get_case_sommet(i-1,j));
		if(j+1<get_plat_taille())
			lier_sommet(get_case_sommet(i,j),get_case_sommet(i-1,j+1));
	}
}

void creer_bord(){
	Sommet w1,w2,b1,b2;
	w1=creer_sommet(-1,-1);
	set_sommet_value(w1,WHITE_edge);
	w2=creer_sommet(-1,-1);
	set_sommet_value(w2,WHITE_edge);
	b1=creer_sommet(-1,-1);
	set_sommet_value(b1,BLACK_edge);
	b2=creer_sommet(-1,-1);
	set_sommet_value(b2,BLACK_edge);
	for(int i=0;i<get_plat_taille();++i){
		lier_sommet(b1,get_case_sommet(i,0));
		lier_sommet(b2,get_case_sommet(i,get_plat_taille()-1));
		lier_sommet(w1,get_case_sommet(0,i));
		lier_sommet(w2,get_case_sommet(get_plat_taille()-1,i));
	}
}

void free_sommet(Sommet s){
	free_liste(s->l,0);
	free_liste(s->lcase,0);
	free(s);
	s=NULL;
}

int get_sommet_value(Sommet s){
	return s->val;
}

void set_sommet_value(Sommet s, int val){
	s->val=val;
}

Liste get_sommet_lcase(Sommet s){
	return s->lcase;
}

Liste get_sommet_lvoisin(Sommet s){
	return s->l;
}

void ajouter_voisin(Sommet s, Sommet s_add){
	s->l=ajouter_elem(s->l,s_add);
}

void lier_sommet(Sommet s1, Sommet s2){
	ajouter_voisin(s1,s2);
	ajouter_voisin(s2,s1);
}

void gerer_sommet_voisin(int lig, int col, int value){
	int found, done=0;
	Sommet s, aux, new_s;
	do{
		s=get_case_sommet(lig,col);
		// On cherche un sommet voisin de la même couleur 
		aux=ite_begin(s->l);
		while(!ite_isEnd(s->l) && aux->val!=value)
			aux=ite_next(s->l);
		// Si on le trouve on fusionne avec lui
		if(!ite_isEnd(s->l) && aux->val==value){
			new_s=aux;
			new_s->l=supprimer_elem(new_s->l,s);
			s->l=supprimer_elem(s->l,new_s);
			s->l=merge_liste(s->l,new_s->l);
			Sommet voisin=ite_begin(new_s->l);
			while(!ite_isEnd(new_s->l)){
				voisin->l=supprimer_elem(voisin->l,new_s);
				voisin->l=ajouter_elem(voisin->l,s);
				voisin=ite_next(new_s->l);
			}
			int ** e=ite_begin(new_s->lcase);
			while(!ite_isEnd(new_s->lcase)){
				set_case_sommet((*e)[0],(*e)[1],s);
				ajouter_elem(s->lcase,e);
				e=ite_next(new_s->lcase);
			}
			supprimer_elem(Liste_Groupe[value-1],new_s);

			Remplacer_Sommet_Pont(new_s,s,value);
			Supprimer_Pont2Sommets(s,s,value);
			Supprimer_Pont2Sommets(s,get_plat_bord(value,0),value);
			Supprimer_Pont2Sommets(s,get_plat_bord(value,1),value);

			free_sommet(new_s);
			done=1;	
			found=1;	
		}else
			found=0;
	}while(found);
	ajouter_elem(Liste_Groupe[value-1],s);
	if(done){
		// On regarde si le nouveau sommet joint les deux bords 
		int nbr=0;
		Sommet bord=ite_begin(s->l);
		while(!ite_isEnd(s->l)){
			if(bord->val==(value*-1)) // Si c'est un bord de la même couleur (cf Const.h)
				++nbr;
			bord=ite_next(s->l);
		}
		if(nbr==2) // Si le sommet joint les deux bords
			set_victory(value);
	}
}

/* ----------------- */
/* ----- DEBUG ----- */
/* ----------------- */

void afficher_voisin(int lig, int col){
	printf("\nListe (%d,%d)\n",lig,col);
	Sommet aux=get_case_sommet(lig,col);
	if(aux!=NULL)
		afficher_liste_sommet(aux->l);
}

void afficher_tout_voisin(){
	for(int i=0;i<get_plat_taille();++i)
		for(int j=0;j<get_plat_taille();++j)
			if(get_case(i,j)!=0)
				afficher_voisin(i,j);
}

void afficher_liste_sommet(Liste l){
	element e=ite_begin(l);
	while(!ite_isEnd(l)){
		printf("%d ",get_sommet_value(e));
		e=ite_next(l);
	}
	/*cellule* aux=l->sent->suiv;
	while(aux!=l->sent){
		printf("%d ",get_sommet_value(aux->elem));
		aux=aux->suiv;
	}*/
	printf("\n");
}

/* ----------------- */
