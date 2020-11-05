#ifndef DEF_JEU
#define DEF_JEU

# include "structures.h"

/* Prototypes */
void jouer(SDL_Renderer* pRenderer);
void limiteFPS(unsigned int limite);
Uint32 bougerEnnemis(Uint32 intervalle, void *parametre);
void colorationEnnemi(SDL_Renderer *pRenderer, ListeEnnemi *li);
Uint32 creationEnnemi(Uint32 intervalle, void *parametre);

Case **allouerTab2D (int n, int m);
void desallouerTab2D(Case **tab, int n);

Bool possibilitePositionnerTourelle (SDL_Point *point, Case **tab, int *n, int *m);
void ajouterTourelleEtPositionnement (ListeTourelle **li, Case **tab, int n, int m);
void colorationTourelle(SDL_Renderer *pRenderer, ListeTourelle *li);

#endif