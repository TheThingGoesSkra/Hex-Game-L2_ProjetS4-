#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "Minimax.h"
#include "Groupe.h"
#include "Plateau.h"
#include "IA.h"

int DEBUG_ITER; // pour compter le nombre de fils parcouru

typedef struct etarbre{
	int coup[3];
	int minimax;
	struct etarbre * pere;
	struct etarbre ** fils;
	int nbfils;
	int nbfils_max;
}cel_abr;



void init_minimax(){
	Hex_MinMax=creer_arbre(0,0,0,get_plat_taille()*get_plat_taille(),NULL);
}


Arbre creer_arbre(int x, int y, int j, int nbfils_max, Arbre pere){
	Arbre a=(Arbre)malloc(sizeof(cel_abr));
	assert(a!=NULL);
	a->coup[0]=x;
	a->coup[1]=y;
	a->coup[2]=j;
	a->minimax=0;
	a->pere=pere;
	a->fils=NULL;
	a->nbfils=0;
	a->nbfils_max=nbfils_max;
	return a;
}


void free_arbre(Arbre a){
	if(a->nbfils!=0){ 
		free(a->fils);
		a->fils=NULL;
	}
	free(a);
	a=NULL;
}


void free_arbre_fils(Arbre a){
	for(int i=0;i<a->nbfils;++i)
		free_arbre_fils(a->fils[i]);
	free_arbre(a);
}


Arbre deplacer_arbre(Arbre a, int ind){
	if(ind==-1) ind=a->nbfils-1;
	for(int i=0;i<a->nbfils;++i)
		if(i!=ind)
			free_arbre_fils(a->fils[i]);
	Arbre aux=a->fils[ind];
	free_arbre(a);
	return aux;	
}


Arbre ajouter_fils(Arbre a){
	if(a!=NULL){
		a->nbfils++;
		a->fils=(struct etarbre**)realloc(a->fils,sizeof(struct etarbre*)*a->nbfils);
		assert(a->fils!=NULL);
	}
	return a;
}


Arbre ajouter_fils2(Arbre a, Arbre b){
	if(a!=NULL){
		a->nbfils++;
		a->fils=(struct etarbre**)realloc(a->fils,sizeof(struct etarbre*)*a->nbfils);
		assert(a->fils!=NULL);
		a->fils[a->nbfils-1]=b;
		if(b!=NULL) b->pere=a;
	}
	return a;
}


int trouver_fils(Arbre a, int x, int y){
	for(int i=0;i<a->nbfils;++i)
		if(a->fils[i]->coup[0]==x && a->fils[i]->coup[1]==y)
			return i;
	return -1;
}


void ajouter_minimax(int x, int y, int value){
	Arbre a=creer_arbre(x,y,value,Hex_MinMax->nbfils_max-1,NULL);
	Hex_MinMax=ajouter_fils2(Hex_MinMax,a);
}


int touche(int x, int y, int x2, int y2){
	if(x==x2){
		if(y==y2+1) return 1;
		if(y==y2-1) return 1;
	}
	if(x==x2+1){
		if(y==y2) return 1;
		if(y==y2-1) return 1;
	}
	if(x==x2-1){
		if(y==y2+1) return 1;
		if(y==y2) return 1;
	}
	return 0;
}


int verifier_coup_minimax(Liste l[2], int coup[3]){
	int tampon, indice, cases[2];
	int ** temp;
	Liste groupe;
	tampon=0;
	indice=0;
	while (indice!=2 && tampon==0){
	    groupe=ite_begin(l[indice]);
	    while(!ite_isEnd(l[indice]) && tampon==0){
			temp=ite_begin(groupe);
			while(!ite_isEnd(groupe) && tampon==0){
				cases[0]=get_groupe_value(temp,0);
				cases[1]=get_groupe_value(temp,1);
				if (cases[0]==coup[0] && cases[1]==coup[1])
					tampon=1;
				temp=ite_next(groupe);
			}
			groupe=ite_next(l[indice]);
	    }
	    indice++;
	}
	return tampon;
}


