#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structures.h"

                                                    ////////////////////////////////////////
                                                    // Fonctions sur les listes d'ennemis //
                                                    ////////////////////////////////////////

/**
 * Permet d'ajouter un nouvel ennemi à la liste
 * @param li pointeur de pointeur de la liste
 * @return 0 si tous s'est bien passé ou -1 si l'allocation dynamique à échouée
 */ 
int ajouterEnnemi(ListeEnnemi **li) {
    ListeEnnemi *element;
    element = (ListeEnnemi*)malloc(sizeof(ListeEnnemi));

    if (element == NULL) {
        return -1;
    }

    element->suivant = *li;
    *li = element;

    //creation test passfiding
    element->moment_chemin =0;
    element->est_block=0;

    return 0;
}

/**
 * @return true si la liste est vide
 */
Bool listeEstVideEnnemi(ListeEnnemi *li) {
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
ListeEnnemi *supprimerTeteListeE(ListeEnnemi **li) {
    ListeEnnemi *elementSuivant = NULL;

    if (listeEstVideEnnemi(*li)) {
        return NULL;
    } else if (listeTailleEn(*li) == 1) {
        free (*li);
        (*li) = NULL;
    } else {
        elementSuivant = (*li)->suivant;
        free(*li);
        *li = elementSuivant;
    }

    return *li;
}

/**
 * Retourne la taille de la liste
 * @param li pointeur d'une liste
 * @return size la taille de la liste
 */
int listeTailleEn(ListeEnnemi *li) {
    int taille = 0;

    if (!listeEstVideEnnemi(li)) {
        while (!listeEstVideEnnemi(li)) {
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
ListeEnnemi *supprimerEnnemi(ListeEnnemi **li, int index) {

    ListeEnnemi *acctuel = *li;
    ListeEnnemi *temp = NULL;

    if (index == 0) {
        return supprimerTeteListeE(&(*li));
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
ListeEnnemi *supprimerToutEn (ListeEnnemi **li) {

    ListeEnnemi *elementSuivant;

    if (listeEstVideEnnemi(*li)) {
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
Ennemi *getEnnemi (ListeEnnemi *li, int index) {
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
void definirEnnemiListe(ListeEnnemi *li, int index, int v, int x, int y, int w, int h) {
    ListeEnnemi *acctuel = li;
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
void setEnnemiPosition(ListeEnnemi *li, int index, int x, int y) {
    ListeEnnemi *acctuel = li;
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
void setEnnemiVie(ListeEnnemi *li, int index, int v) {
    ListeEnnemi *acctuel = li;
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
void setEnemmiTaille(ListeEnnemi *li, int index, int w, int h) {
    ListeEnnemi *acctuel = li;
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

                                                        ///////////////////////////////////////////
                                                        // Fonctions sur les listes de tourelles //
                                                        ///////////////////////////////////////////
/**
 * @return true si la liste est vide
 */
Bool listeEstVideTourelle (ListeTourelle *li) {
    if (li == NULL) {
        return true;
    }

    return false;
}

/**
 * Permet d'ajouter une nouvelle tourelle à la liste
 * @param li pointeur de pointeur de la liste
 * @return 0 si tous s'est bien passé ou -1 si l'allocation dynamique à échouée
 */ 
int ajouterTourelle (ListeTourelle **li) {
    ListeTourelle *element;
    element = (ListeTourelle*)malloc(sizeof(ListeTourelle));

    if (element == NULL) {
        return -1;
    }

    element->suivant = *li;
    *li = element;

    return 0;
}

/**
 * Supprimer le premier élément de la liste
 * @param li double pointeur de la liste
 * @return li un pointeur de la liste ou NULL si la liste est vide
 */
ListeTourelle *supprimerTeteListeT (ListeTourelle **li) {
    ListeTourelle *elementSuivant = NULL;

    if (listeEstVideTourelle(*li)) {
        return NULL;
    }

    elementSuivant = (*li)->suivant;
    free(*li);
    *li = elementSuivant;

    return *li;
}

/**
 * Retourne la taille de la liste
 * @param li pointeur d'une liste
 * @return size la taille de la liste
 */
int listeTailleTour (ListeTourelle *li) {
    int taille = 0;

    if (!listeEstVideTourelle(li)) {
        while (!listeEstVideTourelle(li)) {
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
ListeTourelle *supprimerTourelle (ListeTourelle **li, int index) {

    ListeTourelle *acctuel = *li;
    ListeTourelle *temp = NULL;

    if (index == 0) {
        return supprimerTeteListeT(&(*li));
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
ListeTourelle *supprimerToutTour(ListeTourelle **li) {

    ListeTourelle *elementSuivant;

    if (listeEstVideTourelle(*li)) {
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

Tourelle *getTourelle(ListeTourelle *li, int index) {

    if (index == 0) {
        return &li->tourelle;
    }

    Tourelle *t;

    for (int i = 0; i < index; i++) {
        li = li->suivant;
        t = NULL;
        t = &li->tourelle;
    }

    return t;
}

/**
 * Permet de définir le nouveau temps entre 2 tire
 * @param li pointeur sur la liste
 * @param index del la tourelle
 * @param tps nouveau temps
 */
void setTourelleTps (ListeTourelle *li, int index, int tps) {
    ListeTourelle *acctuel = li;
    Tourelle *t = NULL;

    if (index == 0) {
        t = &li->tourelle;
    } else {
        for (int i = 0; i < index; i++) {
            acctuel = acctuel->suivant;
            t = &acctuel->tourelle;
        }
    }

    t->tpsEntre2Tire = tps;
}
