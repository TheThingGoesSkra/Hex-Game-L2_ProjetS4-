/* 
Module pensé par Matthieu Pont
réalisé par Matthieu Pont.
Liste générique.
*/
#ifndef LISTE_H
#define LISTE_H

typedef struct etliste * Liste;

typedef void* element;


/* Creer la la liste */
Liste creer_liste();

/* Libere la liste si free_elem = 1 alors on free l'element de chaque cellule aussi */
void free_liste(Liste l, int free_elem);

/* Retourne la taille de la liste */
int get_liste_taille(Liste l);

/* Ajoute l'element e a la liste l */
Liste ajouter_elem(Liste l, element e);

/* Supprime l'element e de la liste l */
Liste supprimer_elem(Liste l, element e);

/* Fusionne la liste l1 et l2 dans la liste l1 */
Liste merge_liste(Liste l1, Liste l2);

/* Retourne une copie de la liste l */
Liste copier_liste(Liste l);

/* --------------------- */
/* ----- ITERATEUR ----- */
/* --------------------- */

/* Renvoit le premier element de la liste */
element ite_begin(Liste l);

/* Renvoit 1 si l'iterateur a atteint la fin */
int ite_isEnd(Liste l);

/* Renvoit l'élement suivant et avance l'iterateur a la prochaine cellule */
element ite_next(Liste l);

/* --------------------- */

/* ----------------- */
/* ----- DEBUG ----- */
/* ----------------- */

void afficher_liste_pointeur(Liste l);

/* ----------------- */

#endif
