/* 
Module pensé par Tom Bloch, Bence Lovas et Matthieu Pont
réalisé par Matthieu Pont
Ce module gère le graphe réduit qui permet principalement de détecter la victoire d'un joueur
*/

#ifndef GRAPHE_H
#define GRAPHE_H

#include "Liste.h"

typedef struct hexsommet * Sommet;


/* Créer un sommet correspondant a la case [i][j] du plateau */
Sommet creer_sommet(int i, int j);

/* Initialise le lien entre des sommets voisins */
void init_voisin(int i, int j);

/* Créer les sommets représentant les bords et les lies au graphe réduit existant */
void creer_bord();

/* Libère de la mémoire le sommet */
void free_sommet(Sommet s);

/* ----------------------- */
/* -- GETTER and SETTER -- */
/* ----------------------- */

int get_sommet_value(Sommet s);

void set_sommet_value(Sommet s, int val);

Liste get_sommet_lcase(Sommet s);

Liste get_sommet_lvoisin(Sommet s);

/* ----------------------- */

/* Ajoute au sommet s le voisin s_add */
void ajouter_voisin(Sommet s, Sommet s_add);

/* Ajoute au sommet s le voisin s_add et inversement */
void lier_sommet(Sommet s1, Sommet s2);

/* Fonction principale gérant la fusion des sommets lorsque le coup [lig][col] du joueur value est joué */
void gerer_sommet_voisin(int lig, int col, int value);

/* ----------------- */
/* ----- DEBUG ----- */
/* ----------------- */

void afficher_voisin(int lig, int col);

void afficher_tout_voisin();

void afficher_liste_sommet(Liste l);

/* ----------------- */

#endif
