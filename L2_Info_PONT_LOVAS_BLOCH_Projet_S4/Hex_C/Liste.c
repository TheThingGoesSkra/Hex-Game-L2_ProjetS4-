#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Liste.h"

typedef struct etcel {
	element elem;
	struct etcel * suiv;
	struct etcel * prec;
}cellule;

typedef struct etite {
	cellule * cour;
}ite_int;

typedef struct etliste {
	int taille;
	cellule * sent; //sentinelle
	ite_int * it; //iterateur
}liste_int;

Liste creer_liste(){
	Liste l;
	l=(Liste)malloc(sizeof(liste_int));
	assert(l!=NULL);
	l->sent=(cellule*)malloc(sizeof(cellule));
	assert(l->sent!=NULL);
	l->sent->elem=NULL;
	l->sent->suiv=l->sent;
	l->sent->prec=l->sent;
	l->taille=0;
	// Creation de l'itérateur associé à la liste
	l->it=(ite_int*)malloc(sizeof(ite_int));
	assert(l->it!=NULL);
	ite_begin(l);
	return l;
}

void free_liste(Liste l, int free_elem){
	if(l!=NULL){
		cellule * aux=l->sent->suiv;
		cellule * temp;
		while(aux!=l->sent){
			if(free_elem){
				free(aux->elem);
				aux->elem=NULL;
			}
			temp=aux;
			aux=aux->suiv;
			free(temp);
			temp=NULL;
		}
		free(l->sent);
		l->sent=NULL;
		free(l->it);
		l->it=NULL;
		free(l);
		l=NULL;
	}
}

int get_liste_taille(Liste l){
	return l->taille;
}

Liste ajouter_elem(Liste l, element e){
	cellule * cour=l->sent->suiv;
	while(cour!=l->sent && cour->elem!=e)
		cour=cour->suiv;
	if(cour->elem!=e){
		cellule * aux;
		aux=(cellule*)malloc(sizeof(cellule));
		assert(aux!=NULL);
		aux->elem=e;
		aux->prec=l->sent->prec;
		aux->suiv=l->sent;
		aux->prec->suiv=aux;
		l->sent->prec=aux;
		l->taille++;
	}
	return l;
}

Liste supprimer_elem(Liste l, element e){
	cellule * aux =l->sent->suiv;
	while(aux!=l->sent && aux->elem!=e)
		aux=aux->suiv;
	if(aux->elem==e){
		if(l->it->cour==aux)
			l->it->cour=l->it->cour->prec;
		aux->suiv->prec=aux->prec;
		aux->prec->suiv=aux->suiv;
		free(aux);
		aux=NULL;
		l->taille--;
	}
	return l;
}

Liste merge_liste(Liste l1, Liste l2){
	/*Liste laux=creer_liste();
	element aux;
	aux=ite_begin(l1);
	while(!ite_isEnd(l1)){
		laux=ajouter_elem(laux,aux);
		aux=ite_next(l1);
	}
	aux=ite_begin(l2);
	while(!ite_isEnd(l2)){
		laux=ajouter_elem(laux,aux);
		aux=ite_next(l2);
	}
	return laux;*/
	element aux;
	aux=ite_begin(l2);
	while(!ite_isEnd(l2)){
		l1=ajouter_elem(l1,aux);
		aux=ite_next(l2);
	}
	return l1;
}

Liste copier_liste(Liste l){
	Liste laux=creer_liste();
	element aux;
	aux=ite_begin(l);
	while(!ite_isEnd(l)){
		laux=ajouter_elem(laux,aux);
		aux=ite_next(l);
	}
	return laux;
}

/* --------------------- */
/* ----- ITERATEUR ----- */
/* --------------------- */

element ite_begin(Liste l){
	l->it->cour=l->sent->suiv;
	return l->it->cour->elem;
}

int ite_isEnd(Liste l){
	return (l->it->cour==l->sent);
}

element ite_next(Liste l){
	l->it->cour=l->it->cour->suiv;
	return l->it->cour->elem;
}

/* --------------------- */

/* ----------------- */
/* ----- DEBUG ----- */
/* ----------------- */

void afficher_liste_pointeur(Liste l){
	printf("\nListe : %p\n-- sent : %p\n-- it : %p\n---- cour : %p\n",l,l->sent,l->it,l->it->cour);
	cellule * aux=l->sent->suiv;
	while(aux!=l->sent){
		printf("-- cellule : %p -- element : %p\n",aux,aux->elem);
		aux=aux->suiv;
	}
}

/* ----------------- */
