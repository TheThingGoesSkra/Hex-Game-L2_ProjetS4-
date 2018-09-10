#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Plateau.h"
#include "Groupe.h"
#include "Minimax.h"
#include "Pont.h"
#include "Const.h"

typedef struct plat_cel {
	int val;
	Sommet som; //Sommet correspondant dans le graphe réduit
}cellule;

typedef struct hexplat{
	int taille;
	cellule ** tab; //Tableau à deux dimensions dynamique
	int Victory;
	IA_info IA_info;
	Historique Hist;
}plat_int;

typedef struct hexhist {
	int * tab[3];
	int taille;
}hist_int;

void init_plateau(int n){
	Hex_Plat=(Plateau)malloc(sizeof(plat_int));
	assert(Hex_Plat!=NULL);
	Hex_Plat->tab=(cellule**)malloc(sizeof(cellule*)*n);
	assert(Hex_Plat->tab!=NULL);
	for(int i=0;i<n;++i){
		Hex_Plat->tab[i]=(cellule*)malloc(sizeof(cellule)*n);
		assert(Hex_Plat->tab[i]!=NULL);
	}
	Hex_Plat->taille=n;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j){
			Hex_Plat->tab[i][j].val=0;
			Hex_Plat->tab[i][j].som=creer_sommet(i,j);
			init_voisin(i,j);
		}
	creer_bord();
	// Initialisation de la victoire
	Hex_Plat->Victory=0;
	// Init IA
	Hex_Plat->IA_info=NULL;
	init_ia(0,0);
	// Initialisation de l'historique des coups (pour la sauvegarde)
	Hex_Plat->Hist=(Historique)malloc(sizeof(hist_int));
	Hex_Plat->Hist->tab[0]=NULL;
	Hex_Plat->Hist->tab[1]=NULL;
	Hex_Plat->Hist->tab[2]=NULL;
	Hex_Plat->Hist->taille=0;
	// Creation des listes de groupe de chaque joueur;
	init_groupe();
}

void free_plateau(){
	if(Hex_Plat->Hist->tab[0]!=NULL)
		for(int i=0;i<3;++i){
			free(Hex_Plat->Hist->tab[i]);
			Hex_Plat->Hist->tab[i]=NULL;
		}
	free(Hex_Plat->Hist);
	Hex_Plat->Hist=NULL;
	/*for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			free_sommet(get_plat_bord(i,j));*/
	for(int i=0;i<Hex_Plat->taille;++i){
		for(int j=0;j<Hex_Plat->taille;++j)
			if(Hex_Plat->tab[i][j].som!=NULL)
				free_sommet(Hex_Plat->tab[i][j].som);
		free(Hex_Plat->tab[i]);
		Hex_Plat->tab[i]=NULL;
	}
	free_groupe();
	free_pont();
	free(Hex_Plat->tab);
	Hex_Plat->tab=NULL;
	free(Hex_Plat);
	Hex_Plat=NULL;
}

void ajouter_hist_coup(int x, int y, int j){
	Hex_Plat->Hist->taille++;
	for(int i=0;i<3;++i){
		Hex_Plat->Hist->tab[i]=(int*)realloc(Hex_Plat->Hist->tab[i],sizeof(int)*Hex_Plat->Hist->taille);
		assert(Hex_Plat->Hist->tab[i]!=NULL);
	}
	Hex_Plat->Hist->tab[0][Hex_Plat->Hist->taille-1]=j;
	Hex_Plat->Hist->tab[1][Hex_Plat->Hist->taille-1]=x;
	Hex_Plat->Hist->tab[2][Hex_Plat->Hist->taille-1]=y;
}

void jouer_coup(int lig, int col, int value){
	if(get_case(lig,col)==0){
		set_case(lig,col,value);
		set_sommet_value(get_case_sommet(lig,col),value);
		if(value>=1 && value<=2){
			gerer_sommet_voisin(lig,col,value);

			Creer_Pont(get_case_sommet(lig,col),value);
			Actualiser_Pontadv(lig,col,value);

			ajouter_hist_coup(lig,col,value);
			if(get_plat_IA()!=0){// && get_plat_IA()!=value){
				int temp=trouver_fils(Hex_MinMax,lig,col);
				if(temp==-1) 
					ajouter_minimax(lig,col,value);
				Hex_MinMax=deplacer_arbre(Hex_MinMax,temp);
			}
		}
	}
}

