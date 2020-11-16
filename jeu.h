#ifndef DEF_JEU
#define DEF_JEU

# include "structures.h"

/* Prototypes */
void jouer(SDL_Renderer* pRenderer, SDL_bool *programLaunched);
void limiteFPS(unsigned int limite);
Uint32 bougerEnnemis(Uint32 intervalle, void *parametre);
void colorationEnnemi(SDL_Renderer *pRenderer, ListeEnnemi *li);
Uint32 creationEnnemi(Uint32 intervalle, void *parametre);

Cases **allouerTab2D (int n, int m);
void desallouerTab2D(Cases **tab, int n);

Bool possibilitePositionnerTourelle (SDL_Point *point, Cases **tab, int *n, int *m);
void ajouterTourelleEtPositionnement (ListeTourelle **li, Cases **tab, int n, int m);
void colorationTourelle(SDL_Renderer *pRenderer, ListeTourelle *li);
Bool souriSurTourelle(SDL_Point *p, ListeTourelle *li, int *tourelle);

/**
 * Prototypes des fonctions pour les collision avec un cercle
 * source: http://sdz.tdct.org/sdz/eorie-des-collisions.html
 */
Bool collisionPointCercle(int x, int y, Cercle C);
int projectionSurSegment(int Cx,int Cy,int Ax,int Ay,int Bx,int By);
Bool collisionCercleRectangle(Cercle C1, SDL_Rect box1);

void attaqueEnnemi (ListeEnnemi *le, ListeTourelle *lt);

#endif