/* 
Module pensé par Tom Bloch, Bence Lovas et Matthieu Pont
réalisé par Tom Bloch et Bence Lovas.
Ce module gère la gestion des ponts.
*/

#ifndef pont_h
#define pont_h
#include "Liste.h"
#include "Graphe.h"

typedef struct etcel_pont* Pont;

Liste Liste_Pont[2];



void init_pont();

void free_pont();

Pont Creer_Cel_Pont(Sommet S, Sommet S2, int nbCase, Liste Coup);

void Free_Cel_Pont(Pont c);

void Supprimer_Pont2Sommets(Sommet S, Sommet S2, int i);

void Supprimer_Pont(Pont c, int i);

void Calculer_Pont(Sommet S, Sommet S2, int j);

void Creer_Pont(Sommet S, int j);

void Actualiser_Pont(Sommet S, Sommet S2, int x, int y, int j);

void Actualiser_Pontadv(int x, int y, int j);

void Afficher_Liste_Pont(int i);

void Remplacer_Sommet_Pont(Sommet s1, Sommet s2, int j);

int jouer_ia_pont (int ia);

#endif


