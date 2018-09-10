#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Groupe.h"
#include "Plateau.h"
#include "Minimax.h"
#include "Pont.h"

typedef struct plat_IA {
	int IA; 
	int diff;
	int last_move[2];
}ia_int;

void init_ia(int joueur, int diff){
	IA_info info;
	info=(IA_info)malloc(sizeof(ia_int));
	assert(info!=NULL);
	info->diff=diff;
	info->IA=joueur;
	set_IA_info(info);
	init_minimax();
	init_pont();
}

void coup_suivant1(int coup[3]){
	coup[1]++;
	if (coup[1]==get_plat_taille()){
		coup[0]++;
		coup[1]=0;
	}
}

void coup_suivant2(int coup[3], int * coeff, int * coord_to_change, int * iter, int * iter_max, int * fin){
//printf("\ncoup_suivant2\n");

	// Joue la case à partir du milieu jusqu'aux bords
	coup[(*coord_to_change)]+=(*coeff);
	(*iter)++;
	if((*iter_max)==get_plat_taille() && (*iter)==((*iter_max)-1)){
		(*fin)=1;
	}
	else if((*iter)>=(*iter_max)){
		(*coord_to_change)=((*coord_to_change)+1)%2;
		(*iter)=0;
		if((*coord_to_change)==1){
			(*coeff)*=-1;
			(*iter_max)++;
		}
	}
}

void coup_suivant3(int coup[3], int * etat){
	// Joue sur la diagonale haut-gauche -> bas-droite
	coup[0]++; //--;
	coup[1]++;
	if(coup[0]==get_plat_taille() || coup[1]==get_plat_taille()){
		coup[0]=0; //get_plat_taille()-1;
		coup[1]=0;
	}else if(coup[0]==get_plat_taille()/2 || coup[1]==get_plat_taille()/2){ //-1)
		coup[0]=get_plat_taille()/2;
		coup[1]=get_plat_taille()/2;
		(*etat)++;
	}
}

int recherche_pont_compare(int x, int y, int xoffset, int yoffset, int verif, Liste groupe[2]){
	if((x+xoffset)>=get_plat_taille() || (x+xoffset)<0 ||
	(y+yoffset)>=get_plat_taille() || (y+yoffset)<0 )
		return 1;
	else if(verif)
		return (get_case(x+xoffset,y+yoffset)==0);
	else{
		int coup[3]={x+xoffset,y+yoffset,0};
		return !verifier_coup_minimax(groupe,coup);
	}
}

int recherche_pont(int * x, int * y, int cas, int modify, int verif, Liste groupe[2]){
	int res, res1, res2, res3;
	int tab[2][6]={{ -1,-2,-1,+1,+2,+1},
			{-1,+1,+2,+1,-1,-2}};
	int tab_cases[4][6]=	{{-1,-1, 0,+1,+1, 0},
				{  0, 0,+1, 0, 0,-1},
				{  0,-1,-1, 0,+1,+1},
				{ -1,+1,+1,+1,-1,-1}};
	res1=recherche_pont_compare(*x,*y,tab[0][cas],tab[1][cas],verif,groupe);
	res2=recherche_pont_compare(*x,*y,tab_cases[0][cas],tab_cases[1][cas],verif,groupe);
	res3=recherche_pont_compare(*x,*y,tab_cases[2][cas],tab_cases[3][cas],verif,groupe);
	res = (res1 && res2 && res3);
	if(res && modify){
		(*x)+=tab[0][cas];
		(*y)+=tab[1][cas];
	}
	return res;
}

int isLink_bord(int joueur, int bord){
	Sommet s=get_plat_bord(joueur,bord);
	Liste l=get_sommet_lvoisin(s);
	Sommet aux=ite_begin(l);
	while(!ite_isEnd(l) && get_sommet_value(aux)!=joueur)
		aux=ite_next(l);
	return !ite_isEnd(l);
}

