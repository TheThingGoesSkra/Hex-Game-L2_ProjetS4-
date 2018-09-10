#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Liste.h"
#include "Graphe.h"
#include "Groupe.h"
#include "Pont.h"
#include "Plateau.h"
#include "IA.h"

typedef struct etcel_pont{
    Sommet g1;
    Sommet g2;
    int nb_cases;
    Liste cases;
}cel_pont;

void init_pont(){
  Liste_Pont[0]=creer_liste();
  Liste_Pont[1]=creer_liste();
}

void free_pont(){
	Liste temp;
	for(int i=0;i<1;++i){
		temp=ite_begin(Liste_Pont[i]);
		while(!ite_isEnd(Liste_Pont[i])){
			supprimer_elem(Liste_Pont[i],temp);
			free_liste(temp,1);
			temp=ite_next(Liste_Pont[i]);
		}
	}
}

Pont Creer_Cel_Pont(Sommet S1, Sommet S2,int nbCase, Liste Coup){
Pont c;
c=(Pont)malloc(sizeof(cel_pont));
assert(c!=NULL);
c->g1 = S1;
c->g2 = S2;
c->nb_cases= nbCase;
c->cases= Coup;
return (c) ;}

void Free_Cel_Pont(Pont c) {
     free(c->cases);
     c->cases = NULL ;
     free(c);
     c = NULL ;
}

void Supprimer_Pont2Sommets(Sommet S1,Sommet S2, int i){
Pont c = ite_begin(Liste_Pont[i-1]);
while(!ite_isEnd(Liste_Pont[i-1])){
    if(((c->g1==S1) && (c->g2==S2)) || ((c->g1==S2) && (c->g2==S1))){
    supprimer_elem(Liste_Pont[i-1],c);
    Free_Cel_Pont(c);}
c = ite_next(Liste_Pont[i-1]) ;
}}

void Supprimer_Pont(Pont c, int i ){
     supprimer_elem(Liste_Pont[i-1],c);
     Free_Cel_Pont(c);
}

void Calculer_Pont_Base(Sommet S, Sommet S2, int j){
    int tampon=0;
    int tampon4=0;
    Liste cp=creer_liste();
    Sommet Sv=ite_begin(get_sommet_lvoisin(S));
    while (!ite_isEnd(get_sommet_lvoisin(S)) && tampon4==0){
        int tampon2=0;
        if(Sv==S2){
            tampon4++;
        }
        if (get_sommet_value(Sv)==0){
            Sommet Sv2=ite_begin(get_sommet_lvoisin(S2));
            while (!ite_isEnd(get_sommet_lvoisin(S2)) && tampon2!=1){
                if (Sv==Sv2){
                    tampon++;
                    int **e=ite_begin(get_sommet_lcase(Sv));
                    ajouter_elem(cp, e);
                    tampon2++;
                }
                Sv2=ite_next(get_sommet_lvoisin(S2));
            }
        }
        Sv=ite_next(get_sommet_lvoisin(S));
    }
    if (tampon>0 && tampon4==0){
        Pont s3=ite_begin(Liste_Pont[j-1]);
        int tampon3 =0 ;
        while (!ite_isEnd(Liste_Pont[j-1]) && tampon3==0){
            if ((s3->g1==S && s3->g2==S2) || (s3->g1==S2 && s3->g2==S)){
                s3->nb_cases = tampon ;
                free_liste(s3->cases,0);
                s3->cases = cp ;
                tampon3 ++ ;
            }
            s3=ite_next(Liste_Pont[j-1]);
        }
        if (tampon3==0){
            Pont c=Creer_Cel_Pont(S,S2,tampon,cp);
            ajouter_elem(Liste_Pont[j-1], c);
        }
    }}

