/* 
Module pensé par Tom Bloch, Bence Lovas et Matthieu Pont
réalisé par Matthieu Pont.
Ce module gère le plateau du jeu de Hex, c'est le module principal du jeu.
*/

#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "Graphe.h"
#include "IA.h"

#define TAILLE_MAX 22

typedef struct hexplat * Plateau;

typedef struct hexhist * Historique;

Plateau Hex_Plat;



/* Initialise le plateau de jeu, le graphe et tout le système nécéssaire au jeu de Hex */
void init_plateau(int n);

/* Libère de la mémoire le plateau */
void free_plateau();

/* Joue un coup et fait appel les fonctions necessaires au bon déroulement du jeu */
void jouer_coup(int lig, int col, int value);

/* ----------------------- */
/* -- GETTER and SETTER -- */
/* ----------------------- */

int get_plat_taille();

int get_plat_hist_taille();

void set_case(int lig, int col, int value);

int get_case(int lig, int col);

void set_case_sommet(int lig, int col, Sommet s);

Sommet get_case_sommet(int lig, int col);

void set_victory(int value);

int get_victory();

int get_move(int joueur, int coup, int num);

int get_lastmove(int joueur, int coup);

Sommet get_plat_bord(int joueur, int bord);

int get_va_jouer();

IA_info get_IA_info();

void set_IA_info(IA_info info);

/* ----------------------- */

int sauvegarde_plateau(char * nom);

int chargement_plateau(char * nom);

/* --------------------- */
/* ------- DEBUG ------- */
/* --------------------- */

void afficher_plateau();

/* --------------------- */

#endif
