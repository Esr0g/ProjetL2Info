#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "jeu.h"
#include "structures.h"
#include "constantes.h"
#include "menuDefaite.h"

void menuDefaite(SDL_Renderer *pRenderer, SDL_bool *menu, SDL_bool *programLaunched) {

    Bool menuContinuer = true;

	SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurRouge = {255, 0, 0, 255};

	SDL_Rect positionTextePerdu;
    SDL_Rect poisitionTexteMenu;
    SDL_Rect positionTexteQuitter;

    /* Initialisation du texte "Perdu !"*/
	TTF_Font* font150 = TTF_OpenFont("textures/design.collection2.toontiei.ttf", 150);
	if (font150 == NULL) {
		SDL_Log("ERREUR: Creation de la police à partir d'une d'un fichier  > %s\n", TTF_GetError());

        menuContinuer = false;
        programLaunched = SDL_FALSE;
	}
	
	
    SDL_Surface *police150 = TTF_RenderText_Blended(font150, "Perdu !", couleurBlanche); 
	if (police150 == NULL) {
		SDL_Log("ERREUR: Creation de la surface du texte > %s\n", TTF_GetError());

        TTF_CloseFont(font150);
        menuContinuer = false;
        programLaunched = SDL_FALSE;
	}
	
    SDL_Texture *textureTextePerdu = SDL_CreateTextureFromSurface(pRenderer, police150);
	if (textureTextePerdu == NULL) {
		SDL_Log("ERREUR: Creation de la texture a partir de la surface du texte > %s\n", TTF_GetError());

        SDL_FreeSurface(police150);
        TTF_CloseFont(font150);
        menuContinuer = false;
        programLaunched = SDL_FALSE;        
	}
	
    SDL_QueryTexture(textureTextePerdu, NULL, NULL, &positionTextePerdu.w, &positionTextePerdu.h);

    positionTextePerdu.x = 250;
    positionTextePerdu.y = 100;

	SDL_FreeSurface(police150);
    TTF_CloseFont(font150);
	/*--------Fin de l'iitialisation du texte "Perdu !"---------*/

	/* Initialisation de la police pour "Quitter", "Rejouer" et "Menu" */
	TTF_Font* font70 = TTF_OpenFont("textures/design.collection2.toontiei.ttf", 70);
	if (font70 == NULL) {
		SDL_Log("ERREUR: Creation de la police à partir d'une d'un fichier  > %s\n", TTF_GetError());

        menuContinuer = false;
        programLaunched = SDL_FALSE;
	}

	/* Initialisation du Texte "Quitter" */
	SDL_Surface *policeQuitterBlanche = TTF_RenderText_Blended(font70, "Quitter", couleurBlanche); 
	SDL_Texture *textureTexteQuitter = SDL_CreateTextureFromSurface(pRenderer, policeQuitterBlanche);
	SDL_FreeSurface(policeQuitterBlanche);

	SDL_QueryTexture(textureTexteQuitter, NULL, NULL, &positionTexteQuitter.w, &positionTexteQuitter.h);
    positionTexteQuitter.x = 410;
    positionTexteQuitter.y = 550;

	/* Initialisation du Texte "Menu" */
	SDL_Surface *policeMenu = TTF_RenderText_Blended(font70, "Menu", couleurBlanche); 
	SDL_Texture *textureTexteMenu = SDL_CreateTextureFromSurface(pRenderer, policeMenu);
	SDL_FreeSurface(policeMenu);

	SDL_QueryTexture(textureTexteMenu, NULL, NULL, &poisitionTexteMenu.w, &poisitionTexteMenu.h);
    poisitionTexteMenu.x = 460;
    poisitionTexteMenu.y = 350;

	/*Poisition de la souris */
	SDL_Point positionSouri = {0, 0};
	SDL_Point positionClicSouri = {0, 0};

	Bool coloreTexteQuitter = false;
	Bool coloreTexteMenu = false;

    /* ----------------------------------------------------------- Boucle principal du menuDefaite ---------------------------------------------*/

    while (menuContinuer) {
        SDL_Event eventMenuDefait;
		SDL_Delay(15);
		
		/* Color le fond en noir et noettoye le rendu */
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);

		/* Permet d'afichier le texte Perdu */
        SDL_RenderCopy(pRenderer, textureTextePerdu, NULL, &positionTextePerdu);

		/* Permet mettre en rouge le texte "Quitter" quitter lorsque la souri est dessus */
		if (SDL_PointInRect(&positionSouri, &positionTexteQuitter) && coloreTexteQuitter == false ) {
			coloreTexteQuitter = true;
			SDL_DestroyTexture(textureTexteQuitter);

			policeQuitterBlanche = TTF_RenderText_Blended(font70, "Quitter", couleurRouge); 
			textureTexteQuitter = SDL_CreateTextureFromSurface(pRenderer, policeQuitterBlanche);

			SDL_FreeSurface(policeQuitterBlanche);

			SDL_QueryTexture(textureTexteQuitter, NULL, NULL, &positionTexteQuitter.w, &positionTexteQuitter.h);
			positionTexteQuitter.x = 410;
			positionTexteQuitter.y = 550;
			
		} else if (coloreTexteQuitter == true && !SDL_PointInRect(&positionSouri, &positionTexteQuitter)) {
			coloreTexteQuitter = false;
			SDL_DestroyTexture(textureTexteQuitter);

			policeQuitterBlanche = TTF_RenderText_Blended(font70, "Quitter", couleurBlanche); 
			textureTexteQuitter = SDL_CreateTextureFromSurface(pRenderer, policeQuitterBlanche);

			SDL_FreeSurface(policeQuitterBlanche);

			SDL_QueryTexture(textureTexteQuitter, NULL, NULL, &positionTexteQuitter.w, &positionTexteQuitter.h);
			positionTexteQuitter.x = 410;
			positionTexteQuitter.y = 550;
		}

		/*Permet de colorer en rouge le cadre du texte "Quitter" */
		if (coloreTexteQuitter == true) {
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteQuitter);
		} else {
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteQuitter);
		}

		/* Affiche le texte "Quitter" */
		SDL_RenderCopy(pRenderer, textureTexteQuitter, NULL, &positionTexteQuitter);

		/* Permet mettre en rouge le texte "Menu" lorsque la souri est dessus */
		if (SDL_PointInRect(&positionSouri, &poisitionTexteMenu) && coloreTexteMenu == false ) {
			coloreTexteMenu = true;
			SDL_DestroyTexture(textureTexteMenu);

			policeMenu = TTF_RenderText_Blended(font70, "Menu", couleurRouge); 
			textureTexteMenu = SDL_CreateTextureFromSurface(pRenderer, policeMenu);

			SDL_FreeSurface(policeMenu);

			SDL_QueryTexture(textureTexteMenu, NULL, NULL, &poisitionTexteMenu.w, &poisitionTexteMenu.h);
			poisitionTexteMenu.x = 460;
			poisitionTexteMenu.y = 350;
			
		} else if (coloreTexteMenu == true && !SDL_PointInRect(&positionSouri, &poisitionTexteMenu)) {
			coloreTexteMenu = false;
			SDL_DestroyTexture(textureTexteMenu);

			policeMenu = TTF_RenderText_Blended(font70, "Menu", couleurBlanche); 
			textureTexteMenu = SDL_CreateTextureFromSurface(pRenderer, policeMenu);

			SDL_FreeSurface(policeMenu);

			SDL_QueryTexture(textureTexteMenu, NULL, NULL, &poisitionTexteMenu.w, &poisitionTexteMenu.h);
			poisitionTexteMenu.x = 460;
			poisitionTexteMenu.y = 350;
		}

		/*Permet de colorer en rouge le cadre du texte "Menu" */
		if (coloreTexteMenu == true) {
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(pRenderer, &poisitionTexteMenu);
		} else {
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(pRenderer, &poisitionTexteMenu);
		}

		/* Affiche le texte "Menu" */
		SDL_RenderCopy(pRenderer, textureTexteMenu, NULL, &poisitionTexteMenu);

  		while (SDL_PollEvent(&eventMenuDefait)) {
			switch (eventMenuDefait.type) {
				case SDL_MOUSEBUTTONUP:
					positionClicSouri.x = eventMenuDefait.button.x;
					positionClicSouri.y = eventMenuDefait.button.y;
					if (SDL_PointInRect(&positionClicSouri, &positionTexteQuitter)) {
						menuContinuer = false;
						*menu = SDL_FALSE;
                        *programLaunched = SDL_FALSE;
						printf("Clic\n");
					} else if (SDL_PointInRect(&positionClicSouri, &poisitionTexteMenu)) {
						menuContinuer = false;
						*menu = SDL_FALSE;
					}
					break;
				case SDL_MOUSEMOTION:
					positionSouri.x = eventMenuDefait.motion.x;
					positionSouri.y = eventMenuDefait.motion.y;
					break;
            	default:
                	break;
			}
		}

		SDL_RenderPresent (pRenderer);
    }

    /*-------------------------------------------------------- Fin de la boucle principal du menuDefaite ---------------------------------------*/
	SDL_DestroyTexture (textureTextePerdu);
	SDL_DestroyTexture (textureTexteQuitter);
	SDL_DestroyTexture (textureTexteMenu);
    TTF_CloseFont(font70);
}