void Calculer_Pont(Sommet S, Sommet S2, int j){
  int tampon=0;
  Liste cp=creer_liste();
  Sommet Sv=ite_begin(get_sommet_lvoisin(S));
  while (!ite_isEnd(get_sommet_lvoisin(S))){
    int tampon2=0;
    if (get_sommet_value(Sv)==0){
      Sommet Sv2=ite_begin(get_sommet_lvoisin(S2));
      while (!ite_isEnd(get_sommet_lvoisin(S2)) && tampon2!=1){
        if (Sv==Sv2){
          tampon++;
          int **e=ite_begin(get_sommet_lcase(Sv));
          ajouter_elem(cp, e);
          tampon2++;
        }
        Sv2=ite_next(get_sommet_lvoisin(S2));
      }
    }
    Sv=ite_next(get_sommet_lvoisin(S));
  }
  if (tampon>0){
    Pont s3=ite_begin(Liste_Pont[j-1]);
    int tampon3 =0 ;
        while (!ite_isEnd(Liste_Pont[j-1]) && tampon3==0){
            if ((s3->g1==S && s3->g2==S2) || (s3->g1==S2 && s3->g2==S)){
                s3->nb_cases = tampon ;
                free_liste(s3->cases,0);
                s3->cases = cp ;
                tampon3 ++ ;
            }
            s3=ite_next(Liste_Pont[j-1]);
        }
            if (tampon3==0){
                Pont c=Creer_Cel_Pont(S,S2,tampon,cp);
                ajouter_elem(Liste_Pont[j-1], c);
            }
}}

void Creer_Pont(Sommet S, int j){
  Sommet S2,S3, aux, aux2;
 int bord1=0,bord2=0,tampon=0;
  S2=ite_begin(Liste_Groupe[j-1]);
                 while (!ite_isEnd(Liste_Groupe[j-1])){
                   if(S!=S2){
                    Calculer_Pont(S,S2,j);
                   }
                   S2=ite_next(Liste_Groupe[j-1]);
                 }
                 S2 = get_plat_bord(j,0);
                 S3 = get_plat_bord(j,1);
                 Calculer_Pont_Base(S,S2,j);
                 Calculer_Pont_Base(S,S3,j);
}

void Actualiser_Pont(Sommet S, Sommet S2, int x, int y, int j){
  Pont P;
  int tampon=0;
  int **e ;
  P=ite_begin(Liste_Pont[j-1]);
  while (!ite_isEnd(Liste_Pont[j-1]) && tampon!=1){
    if((P->g1==S && P->g2==S2) || (P->g2==S && P->g1==S2)){
      P->nb_cases--;
      if (P->nb_cases==0){
        Supprimer_Pont(P, j);
        tampon++;
      }else{
        e = ite_begin(P->cases);
        while(!ite_isEnd(P->cases) && tampon!=1){
          if((((*e)[0]==x) && ((*e)[1]==y))){

            supprimer_elem(P->cases, e);
            tampon++;
          }
          e=ite_next(P->cases);
        }
      }
    }
    P=ite_next(Liste_Pont[j-1]);
  }
}

void Actualiser_Pontadv(int x, int y, int j){
  Sommet S ;
  Sommet aux=NULL;
  Sommet aux2=NULL;
  Sommet aux3=NULL;
  for (int i=0; i<6; i++){
        S = NULL;
    switch (i){
    case 0:
        if ((y+1)<(get_plat_taille())){
      		S=get_case_sommet(x,y+1);
        }
  	else (S = get_plat_bord(2,1)) ;
      break;
    case 1:
        if ((y-1)>= 0)  {
      		S=get_case_sommet(x,y-1);
        }
    else (S = get_plat_bord(2,0)) ;
      break;
    case 2:
        if (((x+1)<(get_plat_taille())) && (y-1)>= 0 ){
      		S=get_case_sommet(x+1,y-1);
        }
        else ( S = NULL) ;

      break;
    case 3:
        if ((x+1)<(get_plat_taille()))  {
      		S=get_case_sommet(x+1,y);
         }
    else (S = get_plat_bord(1,1));
      break;
    case 4:
        if (((y+1)<(get_plat_taille())) && ((x-1)>= 0 )){
      		S=get_case_sommet(x-1,y+1);
	}
        else (S = NULL) ;
      break;
    case 5:
        if ((x-1)>=0)   {
      S=get_case_sommet(x-1,y);
                        }
    else (S = get_plat_bord(1,0)) ;
      break;
    }
            if (S != NULL){
    if (get_sommet_value(S)==j%2+1 || get_sommet_value(S)==(j%2+1)*-1){
      if (aux==NULL)
        aux=S;
      else if (aux2==NULL && S!=aux)
        aux2=S;
      else if (aux3==NULL && S!=aux && S!=aux2)
        aux3=S;
    }}
  }
  if (aux!=NULL && aux2!=NULL)
    Actualiser_Pont(aux, aux2, x, y, j%2+1);
  if (aux3!=NULL){
    Actualiser_Pont(aux,aux3, x, y, j%2+1);
    Actualiser_Pont(aux2,aux3, x, y, j%2+1);
  }
}



