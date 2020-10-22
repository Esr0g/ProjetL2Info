#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "jeu.h"

typedef struct Ennemis1 Ennemis1;
struct Ennemis1
{
    int vie; 
	int Rect;
	
	
	
};
	int  getVie(Ennemis1 e1)
	{
		return e1.vie;
	}	


typedef struct Base Base;
struct Base
{
	int vie;
	SDL_Rect rect;
};

void jouer(SDL_Renderer* pRenderer) {

	SDL_bool partieContinuer = SDL_TRUE;

    SDL_Surface *pFond = SDL_LoadBMP ("textures/Terrain.bmp");
    if (pFond == NULL) {
        SDL_Log("ERREUR: Chargement de l'image > %s\n", SDL_GetError());

		partieContinuer = SDL_FALSE;
    }

    SDL_Texture *pTextureFond = SDL_CreateTextureFromSurface(pRenderer, pFond);
    if (pTextureFond == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'une image > %s\n", SDL_GetError());

        SDL_FreeSurface(pFond);
		partieContinuer = SDL_FALSE;
    }

	SDL_FreeSurface (pFond);

	partieContinuer = SDL_TRUE;
	
/*----------------------------- Boucle principale d'une partie -------------------------*/
	while (partieContinuer) {
		SDL_Event eventsJeu;
		SDL_RenderCopy(pRenderer, pTextureFond, NULL, NULL);
        SDL_RenderPresent (pRenderer);

		while (SDL_PollEvent(&eventsJeu)) {
			switch (eventsJeu.type) {
				case SDL_KEYDOWN:
						switch (eventsJeu.key.keysym.sym) {
							case SDLK_ESCAPE:
								partieContinuer =  SDL_FALSE;
								break;
							default:
								continue;

						}
					continue;
            	default:
                	continue;
			}
		}
	}
/*--------------------- Fin de la boucle principale d'une partie ------------------*/

}
