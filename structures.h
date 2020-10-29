#ifndef DEF_STRUCTURE
#define DEF_STRUCTURE

/* Définition du type Booléen */
typedef enum {
    false,
    true
}Bool;

/* Définition d'un ennemi */
typedef struct Ennemi {
    int vie;
    SDL_Rect ennemi;
}Ennemi;

/* Définition d'une Liste */
typedef struct ListeElement {
    Ennemi e;
    struct ListeElement *suivant;
}ListeElement, *Liste;

/* Prototypes */
Liste nouvelleListe();
Bool estVide(Liste li);
int listeTaille(Liste li);
Liste ajouterListe(Liste li, Ennemi en);


#endif
