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