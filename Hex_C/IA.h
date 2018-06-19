/* 
Module pensé par Tom Bloch, Bence Lovas et Matthieu Pont
réalisé par Tom Bloch et Matthieu Pont.
Ce module gère l'IA du jeu.
*/

#ifndef _IA_h
#define _IA_h

typedef struct plat_IA * IA_info;

/* 
Initialise l'IA du jeu.
pour joueur : 0 : pas d'IA / 1 : IA est le joueur 1 / 2 : IA est le joueur 2 / 3 : IA vs IA (non implémenté)
pour diff : 
*/
void init_ia(int joueur, int diff);

/*
Recherche le n eme coup disponible pour le minimax ou pour le comportement par défaut de l'IA
*/
void recherche_coup(int coup[3], int n, Liste l[2], int xlast, int ylast, int verif);

/* Fait jouer l'IA */
int jouer_ia(int joueur);

/* ----------------------- */
/* -- GETTER and SETTER -- */
/* ----------------------- */

void set_plat_IA(int v);

int get_plat_IA();

int get_IA_diff();

int get_IA_lastmove(int i);

/* ----------------------- */

#endif