void Remplacer_Sommet_Pont(Sommet s1, Sommet s2, int j){
  Pont s3;
  s3=ite_begin(Liste_Pont[j-1]);
  while (!ite_isEnd(Liste_Pont[j-1])){
    if (s3->g1==s1)
      s3->g1=s2;
    if (s3->g2==s1)  //Afficher_Liste_Pont(1);
      s3->g2=s2;
   s3=ite_next(Liste_Pont[j-1]);
  }
}

void Afficher_Liste_Pont(int i){
printf("\nPont Joueur:%d\n",i);
  Pont P=ite_begin(Liste_Pont[i-1]);
  while (!ite_isEnd(Liste_Pont[i-1])){
    printf("%d cases : \n",P->nb_cases);
    int **e=ite_begin(P->cases);
    while(!ite_isEnd(P->cases)){
      printf("[ %d;",(*e)[0]);
      printf(" %d] \n",(*e)[1]);
      e=ite_next(P->cases);
    }
    P=ite_next(Liste_Pont[i-1]);
  }
}

int jouer_ia_pont (int ia){
//printf("\nia-pont\n");
     Pont adv ;
     Pont P ;
     int **e ;
    switch (ia){
    case 1:
         P = ite_begin(Liste_Pont[ia-1]) ;
         while (!ite_isEnd(Liste_Pont[ia-1])) {
            if(P->nb_cases == 1){
	         e=ite_begin(P->cases);
                jouer_coup((*e)[0],(*e)[1],ia) ;
                return (0);
            }
         P = ite_next(Liste_Pont[ia-1]);
        }
         adv = ite_begin(Liste_Pont[ia]);
        while(!ite_isEnd(Liste_Pont[ia])){
            if(adv->nb_cases == 1){
	         e=ite_begin(adv->cases);
                jouer_coup((*e)[0],(*e)[1],ia);
                return (0);
            }
            adv = ite_next(Liste_Pont[ia]);
        }
    break;
    case 2:
        P = ite_begin(Liste_Pont[ia-1]) ;
        while (!ite_isEnd(Liste_Pont[ia-1])) {
            if(P->nb_cases == 1){
	        e=ite_begin(P->cases);
                jouer_coup((*e)[0],(*e)[1],ia) ;
                return (0);
        }
        P = ite_next(Liste_Pont[ia-1]);
        }
        adv = ite_begin(Liste_Pont[ia-2]);
        while(!ite_isEnd(Liste_Pont[ia-2])){
            if(adv->nb_cases == 1){
		e=ite_begin(adv->cases);
                jouer_coup((*e)[0],(*e)[1],ia);
                return (0);
            }
            adv = ite_next(Liste_Pont[ia-2]);
        }
    break;
}
    return (1);
}