/* ---------------------------------------------------------------------- */
/*
Fonction d'evaluation pour le jeu de Hex.
Réalisé par Matthieu Pont en 2017 (matthieu.pont@hotmail.fr)
Se base sur le principe de la machine analogique de Shannon pour le jeu de Hex (cf. rapport).
Pour symboliser l'impédance infini nous utilisons la valeur -1.
La liste l de minimax_fonction_evaluation est une liste de liste des groupes de chaque joueur qui contient toutes les cases jouées à cet instant.
L'objectif est de déterminer la valeur de la résistance totale pour deux reseaux de resistance (un pour chaque joueur).
Nous pourrons ensuite déterminer si le plateau est favorable plus pour tel ou tel joueur.
*/
Liste trouver_groupe(Liste l, int x, int y){
	int ** e;
	Liste laux=ite_begin(l);
	while(!ite_isEnd(l)){
		e=ite_begin(laux);
		while(!ite_isEnd(laux)){
			if((*e)[0]==x && (*e)[1]==y)
				return laux;
			e=ite_next(laux);
		}
		laux=ite_next(l);
	}
	return NULL;
}

int max(int a, int b){
	return (a>b) ? a : b ;
}

/* Se base sur la distance de Chebyshev d = max(delta(x),delta(y)) */
/*void trouver_case_groupe_loin(Liste l, int * x, int * y, Liste l_all[2]){
	int coord[2][6]= 	{{ 0,-1,-1, 0,+1,+1},
						{ -1, 0,+1,+1, 0,-1}};
	int ** e;
	int ** temp;
	int deltamax=0, dtemp, etat=0, coup[3];
	e=ite_begin(l);
	while(!ite_isEnd(l)){
		dtemp=max(fabs((*e)[0]-(*x)),fabs((*e)[1]-(*y)));
		if(dtemp>deltamax){
			deltamax=dtemp;
			(*x)=(*e)[0];
			(*y)=(*e)[1];
		}
		e=ite_next(l);
	}
	for(int i=0;i<6;++i){
		coup[0]=(*x)+coord[0][i];
		coup[1]=(*y)+coord[1][i];
		if(!verifier_coup_minimax(l_all,coup)){
			(*x)=coup[0];
			(*y)=coup[1];
		}
	}
}*/

int groupe_touche_bord(Liste l, int joueur){
	int ** e=ite_begin(l);
	while(!ite_isEnd(l)){
		if((*e)[joueur-1]==0)
			return 1;
		if((*e)[joueur-1]==get_plat_taille()-1)
			return 2;
		e=ite_next(l);
	}
	return 0;
}

double calcul_current_inout(double V1, double V2, int R, int inout){
	if(!inout)
		return (V2-V1)/(double)R;
	else
		return (V1-V2)/(double)R;
}

/* Algorithme qui tente de ne laisser aucun 0 sur la diagonale */
void gerer_matrice(int n, double mat[n][n], double matB[n]){
	int lig, done, cond_deb, cond_fin;
	double temp;
		for(int i=0;i<n-2;++i){
			if(mat[i][i]==0){
				lig=i+1;
				done=0;
				while(lig<n && !done){
					if(mat[lig][i]!=0){
						for(int j=0;j<n;++j){
							temp=mat[lig][j];
							mat[lig][j]=mat[i][j];
							mat[i][j]=temp;
						}
						temp=matB[lig];
						matB[lig]=matB[i];
						matB[i]=temp;
						done=1;
					}
					++lig;
				}
			}
		}
	if(mat[n-1][n-1]!=0){
		for(int i=n-1;i>0;--i){
			if(mat[i][i]==0){
				lig=i-1;
				done=0;
				while(lig>=0 && !done){
					if(mat[lig][i]!=0){
						for(int j=0;j<n;++j){
							temp=mat[lig][j];
							mat[lig][j]=mat[i][j];
							mat[i][j]=temp;
						}
						temp=matB[lig];
						matB[lig]=matB[i];
						matB[i]=temp;
						done=1;
					}
					--lig;
				}
			}
		}
	}
}

