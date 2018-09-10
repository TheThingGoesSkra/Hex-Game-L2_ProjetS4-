/* 
Module pensé par Tom Bloch et Matthieu Pont
réalisé par Tom Bloch et Matthieu Pont.
Ce module gère l'arbre du minimax de l'IA.
*/

#ifndef _MINMAX_h
#define _MINMAX_h

#include "Liste.h"

#define MINIMAX_TIME 5 //in second

typedef struct etarbre * Arbre;

Arbre Hex_MinMax;



/* Initialise l'arbre du minimax */
void init_minimax();

/* Creer un noeud de l'arbre */
Arbre creer_arbre(int x, int y, int j, int nbfils_max, Arbre pere);

/* Free un noeud */
void free_arbre(Arbre a);

/* Free un noeud et ses fils */
void free_arbre_fils(Arbre a);

/* Free tous les fils de a autre que le fils numero ind et deplace la racine de a vers son fils numero ind*/
Arbre deplacer_arbre(Arbre a, int ind);

/* Ajoute un fils a l'arbre a */
Arbre ajouter_fils(Arbre a);

/* Ajoute le fils b a l'arbre de a */
Arbre ajouter_fils2(Arbre a, Arbre b);

/* Retourne l'indice du fils de l'arbre a ayant pour coup [x][y][] */
int trouver_fils(Arbre a, int x, int y);

/* Ajoute un fils a l'arbre Hex_MinMax ayant pour coup[x][y][value] */
void ajouter_minimax(int x, int y, int value);

/* Verifie si le coup est present dans les listes (ie il a deja ete joue) */
int verifier_coup_minimax(Liste l[2], int coup[3]);

/* Joue le minimax jusqu'à que MINIMAX_TIME ou depth_max soit atteint*/
int jouer_ia_minimax(int depth_max);

/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_arbre(Arbre a);

void afficher_minimax();

void afficher_un_arbre(Arbre a);

void afficher_arbre_pointeur(Arbre a);

void afficher_matrice1(int n, double mat[n]);

void afficher_matrice2(int n, int m, double mat[n][m]);

/* --------------------- */

#endif 
