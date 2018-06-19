/* 
Module pensé par Tom Bloch, Bence Lovas et Matthieu Pont
réalisé par Matthieu Pont
Ce module gère les groupes de chaque joueur.
*/

#ifndef GROUPE_h
#define GROUPE_h

#include "Liste.h"

Liste Liste_Groupe[2];



/* Initialise la liste des groupes */
void init_groupe();

/* Libère de la mémoire les listes des groupes */
void free_groupe();

/* Retourne l'indice 0 ou 1 d'un int[2] (utile lorsque nous manipulons des void *) */ 
int get_groupe_value(int * e[], int ind);

/* Alloue une cellule de groupe de coordonnes [x][y] et l'ajoute dans la liste l */
void ajouter_elem_groupe(int x, int y, Liste l);

/* Libère de la mémoire une cellule de groupe */
void free_elem_groupe(int ** e);

/* Copie une liste de liste de int[2] dans une autre liste et la retourne */
Liste copier_groupe(Liste l);

/* Copie la liste des groupes de int[2] dans une autre liste et la retourne */
Liste copier_vrai_groupe(int v);

/* Libère de la mémoire une liste de groupe */
void free_liste_groupe(Liste l);

/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_vrai_groupe(int v);

void afficher_liste_groupe(Liste l);

void afficher_groupe2(Liste l);

void afficher_groupe3(Liste l);

/* --------------------- */

#endif