/* ----------------------- */
/* -- GETTER and SETTER -- */
/* ----------------------- */

int get_plat_taille(){
	return Hex_Plat->taille;
}

int get_plat_hist_taille(){
	return Hex_Plat->Hist->taille;
}

void set_case(int lig, int col, int value){
	Hex_Plat->tab[lig][col].val=value;
}

int get_case(int lig, int col){
	return Hex_Plat->tab[lig][col].val;
}

void set_case_sommet(int lig, int col, Sommet s){
	Hex_Plat->tab[lig][col].som=s;
}

Sommet get_case_sommet(int lig, int col){
	return Hex_Plat->tab[lig][col].som;
}

void set_victory(int value){
	Hex_Plat->Victory=value;
}

int get_victory(){
	return Hex_Plat->Victory;
}

int get_move(int joueur, int coup, int num){
	joueur--;
	coup++;
	if(num+joueur<0 || num+joueur>=Hex_Plat->Hist->taille) return -1;
	return Hex_Plat->Hist->tab[coup][num+joueur];
}

int get_lastmove(int joueur, int coup){
	coup++;
	if(joueur==Hex_Plat->Hist->tab[0][get_plat_hist_taille()-1])
		return Hex_Plat->Hist->tab[coup][get_plat_hist_taille()-1];
	return Hex_Plat->Hist->tab[coup][get_plat_hist_taille()-2];
}

Sommet get_plat_bord(int joueur, int bord){
	Sommet aux, temp;
	aux = (bord==0) ? get_case_sommet(0,0) : get_case_sommet(get_plat_taille()-1,get_plat_taille()-1);
	Liste lvoisin=get_sommet_lvoisin(aux);
	temp=ite_begin(lvoisin);
	while(!ite_isEnd(lvoisin) && get_sommet_value(temp)!=(joueur*-1))
		temp=ite_next(lvoisin);
	return temp;
}

int get_va_jouer(){
	int j=Hex_Plat->Hist->tab[0][Hex_Plat->Hist->taille-1];
	j=j%2+1;
	return j;
}

void set_IA_info(IA_info info){
	Hex_Plat->IA_info=info;
}

IA_info get_IA_info(){
	return Hex_Plat->IA_info;
}

/* ----------------------- */

int sauvegarde_plateau(char * nom){
	FILE * fichier=fopen(nom,"wt");
	char temp, coup;
	if(fichier!=NULL){
		fprintf(fichier,"\\hex\n\\dim %d\n\\IA %d %d\n\\board\n",Hex_Plat->taille,get_plat_IA(),get_IA_diff());
		for(int i=0;i<Hex_Plat->taille;++i){
			for(int j=0;j<Hex_Plat->taille;++j){	
				switch(get_case(i,j)){
					case 0: temp='.'; 
						break;
					case 1: temp='o';
						break;
					case 2: temp='*';
						break;
				}
				fprintf(fichier,"%c ",temp);
			}
			fprintf(fichier,"\n");
		}
		fprintf(fichier,"\\endboard\n\\game\n");
		for(int i=0;i<Hex_Plat->Hist->taille;++i){
			switch(Hex_Plat->Hist->tab[0][i]){
				case 1: coup='o';
					break;
				case 2: coup='*';
					break;
			}
			fprintf(fichier,"\\play %c %d %d\n",coup,Hex_Plat->Hist->tab[1][i],Hex_Plat->Hist->tab[2][i]);
		}
		fprintf(fichier,"\\endgame\n\\endhex");
	}else
		return 1;
	fclose(fichier);
	return 0;
}

