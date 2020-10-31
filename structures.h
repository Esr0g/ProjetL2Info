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
    SDL_Rect forme;
}Ennemi;

/* Définition de la base */
typedef struct Base {
    int vie;
    SDL_Rect base;
}Base;

/* Définition de la liste */
typedef struct ElementListe {
    Ennemi en;
    struct ElementListe *suivant;
}Liste;

/* Prototypes */
Bool estVide(Liste *li);
int ajouterEnnemi(Liste **li);
Liste *supprimerTete(Liste **li);
int listeTaille(Liste *li);
Liste *supprimerEnnemi(Liste **li, int index);
Liste *supprimerTout(Liste **li);
Ennemi *getEnnemi(Liste *li, int index);
void definirEnnemiListe(Liste *li, int index, int v, int x, int y, int w, int h);
void setEnnemiPosition(Liste *li, int index, int x, int y);
void setEnnemiVie(Liste *li, int index, int v);
void setEnemmiTaille(Liste *li, int index, int w, int h);

#endif
