#ifndef DEF_JEU
#define DEF_JEU

# include "structures.h"

/* Prototypes */
void jouer(SDL_Renderer* pRenderer);
void limiteFPS(unsigned int limite);
Uint32 bougerEnnemis(Uint32 intervalle, void *parametre);
void colorationEnnemi(SDL_Renderer *pRenderer, Liste *li);
Uint32 creationEnnemi(Uint32 intervalle, void *parametre);

#endif