int chargement_plateau(char * nom){
	char temp[10]="\0";
	char car;
	int j,x,y;
	FILE * fichier=fopen(nom,"rt");
	if(fichier!=NULL){
		/* \hex */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\hex")!=0) return 2;
		/* \dim */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\dim")!=0) return 3;
		fscanf(fichier,"%s",temp);
		if(atoi(temp)<=0 || atoi(temp)>TAILLE_MAX) return 4;
		init_plateau(atoi(temp));
		/* \IA */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\IA")!=0) return 14;
		fscanf(fichier,"%s",temp);
		if(atoi(temp)<0 || atoi(temp)>3) return 15;
		j=atoi(temp);
		fscanf(fichier,"%s",temp);
		if(atoi(temp)<0 || atoi(temp)>3) return 16;
		init_ia(j,atoi(temp));
		/* \board */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\board")!=0) return 5;			
		int tab[Hex_Plat->taille][Hex_Plat->taille];
		for(int i=0;i<Hex_Plat->taille;++i)
			for(int j=0;j<Hex_Plat->taille;++j){
				fscanf(fichier,"%s",temp);
				if(strcmp(temp,".")==0)
					tab[i][j]=0;
				else if(strcmp(temp,"o")==0)
					tab[i][j]=1;
				else if(strcmp(temp,"*")==0)
					tab[i][j]=2;
			}
		/* \endboard */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\endboard")!=0) return 6;
		/* \game */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\game")!=0) return 7;
		fscanf(fichier,"%s",temp);
		while(strcmp(temp,"\\endgame")!=0){
			if(strcmp(temp,"\\play")!=0) return 8;			
			fscanf(fichier,"%s",temp);
			if(strcmp(temp,"o")!=0 && strcmp(temp,"*")!=0) return 9;
			if(temp[0]=='o') j=1;
			else j=2;
			fscanf(fichier,"%d",&x);
			if(x<0 || x>=Hex_Plat->taille) return 10;
			fscanf(fichier,"%d",&y);
			if(y<0 || y>=Hex_Plat->taille) return 11;
			jouer_coup(x,y,j);
			fscanf(fichier,"%s",temp);
		}
		/* \endhex */
		fscanf(fichier,"%s",temp);
		if(strcmp(temp,"\\endhex")!=0) return 12;
		/* Verification du plateau */
		for(int i=0;i<Hex_Plat->taille;++i)
			for(int j=0;j<Hex_Plat->taille;++j)
				if(tab[i][j]!=Hex_Plat->tab[i][j].val) return 13;
	}else
		return 1;
	fclose(fichier);
	return 0;
}

/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_plateau(){
	char temp;
	int i, j;
	for(i=0;i<Hex_Plat->taille;++i)
		printf("W ");
	printf("W/B\n");
	for(i=0;i<Hex_Plat->taille;++i){
		for(j=0;j<=i;++j)
			printf(" ");
		printf("B ");
		for(j=0;j<Hex_Plat->taille;++j){
			switch(Hex_Plat->tab[i][j].val){
				case 1: temp='o';
					break;
				case 2: temp='*';
					break;
				default: temp='.';
					break;
			}
			printf("%c ",temp);
		}
		printf("B\n");
	}
	for(j=0;j<=Hex_Plat->taille;++j)
		printf(" ");
	printf("B/W ");
	for(i=0;i<Hex_Plat->taille;++i)
		printf("W ");
	printf("\n");
}

/* --------------------- */

