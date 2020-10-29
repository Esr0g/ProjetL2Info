#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "jeu.h"
#include "structures.h"


typedef struct Base Base;
struct Base
{
	int vie;
	SDL_Rect rect;
};

void jouer(SDL_Renderer* pRenderer) {

	SDL_bool partieContinuer = SDL_TRUE;
	
	/* Chargelment de l'image du fond*/
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

	SDL_Rect e;
		e.x = 0;
		e.y = 260;
		e.h = 50;
		e.w = 50;

	int tempsActuel =0, tempsPrecedent = 0;

/*----------------------------- Boucle principale d'une partie -------------------------*/
	while (partieContinuer) {
		SDL_Event eventsJeu;

		SDL_RenderCopy(pRenderer, pTextureFond, NULL, NULL);

		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
		SDL_RenderFillRect(pRenderer, &e);

        SDL_RenderPresent (pRenderer);

		tempsActuel = SDL_GetTicks();
		if (tempsActuel-tempsPrecedent > 40) {
			e.x++;
			tempsPrecedent = tempsActuel;
		} else {
			SDL_Delay(40 - (tempsActuel - tempsPrecedent));
		}
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
