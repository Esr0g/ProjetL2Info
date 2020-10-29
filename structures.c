#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structures.h"

/* Initialisation d'une nouvelle liste */
Liste nouvelleListe() {
    return NULL;
}

/* Renvoie true si la liste est vide */
Bool estVide(Liste li) {
    if (li == NULL) {
        return true;
    }

    return false;
}

/* Retourne le nombre d'élements qui composent la liste */
int listeTaille(Liste li) {
    int size = 0;

    if (!estVide(li)) {
        while (li != NULL) {
            size++;
            li = li->suivant;
        }
    }

    return size;
}

/* Ajoute un élément au début de la liste */
Liste ajouterListe(Liste li, Ennemi en) {
    
}