int main_test(){
	int n=3;
	init_plateau(n);
	init_ia(0,0);
	
	/*jouer_coup(0,1,1);
	jouer_coup(1,2,2);
	jouer_coup(2,0,1);
	jouer_coup(2,1,2);
	jouer_coup(3,0,1);
	jouer_coup(0,3,2);
	jouer_coup(4,1,1);
	jouer_coup(4,4,2);
	jouer_coup(4,3,1);
	jouer_coup(4,2,2);
	jouer_coup(3,4,1);
	jouer_coup(2,4,2);
	jouer_coup(1,4,1);
	jouer_coup(3,3,2);
	afficher_plateau();
	Liste l[2];
	l[0]=copier_vrai_groupe(0);
	l[1]=copier_vrai_groupe(1);
	printf("\n%d\n",minimax_fonction_evaluation(l,2));
	afficher_plateau();*/
	
	/*Sommet s=get_plat_bord(2,0);
	printf("%d\n",get_sommet_value(s));*/
	
	/*Liste l[2];
	int coup[3];
	coup[2]=1;
	for(int i=0;i<n*n;++i){
		getchar();
		l[0]=copier_vrai_groupe(0);
		l[1]=copier_vrai_groupe(1);
		recherche_coup(coup,1,l);
		jouer_coup(coup[0],coup[1],coup[2]);
		afficher_tout_voisin();
		printf("%d\n",get_victory());
		afficher_plateau();
		free_liste_groupe(l[0]);
		free_liste_groupe(l[1]);
	}*/

	/*set_plat_IA(2);
	init_minimax();

	jouer_coup(1,0,1);
	afficher_plateau();

	jouer_ia_minimax(get_plat_IA());
	afficher_minimax();
	afficher_plateau();*/

	//jouer_ia_minimax(get_plat_IA());
	//afficher_plateau();
	//jouer_coup(0,0,2);
	//afficher_plateau();

	/*int * e[2]={0,2};
	Liste l=creer_liste();
	ajouter_elem(l,e);
	int * f[2]={5,2};
	ajouter_elem(l,f);
	ajouter_elem(l,e);
	printf("%d\n",get_liste_taille(l));
	afficher_liste_groupe(l);*/

	/*jouer_coup(1,2,1);
	jouer_coup(0,0,2);
	jouer_coup(0,1,2);
	jouer_coup(0,2,2);
	jouer_coup(0,3,2);
	afficher_plateau();
	afficher_tout_voisin();
	printf("\n");
	afficher_voisin(0,2);
	afficher_voisin(0,3);
	afficher_voisin(0,4);
	afficher_voisin(1,0);
	afficher_voisin(1,2);
	afficher_voisin(1,3);

	printf("\n");

	jouer_coup(2,3,2);
	jouer_coup(3,3,2);
	jouer_coup(4,3,2);
	jouer_coup(4,4,2);
	afficher_plateau();
	afficher_tout_voisin();

	jouer_coup(1,3,2);
	jouer_coup(4,0,1);
	jouer_coup(4,1,1);
	afficher_plateau();
	afficher_tout_voisin();

	afficher_groupe(1);
	afficher_groupe(2);*/

	/*Liste l[2];
	l[0]=copier_vrai_groupe(0);
	l[1]=copier_vrai_groupe(1);
	int coup[3];
	recherche_coup(coup,1,l);
	printf("\n[%d,%d,%d]\n",coup[0],coup[1],coup[2]);*/
	
	// Liste et Groupe

	/*jouer_coup(0,0,1);
	jouer_coup(1,1,1);
	jouer_coup(1,0,2);	
	afficher_plateau();
	Liste l=copier_vrai_groupe(0);
	afficher_groupe2(l);*/	

	/*char temp;
	int x,y,v;
	do{
		afficher_plateau();
		printf("\n-:");
		scanf("%c",&temp);
		if(temp!='q'){
			printf("_");
			scanf("%d",&x);
			scanf("%d",&y);
			scanf("%d",&v);
			jouer_coup(x,y,v);
			afficher_voisin(x,y);
		}
	}while(temp!='q' && Hex_Plart->Victory==0);*/

	switch(Hex_Plat->Victory){
		case EMPTY:
			printf("Empty\n");
			break;
		case WHITE:
			printf("White\n");
			break;
		case BLACK:
			printf("Black\n");
			break;
	}

	/*sauvegarde_plateau("test.txt");
	init_plateau(2);
	afficher_plateau();
	printf("\n--%d--\n",chargement_plateau("/home/matthieu/Documents/Licence2/S4/ProjetS4/save.txt"));
	afficher_plateau();
	afficher_voisin(0,0);
	afficher_voisin(0,1);
	afficher_voisin(0,2);
	afficher_voisin(0,3);
	afficher_voisin(1,1);*/
	
	free_plateau();
	
	return 1;
}

int main(){
	int debug=0;

	if(debug)
		main_test();
	else{
		init_plateau(17);	
		init_ia(1,1);

		int tour=0;
		int x,y;
		while(get_victory()==EMPTY){
			printf("\n");
			//afficher_minimax();
			afficher_plateau();	
			if(get_plat_IA()==tour+1){
				jouer_ia(tour+1);
			}
			else{
				do{
					scanf("%d",&x);
					scanf("%d",&y);
				}while(get_case(x,y)!=0);
				jouer_coup(x,y,tour+1);
			}
			tour=(tour+1)%2;
		}
		afficher_plateau();
		printf("\n");
		switch(get_victory()){
			case EMPTY:
				printf("Empty\n");
				break;
			case WHITE:
				printf("White\n");
				break;
			case BLACK:
				printf("Black\n");
				break;
		}
	}
	//free_plateau();
	return 0;
}
