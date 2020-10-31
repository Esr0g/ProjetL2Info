#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structures.h"

/**
 * Permet d'ajouter un nouvel ennemi à la liste
 * @param li pointeur de pointeur de la liste
 * @return 0 si tous s'est bien passé ou -1 si l'allocation dynamique à échouée
 */ 
int ajouterEnnemi(Liste **li) {
    Ennemi ennemi;
    Liste *element;
    element = (Liste*)malloc(sizeof(Liste));

    if (element == NULL) {
        return -1;
    }

    element->en = ennemi;
    element->suivant = *li;
    *li = element;

    return 0;
}

/**
 * @return true si la liste est vide
 */
Bool estVide(Liste *li) {
    if (li == NULL) {
        return true;
    }

    return false;
}

/**
 * Supprimer le premier élément de la liste
 * @param li double pointeur de la liste
 * @return li un pointeur de la liste ou NULL si la liste est vide
 */
Liste *supprimerTete(Liste **li) {
    Liste *elementSuivant = NULL;

    if (estVide(*li)) {
        return NULL;
    }

    elementSuivant = (*li)->suivant;
    free(*li);
    *li = elementSuivant;
    free(elementSuivant);

    return *li;
}

/**
 * Retourne la taille de la liste
 * @param li pointeur d'une liste
 * @return size la taille de la liste
 */
int listeTaille(Liste *li) {
    int taille = 0;

    if (!estVide(li)) {
        while (!estVide(li)) {
            taille++;
            li = li->suivant;
        }
    }

    return taille;
}

/**
 * Suprime un élément à un index précis
 * @param li double pointeur de la liste
 * @param index de l'élément à supprimer
 * @return li pointeur de la liste ou NULL si la liste est vide
 */
Liste *supprimerEnnemi(Liste **li, int index) {

    Liste *acctuel = *li;
    Liste *temp = NULL;

    if (index == 0) {
        return supprimerTete(&(*li));
    }

    for (int i = 0; i < index-1; i++) {
        if (acctuel->suivant == NULL) {
            return NULL;
        }
        acctuel = acctuel->suivant;
    }

    temp = acctuel->suivant;
    acctuel->suivant = temp->suivant;
    free(temp);

    return *li;
}

/**
 * Supprime tous les éléments de la liste
 * @param li double pointeur de la liste
 * @return une liste vide
 */
Liste *supprimerTout (Liste **li) {

    Liste *elementSuivant;

    if (estVide(*li)) {
        return NULL;
    } else {

        while (*li != NULL) {
            elementSuivant = NULL;
            elementSuivant = (*li)->suivant;
            free(*li);
            *li = elementSuivant;
        }

        return *li;
    } 
}

/**
 * Renvoie l'ennemi à l'index spécifique de la liste
 * @param li pointeur de la liste
 * @param index de l'ennemi (compris entre 1 et la taille de la liste);
 * @return e l'ennemi à l'index choisi
 */
Ennemi *getEnnemi (Liste *li, int index) {
    if (index == 0) {
        return &li->en;
    }

    Ennemi *e;

    for (int i = 0; i < index; i++) {
        li = li->suivant;
        e = NULL;
        e = &li->en;
    }

    return e;
}

/**
 * Permet de définir complétement un énnemi à un index précis
 * @param li pointeur de la liste;
 * @param index de l'ennemi dans la liste
 * @param vie de l'ennemi
 * @param x coordonée x de l'ennemi
 * @param y coordonée y de l'ennemi
 * @param w largeur de l'ennemi
 * @param h hauteur de l'ennemi
 */
void definirEnnemiListe(Liste *li, int index, int v, int x, int y, int w, int h) {
    Liste *acctuel = li;
    Ennemi *e = NULL;

    if (index == 0) {
        e = &li->en;
    } else {
        for (int i = 0; i < index; i++) {
            acctuel = acctuel->suivant;
            e = &acctuel->en;
        }
    }

    e->vie = v;
    e->forme.h = h;
    e->forme.w = w;
    e->forme.x = x;
    e->forme.y = y;
}

/**
 * Permet de définir la position de l'ennemi
 * @param li pointeur de la liste
 * @param index de l'ennemi dans la liste
 * @param x
 * @param y
 */
void setEnnemiPosition(Liste *li, int index, int x, int y) {
    Liste *acctuel = li;
    Ennemi *e = NULL;

    if (index == 0) {
        e = &li->en;
    } else {
        for (int i = 0; i < index; i++) {
            acctuel = acctuel->suivant;
            e = &acctuel->en;
        }
    }

    e->forme.x = x;
    e->forme.y = y;
}

/**
 * Permet de définir la vie de l'ennemi
 * @param li pointeur sur la liste
 * @param index de l'ennemi
 * @param v vie de l'ennemi
 */
void setEnnemiVie(Liste *li, int index, int v) {
    Liste *acctuel = li;
    Ennemi *e = NULL;

    if (index == 0) {
        e = &li->en;
    } else {
        for (int i = 0; i < index; i++) {
            acctuel = acctuel->suivant;
            e = &acctuel->en;
        }
    }

    e->vie = v;
}

/**
 * Permet de définir la taille de l'ennemi
 * @param li pointeur sur la liste
 * @param w largeur de l'ennemi
 * @param h hauteur de l'ennemi
 */
void setEnemmiTaille(Liste *li, int index, int w, int h) {
    Liste *acctuel = li;
    Ennemi *e = NULL;

    if (index == 0) {
        e = &li->en;
    } else {
        for (int i = 0; i < index; i++) {
            acctuel = acctuel->suivant;
            e = &acctuel->en;
        }
    }

    e->forme.w = w;
    e->forme.h = h;
}
