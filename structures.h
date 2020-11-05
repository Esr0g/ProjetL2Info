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

/*Définition d'une tourelle */
typedef struct Tourelle {
    int vie;
    int degats;
    int vitesseAttaque;
    int type;
    SDL_Rect forme;
}Tourelle;

/* Définition d'une liste de tourelles */
typedef struct ElementListeTourelle {
    Tourelle tourelle;
    struct ElementListeTourelle *suivant;
}ListeTourelle;

/* Définition d'une liste d'ennemis */
typedef struct ElementListe {
    Ennemi en;
    struct ElementListe *suivant;
}ListeEnnemi;

/* Prototypes ListeEnnemi */
Bool listeEstVideEnnemi(ListeEnnemi *li);
int ajouterEnnemi(ListeEnnemi **li);
ListeEnnemi *supprimerTeteListeE(ListeEnnemi **li);
int listeTailleEn (ListeEnnemi *li);
ListeEnnemi *supprimerEnnemi(ListeEnnemi **li, int index);
ListeEnnemi *supprimerToutEn(ListeEnnemi **li);
Ennemi *getEnnemi(ListeEnnemi *li, int index);
void definirEnnemiListe(ListeEnnemi *li, int index, int v, int x, int y, int w, int h);
void setEnnemiPosition(ListeEnnemi *li, int index, int x, int y);
void setEnnemiVie(ListeEnnemi *li, int index, int v);
void setEnemmiTaille(ListeEnnemi *li, int index, int w, int h);

/* prototypes ListeTourelle */
Bool listeEstVideTourelle (ListeTourelle *li);
int ajouterTourelle (ListeTourelle **li);
ListeTourelle *supprimerTeteListeT (ListeTourelle **li);
int listeTailleTour (ListeTourelle *li);
ListeTourelle *supprimerTourelle (ListeTourelle **li, int index);
ListeTourelle *supprimerToutTour(ListeTourelle **li);
Tourelle *getTourelle(ListeTourelle *li, int index);

#endif