void coup_suivant4(int coup[3], int * etat, int joueur, Liste groupe[2], int * mode, int * xlast, int * ylast,int verif){
	int x=*xlast, y=*ylast, i, j, temp;
	int change=1;
	int oldx, oldy;
//printf("\n-%d-%d-_%d,%d",*bord,*etat,*xlast,*ylast);
	if(get_liste_taille(groupe[joueur-1])==0){ // Si on a pas encore joué
		coup[joueur%2]--;
	}else switch((*etat)){
		case 0: // Chercher a creer des ponts vers les bords
			/*if((x>get_plat_taille()/2 && joueur==1) || (y>get_plat_taille()/2 && joueur==2))
				(*mode)=1;*/
			if(isLink_bord(joueur,0)){
				(*mode)=1;
				coup[0]=get_plat_taille()/2;
				coup[1]=get_plat_taille()/2;
			}else{
				i=0;
				j=1;
				while(i<get_plat_taille() && !(*mode)){
					if(joueur==1) temp=1;
					else temp=4;
					if(get_case(j,i)==joueur)
						if(recherche_pont(&j,&i,temp,0,1,groupe)){
							(*mode)=1;
							coup[0]=get_plat_taille()/2;
							coup[1]=get_plat_taille()/2;
						}
					++i;
				}
			}
			//do{
			oldx=x; 
			oldy=y;
			// On recherche des ponts
			if(joueur==1){
				if((*mode)==0){
					if(!recherche_pont(&x,&y,1,change,verif,groupe))
						if(!recherche_pont(&x,&y,0,change,verif,groupe))
							recherche_pont(&x,&y,2,change,verif,groupe);
				}else{
					if(!recherche_pont(&x,&y,4,change,verif,groupe))
						if(!recherche_pont(&x,&y,3,change,verif,groupe))
							recherche_pont(&x,&y,5,change,verif,groupe);
				}
			}else{
				if((*mode)==0){
					if(!recherche_pont(&x,&y,0,change,verif,groupe))
						recherche_pont(&x,&y,5,change,verif,groupe);
				}else{
					if(!recherche_pont(&x,&y,2,change,verif,groupe))
						recherche_pont(&x,&y,3,change,verif,groupe);
				}
			}
//printf("_%d,%d_\n",x,y);
//getchar();
			//if(change==0)
			//	change=-1;
			if(x!=oldx || y!=oldy){
				if(x<0 || y<0 || x>=get_plat_taille() || y>=get_plat_taille()){
					if((*mode)==0){
						(*mode)=1;
						if(get_plat_hist_taille()!=0){
							coup[0]=get_move(joueur,0,0);
							coup[1]=get_move(joueur,1,0);
						}else
							coup[0]=-1;
						if(coup[0]==-1 || coup[1]==-1){
							coup[0]=get_plat_taille()/2;
							coup[1]=get_plat_taille()/2;
						}
//printf("|%d_%d|\n",coup[0],coup[1]);
						*xlast=coup[0];
						*ylast=coup[1];
					}else{
						(*etat)=1;
						coup[0]=get_plat_taille()/2;
						coup[1]=get_plat_taille()/2;
					}
				}else{
				//if(change){
					//change=0;
					coup[0]=x;
					coup[1]=y;
				//}
				}
			}else 
				(*etat)=1;
			if((*etat)==1) (*mode)=0;
			//}while(change!=-1);
			break;
		case 1:
			/*if(joueur==1){
				if((*mode)==0){
					coup[0]++;
					(*mode)=1;
				}
				else{ 
					coup[1]--;
					(*mode)=3;
				}
			}else{
				switch(*mode){
					case 0:
						coup[1]++;
						(*mode)++;
						break;
					case 1:
						coup[0]--;
						(*mode)++;
						break;
					case 2:
						coup[0]+=2;
						coup[1]--;
						(*mode)++;
						break;
				}
			}
			if((*mode)==3)*/ (*etat)=2;
			break;
	}
}

void recherche_coup(int coup[3], int n, Liste l[2], int xlast, int ylast, int verif){
	int num=0;
	Liste groupe;
	int cases[2], tampon, indice;
	int coeff=-1, coord_to_change=1, iter=0, iter_max=1, fin=0;
	int etat=0, mode=0;
	element temp;
	int joueur=coup[2];

	// coup_suivant 1
	//coup[0]=0;
	//coup[1]=0;
	// coup_suivant 2 et 3 et 4
	coup[0]=get_plat_taille()/2;
	coup[1]=get_plat_taille()/2;
	// coup_suivant 4
	//if(get_plat_taille()%2==0) coup[0]--;

	while (!fin && (num!=n)) {
		if(verif==0) // Minimax
			tampon=verifier_coup_minimax(l,coup);
		else
			tampon=(get_case(coup[0],coup[1])!=0);
		if (tampon==0)
			num++;
		if(num!=n){
			//coup_suivant1(coup);
			//coup_suivant3(coup,&etat);
			if(verif==0) // Si minimax
				coup_suivant2(coup,&coeff,&coord_to_change,&iter,&iter_max,&fin);
			else{ //Si IA_defaut
				if(etat<2) coup_suivant4(coup,&etat,joueur,l,&mode,&xlast,&ylast,verif);
				else /*if(etat==2 && jouer_ia_minimax(2)==0) etat=3;
				if(etat==3)*/ coup_suivant2(coup,&coeff,&coord_to_change,&iter,&iter_max,&fin);
			}
		}
	}
//printf("etat:%d__mode:%d\n",etat,mode);
}

int jouer_ia_defaut(){
//printf("\nia-defaut\n");

	Liste l[2];
	int coup[3];
	l[0]=copier_vrai_groupe(0);
	l[1]=copier_vrai_groupe(1);
	coup[2]=get_plat_IA();
	recherche_coup(coup,1,l,get_IA_lastmove(0),get_IA_lastmove(1),1);
	jouer_coup(coup[0],coup[1],coup[2]);
	IA_info info=get_IA_info();
	info->last_move[0]=coup[0];
	info->last_move[1]=coup[1];
	free_liste_groupe(l[0]);
	free_liste_groupe(l[1]);
	return 0;
}

int jouer_ia(int joueur){
	if(jouer_ia_minimax(7)==0)
		if(jouer_ia_pont(joueur)!=0)
			//if(jouer_ia_minimax(3)==0)
				jouer_ia_defaut();
	return get_lastmove(joueur,0)*get_plat_taille()+get_lastmove(joueur,1);
}

/* ----------------------- */
/* -- GETTER and SETTER -- */
/* ----------------------- */

void set_plat_IA(int v){
	IA_info info=get_IA_info();
	info->IA=v;
}

int get_plat_IA(){
	IA_info info=get_IA_info();
	return info->IA;
}

int get_IA_diff(){
	IA_info info=get_IA_info();
	return info->diff;
}

int get_IA_lastmove(int i){
	IA_info info=get_IA_info();
	return info->last_move[i];
}

/* ----------------------- */