/*

Cette fonction effectue un test sur tous les sommets relié à une base.
Elle renvoie les coordonées du premier coup à joué si il éxiste une stratégie gagnante. 
//Retourne 0 ou 1 : Trouvé ou pas trouvé
int recherche_diagonale (int cp[3]){
    int aux=0;
    Pont p=ite_begin(Liste_Pont[cp[2]-1])
    while(!ite_isEnd(Liste_Pont[cp[2]-1])){
        if(get_pont_sommet(p,1)==get_plat_bord(cp[2],0){
            Liste S=create_liste();
            aux=recherche_pont_voisins(cp[2],get_pont_sommet(p,1),get_pont_sommet(p,2),1,S);
            if(aux>0)
                return 0;
        }
        if(get_pont_sommet(p,2)==get_plat_bord(cp[2],0)){
            Liste S=create_liste();
            aux=recherche_pont_voisins(cp[2],get_pont_sommet(p,1),get_pont_sommet(p,2),1,S);
            if(aux>0)
                return 0;
        }
        if(get_pont_sommet(p,1)==get_plat_bord(cp[2],1){
            Liste S=create_liste();
            aux=recherche_pont_voisins(cp[2],get_pont_sommet(p,1),get_pont_sommet(p,2),0,S);
            if(aux>0)
                return 0;
        }
        if(get_pont_sommet(p,2)==get_plat_bord(cp[2],1)){
            Liste S=create_liste();
            aux=recherche_pont_voisins(cp[2],get_pont_sommet(p,1),get_pont_sommet(p,2),0,S);
            if(aux>0)
                return 0;
        }
        p=ite_next(Liste_Pont[cp[2]-1]);
    }
    Sommet S1=ite_begin(Liste_Groupe[cp[2]-1]);
    while(!ite_isEnd(Liste_Groupe[cp[2]-1]){
        Sommet S2=ite_begin(get_sommet_lvoisin(S1);
        while(!ite_isEnd(get_sommet_lvoisin(S1)){
            if(S2==get_plat_bord(cp[2],1)){
                Liste S=create_liste();
                aux=recherche_pont_voisins(cp[2],S2,S1,0,S);
                if(aux>0)
                    return 0;
            }
            if(S2==get_plat_bord(cp[2],0)){
                Liste S=create_liste();
                aux=recherche_pont_voisins(cp[2],S2,S1,1,S);
                if(aux>0)
                    return 0;
            }
            S2=ite_next(get_sommet_lvoisin(S1));
        }
        S1=ite_next(Liste_Groupe[cp[2]-1]);
    }
    return 1;
}*/
/*

int liste_contient_sommet(Liste l , Sommet S){
    Sommet S1=ite_begin(l) ;
    while (!ite_isEnd(l)){
        if (S1==S){
            return 1;
        }
        S1=ite_next(l);
    }
    return 0;
}

Sommet get_pont_sommet(Pont p, int i){
    if ( i == 1){
        return (p->g1) ;
    }
    else
        return (p->g2);
    
}
                  
//Retourne 0 ou 1 : NULL ou trouvé.

Cette fonction parcours le "plateau", en partant d'une base et d'un sommet. Elle renvoie 1 si il éxiste un chemin de ponts jusqu'à l'autre base (Soit, une stratégie gagnante).
Nous n'avons pas eu le temps de terminer. Un problème semblait venir de l'itérateur (il est peut-être corrompus à chaque appel récursif). 
int recherche_pont_voisins (int j, Sommet S1, Sommet S2, int b, Liste S){
    int aux=0;
    ajouter_elem(S,S1);
    Sommet S3=ite_begin(get_sommet_lvoisin(S2));
    while(!ite_isEnd(get_sommet_lvoisin(S2))){
        if(S3==get_plat_bord(j,b)){
            return 1;
        }
        S3=ite_next(get_sommet_lvoisin(S2));
    }
    Pont p=ite_begin(Liste_Pont[j-1]);
    while(!ite_isEnd(Liste_Pont[j-1])){
        if((get_pont_sommet(p,1)==S2 && get_pont_sommet(p,2)==get_plat_bord(j,b)) || (get_pont_sommet(p,2)==S2 && get_pont_sommet(p,1)==get_plat_bord(j,b))){
                return 1;
        }
        if(get_pont_sommet(p,1)==S2 && liste_contient_sommet(S,get_pont_sommet(p,2))==0){
            aux=recherche_pont_voisins(j,S2,get_pont_sommet(p,2),b, S);
            if(aux==1){
                return 1;
            }
        }
        if(get_pont_sommet(p,2)==S2 && liste_contient_sommet(S,get_pont_sommet(p,1))==0){
            aux=recherche_pont_voisins(j,S2,get_pont_sommet(p,1),b, S);
            if(aux==1){
                return 1;
            }
        }
        p=ite_next(Liste_Pont[j-1]);
    }
    return 0;
}*/