/* thanks to codewithc.com for their gauss elimination algorithm 
L'algorithme ne prend pas en compte un 0 sur la diagonale qui résulterait en une division par 0 */
int gauss(int mat_ordre, double A[mat_ordre][mat_ordre], double matB[mat_ordre], double x[mat_ordre])
{
	int i,j,k,n=mat_ordre;
	double c,sum=0.0;
	for(j=0; j<=n-1; j++) /* loop for the generation of upper triangular matrix*/
		for(i=0; i<=n-1; i++){
			if(i>j){
				c=A[i][j]/A[j][j];
				for(k=0; k<=n; k++){
					if(k!=n) A[i][k]=A[i][k]-c*A[j][k];
					else matB[i]=matB[i]-c*matB[j];
				}
			}
		}
	x[n-1]=matB[n-1]/A[n-1][n-1];
	/* this loop is for backward substitution*/
	for(i=n-2; i>=0; i--){
		sum=0;
		for(j=i; j<=n-1; j++)
			sum=sum+A[i][j]*x[j];
		x[i]=(matB[i]-sum)/A[i][i];
	}
	return(0);
}

void init_matrice1(int n, double mat[n], int value){
	for(int i=0;i<n;++i)
		mat[i]=value;
}

void init_matrice2(int n, int m, double mat[n][m], int value){
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			mat[i][j]=value;
}

