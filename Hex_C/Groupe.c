#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Groupe.h"
#include "Plateau.h"

void init_groupe(){
	Liste_Groupe[0]=creer_liste();
	Liste_Groupe[1]=creer_liste();
}

void free_groupe(){
	Liste temp;
	for(int i=0;i<1;++i){
		temp=ite_begin(Liste_Groupe[i]);
		while(!ite_isEnd(Liste_Groupe[i])){
			supprimer_elem(Liste_Groupe[i],temp);
			free_liste(temp,1);
			temp=ite_next(Liste_Groupe[i]);
		}
	}
}

int get_groupe_value(int * e[], int ind){
	if(e!=NULL)
		return (*e)[ind];
	return -1;
}

void ajouter_elem_groupe(int x, int y, Liste l){
	int ** e;
	e=(int**)malloc(sizeof(int*));
	assert(e!=NULL);
	(*e)=(int*)malloc(sizeof(int)*2);
	assert((*e)!=NULL);
	(*e)[0]=x;
	(*e)[1]=y;
	ajouter_elem(l,e);
}

void free_elem_groupe(int ** e){
	free(*e);
	(*e)=NULL;
	free(e);
	e=NULL;
}

Liste copier_groupe(Liste l){
	Liste laux=creer_liste();
	Liste ltemp;
	Liste aux;
	aux=ite_begin(l);
	while(!ite_isEnd(l)){
		ltemp=copier_liste(aux);
		laux=ajouter_elem(laux,ltemp);
		aux=ite_next(l);
	}
	return laux;
}

Liste copier_vrai_groupe(int v){
	Liste laux=creer_liste();
	Liste l=Liste_Groupe[v];
	Liste ltemp;
	Sommet aux;
	aux=ite_begin(l);
	while(!ite_isEnd(l)){
		ltemp=copier_liste(get_sommet_lcase(aux));
		laux=ajouter_elem(laux,ltemp);
		aux=ite_next(l);
	}
	return laux;
}

void free_liste_groupe(Liste l){
	Liste ltemp2, ltemp=ite_begin(l);
	while(!ite_isEnd(l)){
		ltemp2=ltemp;
		free_liste(ltemp2,0);
		ltemp=ite_next(l);
	}
	free_liste(l,0);
}


/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_vrai_groupe(int v){
	printf("\nGroupe J%d\n",v);
	v--;
	//cel_gr * aux;
	Sommet aux;
	aux=ite_begin(Liste_Groupe[v]);
	while(!ite_isEnd(Liste_Groupe[v])){
		afficher_liste_groupe(get_sommet_lcase(aux));
		aux=ite_next(Liste_Groupe[v]);
	}
}

void afficher_liste_groupe(Liste l){
	element e=ite_begin(l);
	while(!ite_isEnd(l)){
		printf("[%d,%d] ",get_groupe_value(e,0),get_groupe_value(e,1));
		e=ite_next(l);
	}
	printf("\n");
}

void afficher_groupe2(Liste l){
	printf("\nListe l\n");
	Liste aux;
	aux=ite_begin(l);
	while(!ite_isEnd(l)){
		afficher_liste_groupe(aux);
		aux=ite_next(l);
	}
}

void afficher_groupe3(Liste l){
	printf("\nListe l\n");
	//cel_gr * aux;
	Sommet aux;
	aux=ite_begin(l);
	while(!ite_isEnd(l)){
		afficher_liste_groupe(get_sommet_lcase(aux));
		aux=ite_next(l);
	}
}

/* --------------------- */
