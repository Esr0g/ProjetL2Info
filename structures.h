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
}ListeEnnemi;

/* Prototypes */
Bool estVide(ListeEnnemi *li);
int ajouterEnnemi(ListeEnnemi **li);
ListeEnnemi *supprimerTete(ListeEnnemi **li);
int listeTaille(ListeEnnemi *li);
ListeEnnemi *supprimerEnnemi(ListeEnnemi **li, int index);
ListeEnnemi *supprimerTout(ListeEnnemi **li);
Ennemi *getEnnemi(ListeEnnemi *li, int index);
void definirEnnemiListe(ListeEnnemi *li, int index, int v, int x, int y, int w, int h);
void setEnnemiPosition(ListeEnnemi *li, int index, int x, int y);
void setEnnemiVie(ListeEnnemi *li, int index, int v);
void setEnemmiTaille(ListeEnnemi *li, int index, int w, int h);

#endif