/* ---------------------------------------------------------------------- */
int minimax_fonction_evaluation(Liste l[2], int joueur){
	int voltage=5, ground=0;
	double current_white=0, current_black=0, current_in, current_out, current_temp, V1, V2, resistance_white=-1, resistance_black=-1;
	int n=get_plat_taille();
	int coord1, coord2, coeff=1, coup[3], R, R2, f, bord, done, factor, node_law;
	int ** temp;
	int mat_taille, mat_multiplyBy2, mat_ind;
	int mat_corres[n][n];

	// Initialisation de la matrice de correspondance
	mat_ind=0;
	for(int i=0;i<get_plat_taille();++i)
		for(int j=0;j<get_plat_taille();++j){
			coup[0]=i;
			coup[1]=j;
			if(!verifier_coup_minimax(l,coup)) // Si la case est vide
				mat_corres[i][j]=mat_ind++;
			else
				mat_corres[i][j]=-1;
		}
	double matA[mat_ind][mat_ind];
	double matB[mat_ind];
	double mat_solve[mat_ind];
	int Resistor[n][n];
	int coord_white[4][3]= {{ 0,-1,-1},{-1, 0,+1},
							{ 0,+1,+1},{+1, 0,-1}};
	int coord_black[4][3]= {{-1, 0,+1},{ 0,-1,-1},
							{-1, 0,+1},{+1,+1, 0}};
	Liste lg;
	// Initialisation du reseau de resistance
	for(int i=0;i<get_plat_taille();++i)
		for(int j=0;j<get_plat_taille();++j)
			Resistor[i][j]=1;
	// Creation du reseau de resistance pour le joueur blanc 
	// (on utilise le meme tableau pour les deux joueurs il suffit d'inverser les 0 et -1)
	/*	On calcule la resistance propre a chaque noeud avec la formule suivante:
		R[i][j] = 1 si vide
			= 0 si occupé par un de nos pions
			= infini (-1) si occupé par un pion adverse
		On calcule la resistance entre deux noeuds de la facon suivante:
		R( i,j ; k,l ) = R[i][j] + R[k][l]
	*/
	int indice=0;
	Liste groupe;
	while (indice!=2){
		groupe=ite_begin(l[indice]);
		while(!ite_isEnd(l[indice])){
			temp=ite_begin(groupe);
			while(!ite_isEnd(groupe)){
				if(indice!=0)
					Resistor[(*temp)[0]][(*temp)[1]]=-1;
				else
					Resistor[(*temp)[0]][(*temp)[1]]=0;
				temp=ite_next(groupe);
			}
			groupe=ite_next(l[indice]);
		}
		++indice;
	}

	for(int circuit=0;circuit<2;++circuit){
		/*	Calcul de la matrice des equations lineaires liees aux lois de Kirchhoff (loi des noeuds)
			Une fois le systeme resolu nous connaitrons la tension a chaque noeud du reseau et nous
			pourrons determiner le courant sortant du circuit et donc la resistance totale.
		*/
		mat_taille=0;
		mat_multiplyBy2=0;
		init_matrice2(mat_ind,mat_ind,matA,0);
		init_matrice1(mat_ind,matB,0);
		init_matrice1(mat_ind,mat_solve,0);
		for(int i=0;i<get_plat_taille();++i) for(int j=0;j<get_plat_taille();++j){
			if(Resistor[i][j]==1){
				bord=0;
				for(int m=0;m<2;++m){
					for(int k=0;k<3;++k){
						if(circuit){
							coord1=i+coord_black[m*2][k];
							coord2=j+coord_black[m*2+1][k];
						}else{
							coord1=i+coord_white[m*2][k];
							coord2=j+coord_white[m*2+1][k];
						}
						if(coord1<0 || coord2<0){
							// Contact avec vcc
							if(!bord && ((!circuit && coord1<0) || (circuit && coord2<0))){
								matB[mat_taille]-=voltage*coeff;
								matA[mat_taille][mat_corres[i][j]]-=coeff;
								bord=1;
							}
						}else if(coord1>=get_plat_taille() || coord2>=get_plat_taille()){
							// Contact avec gnd
							if(!bord && ((!circuit && coord1>=get_plat_taille()) || (circuit && coord2>=get_plat_taille()))){
								matB[mat_taille]-=ground*coeff;
								matA[mat_taille][mat_corres[i][j]]-=coeff;
								bord=1;
							}
						}else if(Resistor[coord1][coord2]==0){
							// Resistance 1+0=1
							lg=trouver_groupe(l[circuit],coord1,coord2);
							if(lg!=NULL){
								if(groupe_touche_bord(lg,circuit+1)==1){ // contact vcc
										matB[mat_taille]-=voltage*coeff;
								}else if(groupe_touche_bord(lg,circuit+1)==2){ // contact gnd
										matB[mat_taille]-=ground*coeff;
								}else{
									//trouver_case_groupe_loin(lg,&coord1,&coord2,l);
									//matA[mat_taille][mat_corres[coord1][coord1]]+=coeff;
								}
								matA[mat_taille][mat_corres[i][j]]-=coeff;
							}
						}else if(Resistor[coord1][coord2]==1){
							// Resistance 1+1=2
							matA[mat_taille][mat_corres[coord1][coord2]]+=(float)(coeff)/2;
							matA[mat_taille][mat_corres[i][j]]-=(float)(coeff)/2;
							mat_multiplyBy2=1;
						}
					}
					coeff*=-1;
				}
				mat_taille++;
			}
		}
		if(mat_multiplyBy2)
			for(int i=0;i<mat_ind;++i){
				for(int j=0;j<mat_ind;++j)
					matA[i][j]*=2;
				matB[i]*=2;
			}
		gerer_matrice(mat_ind,matA,matB);
		/* Calcul des solutions des equations lineaires */
		gauss(mat_ind,matA,matB,mat_solve);
		/* Calcul du courant entrant et sortant dans chaque noeud 
		et deduction du courant sortant du circuit.
		*/
		indice=0;
		for(int i=0; i<get_plat_taille();++i) for(int j=0; j<get_plat_taille();++j)
			if(Resistor[i][j]==1){
				current_in=0;
				current_out=0;
				current_temp=0;
				V1=mat_solve[mat_corres[i][j]];
				bord=0;
				for(int m=0;m<2;m++){
					for(int k=0;k<3;++k){
						done=0;
						if(circuit){
							coord1=i+coord_black[m*2][k];
							coord2=j+coord_black[m*2+1][k];
						}else{
							coord1=i+coord_white[m*2][k];
							coord2=j+coord_white[m*2+1][k];
						}
						if(coord1<0 || coord2<0){
							// Contact avec vcc
							if(!bord && ((!circuit && coord1<0) || (circuit && coord2<0))){
								V2=voltage;
								bord=1;
								R2=0;
								done=1;
							}
						}else if(coord1>=get_plat_taille() || coord2>=get_plat_taille()){
							// Contact avec gnd
							if(!bord && ((!circuit && coord1>=get_plat_taille()) || (circuit && coord2>=get_plat_taille()))){
								V2=ground;
								bord=1;
								R2=0;
								done=1;
							}
						}else if(Resistor[coord1][coord2]==0){
							lg=trouver_groupe(l[circuit],coord1,coord2);
							if(lg!=NULL){
								if(groupe_touche_bord(lg,circuit+1)==1){ // contact vcc
										V2=voltage;
								}else if(groupe_touche_bord(lg,circuit+1)==2){ // contact gnd
										V2=ground;
								}else{
									//trouver_case_groupe_loin(lg,&coord1,&coord2,l);
									//V2=mat_solve[mat_corres[coord1][coord2]];
									V2=0;
								}
								R2=0;
								done=1;
							}
						}else if(Resistor[coord1][coord2]==1){
							V2=mat_solve[mat_corres[coord1][coord2]];
							R2=Resistor[coord1][coord2];
							done=1;
						}
						if(done){
							R=Resistor[i][j]+R2;
							current_temp=calcul_current_inout(V1,V2,R,m);
							if(!m)
								current_in+=current_temp;
							else
								current_out+=current_temp; // en réalite nous calculons -current_out
						}
					}
				}
				// Validation des calculs en verifiant la loi des noeuds
				node_law=0;
				if(current_in!=current_out*-1) {
					if(fabs(current_in)>=10) factor=(int)log10(fabs(current_in));
					else factor=1;
					if(fabs(current_in+current_out)>(0.00001*pow(10,factor))){ // On verifie l'arrondi
/*
						printf("\n ! La loi des noeuds n'est pas valide sur le noeud [%d,%d] ! \n",i,j);
						printf("factor=%d",factor);
						printf("\n[%d,%d]_in:%0.20f|out:%0.20f",i,j,current_in,current_out);
						printf("\n_%f_\n",fabs(current_in+current_out));
						getchar();
*/
					}else
						node_law=1;;
				}else
					node_law=1;;
				if(node_law){
					if(!circuit && fabs(current_in)>current_white) current_white=fabs(current_in);
					else if(circuit && fabs(current_in)>current_black) current_black=fabs(current_in);
				}
			}

		// Inversion du reseau de resistance pour le circuit du prochain joueur
		for(int i=0;i<get_plat_taille();++i)
			for(int j=0;j<get_plat_taille();++j)
				if(Resistor[i][j]==0) Resistor[i][j]=-1;
				else if(Resistor[i][j]==-1) Resistor[i][j]=0;	
	}
	// Calcul de la resistance totale des circuits
	if(current_black!=0) resistance_black=voltage/current_black;
	if(current_white!=0) resistance_white=voltage/current_white;
/*
	printf("\nRB=%f|current=%f",resistance_black,current_black);
	printf("\nRW=%f|current=%f",resistance_white,current_white);
*/
		
	// Calcul de la fonction d'evaluation
	if(resistance_black==-1 || resistance_white==-1 || resistance_black==resistance_white) f=0;
	else if(resistance_black<resistance_white){
			f = (joueur==1) ? -1 : 1;
	}else f = (joueur==1) ? 1 : -1;
	return f;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */


int calculer_minimax(Liste l, int j){
	int borne1=0;
	int borne2=0;
	int cases[2];
	element temp;
	temp=ite_begin(l);
	while(!ite_isEnd(l) && ((borne1+borne2)!=2)){
		cases[0]=get_groupe_value(temp,0);
		cases[1]=get_groupe_value(temp,1);
		if (cases[j-1]==(get_plat_taille()-1))
			borne1=1;
		else if (cases[j-1]==0)
			borne2=1;
		temp=ite_next(l);
	}
	if (borne1==1 && borne2==1)
		return j;
	else
		return 0;
}


int jouer_coup_minimax(int coup[3], Liste l){
	Liste laux, ltemp, lsave;
	element temp;
	int done=0, out=0;
	laux=ite_begin(l);
	while(!ite_isEnd(l)){
		out=0;
		temp=ite_begin(laux);
		while(!out && !ite_isEnd(laux)){
			if(touche(coup[0],coup[1],get_groupe_value(temp,0),get_groupe_value(temp,1))){
				if(!done){
					ajouter_elem_groupe(coup[0],coup[1],laux);
					ltemp=laux;
					done=1;
					out=1;
				}else{
					ltemp=merge_liste(ltemp,laux);
					supprimer_elem(l,laux);
					free_liste(laux,0);
					out=1;
				}
			}
			if(!out) temp=ite_next(laux);
		}
		laux=ite_next(l);
	}
	if(!done){
		ltemp=creer_liste();
		ajouter_elem_groupe(coup[0],coup[1],ltemp);
		l=ajouter_elem(l,ltemp);
	}
	return calculer_minimax(ltemp,coup[2]);		
}


Arbre creer_minimax(int num_fils, Arbre pere, int j, Liste lpere[2], clock_t debut, int depth_max){
DEBUG_ITER++;

	if(depth_max>0) 
		depth_max--;
	clock_t actuel;
	int i=0, cond, res, profondeur, xlast=0, ylast=0;
	Liste l[2];
	l[0]=copier_groupe(lpere[0]);
	l[1]=copier_groupe(lpere[1]);
	Arbre a;
	profondeur=get_plat_taille()*get_plat_taille()-pere->nbfils_max;
	if(pere->nbfils==num_fils+1){ // Si on a pas deja cree ce noeud
		a=creer_arbre(-1,-1,-1,pere->nbfils_max-1,pere);

		a->coup[2]=profondeur%2+1;
		if(a->pere->pere!=NULL && a->pere->pere!=Hex_MinMax){
			xlast=a->pere->pere->coup[0];
			ylast=a->pere->pere->coup[1];
		}

		recherche_coup(a->coup,num_fils+1,l,xlast,ylast,0);
	}else
		a=pere->fils[num_fils];

	res=jouer_coup_minimax(a->coup,l[a->coup[2]-1]);

	if(res!=0){
		a->minimax = (res==j) ? 1 : -1 ;
	}else{
		actuel=clock();
		if((actuel-debut)/CLOCKS_PER_SEC<MINIMAX_TIME){
			if(depth_max!=0){
					cond = (a->coup[2]==j) ? -1 : 1 ;
					while(a->minimax!=cond && a->nbfils<a->nbfils_max){
						a=ajouter_fils(a);
						a->fils[i]=creer_minimax(i,a,j,l,debut,depth_max);
						if(a->fils[i]!=NULL)
							a->minimax=a->fils[i]->minimax;
						++i;
					}
			}else
				a->minimax=minimax_fonction_evaluation(l,j);
		}
	}

	// On free le coup joué de ce noeud de l'arbre
	Liste ltemp=ite_begin(l[a->coup[2]-1]);
	int ** e, done=0;
	while(!ite_isEnd(l[a->coup[2]-1]) && !done){
		e=ite_begin(ltemp);
		while(!ite_isEnd(ltemp) && !done){
			if((*e)[0]==a->coup[0] && (*e)[1]==a->coup[1]){
				ltemp=supprimer_elem(ltemp,e);
				free_elem_groupe(e);
				done=1;
			}
			e=ite_next(ltemp);
		}
		ltemp=ite_next(l[a->coup[2]-1]);
	}
	free_liste_groupe(l[0]);
	free_liste_groupe(l[1]);
	return a;
}


int jouer_ia_minimax(int depth_max){
//printf("\nia-minimax\n");

	int i=-1;
	int j=get_plat_IA();
	Liste l[2];
	clock_t debut=clock();	

	l[0]=copier_vrai_groupe(0);
	l[1]=copier_vrai_groupe(1);
DEBUG_ITER=0;
	while(Hex_MinMax->minimax!=1 && Hex_MinMax->nbfils<Hex_MinMax->nbfils_max){
		++i;
		if(i>=Hex_MinMax->nbfils)
			Hex_MinMax=ajouter_fils(Hex_MinMax);
		Hex_MinMax->fils[i]=creer_minimax(i,Hex_MinMax,j,l,debut,depth_max);
		if(Hex_MinMax->fils[i]!=NULL)
			Hex_MinMax->minimax=Hex_MinMax->fils[i]->minimax;
	}
	free_liste_groupe(l[0]);
	free_liste_groupe(l[1]);
//printf("__%d__\n",DEBUG_ITER);
	if(Hex_MinMax->minimax!=1){
		//printf("|____|");
	}else{
		int coup[3], indice;
		indice=Hex_MinMax->nbfils-1;
		coup[0]=Hex_MinMax->fils[indice]->coup[0];
		coup[1]=Hex_MinMax->fils[indice]->coup[1];
		coup[2]=Hex_MinMax->fils[indice]->coup[2];
		jouer_coup(coup[0],coup[1],coup[2]);
		//Hex_MinMax=deplacer_arbre(Hex_MinMax,indice);
		return 1;
	}
	return 0;
}


/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_arbre(Arbre a){
	printf("\n------ARBRE------\n");
	//if(a->pere!=NULL);	
		//printf("Coup pere = [%d,%d,%d]",a->pere->coup[0],a->pere->coup[1],a->pere->coup[2]);
	printf("Coup       = [%d,%d,%d]\nMinimax    = %d\n",a->coup[0],a->coup[1],a->coup[2],a->minimax);
	printf("Nbfils     = %d\n",a->nbfils);	
	printf("Nbfils_max = %d\n",a->nbfils_max);
	printf("-----------------\n");
	for(int i=0;i<a->nbfils;++i){
		afficher_arbre(a->fils[i]);
	}
}

void afficher_minimax(){
	afficher_arbre(Hex_MinMax);
}

void afficher_un_arbre(Arbre a){
	printf("\n------1ARBRE------\n");
	//if(a->pere!=NULL);	
		//printf("Coup pere = [%d,%d,%d]",a->pere->coup[0],a->pere->coup[1],a->pere->coup[2]);
	printf("Coup      = [%d,%d,%d]\nMinimax = %d\n",a->coup[0],a->coup[1],a->coup[2],a->minimax);
	printf("Nbfils     = %d\n",a->nbfils);	
	printf("Nbfils_max = %d",a->nbfils_max);
	printf("\n__________________\n");
}

void afficher_arbre_pointeur(Arbre a){
	printf("\n------PARBRE------\n");
	printf("Arbre      = %p\n",a);
	printf("Coup       = %p\nMinimax    = %p\n",a->coup,&a->minimax);
	printf("Nbfils     = %p\n",&a->nbfils);	
	printf("Nbfils_max = %p",&a->nbfils_max);
	for(int i=0;i<a->nbfils;++i){
		printf("\nfils[%02d]  = %p",i,a->fils[i]);
	}
	printf("\n__________________\n");
}

void afficher_matrice1(int n, double mat[n]){
	printf("\nMat[%d]\n",n);
	for(int i=0;i<n;++i)
			printf("%f ",mat[i]);
}

void afficher_matrice2(int n, int m, double mat[n][m]){
	printf("\nMat[%d][%d]\n",n,m);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
			printf("%0.2f ",mat[i][j]);
		printf("\n");
	}
}

/* --------------------- */
