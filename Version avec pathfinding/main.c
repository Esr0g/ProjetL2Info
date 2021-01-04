#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "constantes.h"

#include "jeu.h"
#include "structures.h"
/* https://github.com/Esr0g/ProjetL2Info.git */
/* valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=supdata.log ./towerDefence */

int main(void)
{
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;
    SDL_bool programLaunched = SDL_TRUE;

    /**
     * Initialisation de la SDL
     */
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log ("ERREUR: Initialisation SDL > %s\n", SDL_GetError());

        exit(EXIT_FAILURE);
    }

    /**
     * Creation de la fenêtre
     */
    pWindow = SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FENETRE_LARGEUR, FENETRE_HAUTEUR, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("ERREUR: Creation de la fenêtre > %s\n", SDL_GetError());

        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /**
     * Initialisation de SDL_ttf qui permet de géré le texte
     */
	if (TTF_Init() < 0) {
		SDL_Log("ERREUR: Creation de la fenêtre > %s\n", TTF_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
		exit(EXIT_FAILURE);
	}

    /**
     * Création du Rendu
     */
    pRenderer = SDL_CreateRenderer (pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL) {
        SDL_Log("ERREUR: Creation du Rendu > %s\n", SDL_GetError());

        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

                        /////////////////////////////////
                        // Chargement des textes du Menu
                        /////////////////////////////////


    /** 
     * Menu
     */
    TTF_Font *policeMenuPrcipale150 = TTF_OpenFont("textures/design.collection2.toontiei.ttf", 150);
    if (policeMenuPrcipale150 == NULL) {
        SDL_Log("ERREUR: Chargement de la police > %s\n", TTF_GetError());

        programLaunched = SDL_FALSE;
    }

    SDL_Color couleurBlancheTexteMenu = {255, 255, 255, 255};
    SDL_Color couleurRougeTexteMenu = {255, 0, 0, 255};

    SDL_Rect positionTexteMenuPrincipale;

    SDL_Surface *surfaceTexteMenuPrincipale = TTF_RenderText_Blended(policeMenuPrcipale150, "Menu", couleurBlancheTexteMenu);
    if (surfaceTexteMenuPrincipale == NULL) {
        SDL_Log("ERREUR: Chargement de la surface > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }

    TTF_CloseFont(policeMenuPrcipale150);

    SDL_Texture *textureTexteMenuPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteMenuPrincipale);
    if (textureTexteMenuPrincipale == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'un texte > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }

    SDL_FreeSurface(surfaceTexteMenuPrincipale);

    SDL_QueryTexture(textureTexteMenuPrincipale, NULL, NULL, &positionTexteMenuPrincipale.w, &positionTexteMenuPrincipale.h);

    positionTexteMenuPrincipale.x = (FENETRE_LARGEUR / 2) - (positionTexteMenuPrincipale.w / 2);
    positionTexteMenuPrincipale.y = 100;

    /**
     * Jouer
     */
    TTF_Font *policeMenuPrcipale70 = TTF_OpenFont("textures/design.collection2.toontiei.ttf", 70);
    if (policeMenuPrcipale70 == NULL) {
        SDL_Log("ERREUR: Chargement de la police > %s\n", TTF_GetError());

        programLaunched = SDL_FALSE;
    }
    
    SDL_Rect positionTexteJouerPrincipale;

    SDL_Surface *surfaceTexteJouerPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Jouer", couleurBlancheTexteMenu);
    if (surfaceTexteJouerPrincipale == NULL) {
        SDL_Log("ERREUR: Chargement de la surface > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }

    SDL_Texture *textureTexteJouerPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteJouerPrincipale);
    if (textureTexteJouerPrincipale == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'un texte > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }
    
    SDL_FreeSurface(surfaceTexteJouerPrincipale);

    SDL_QueryTexture(textureTexteJouerPrincipale, NULL, NULL, &positionTexteJouerPrincipale.w, &positionTexteJouerPrincipale.h);

    positionTexteJouerPrincipale.x = (FENETRE_LARGEUR / 2) - (positionTexteJouerPrincipale.w / 2);
    positionTexteJouerPrincipale.y = 350;
    

    /**
     * Quitter
     */
    SDL_Rect positionTexteQuitterPricipale;

    SDL_Surface *surfaceTexteQuitterPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Quitter", couleurBlancheTexteMenu);
    if (surfaceTexteQuitterPrincipale == NULL) {
        SDL_Log("ERREUR: Chargement de la surface > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }
    
    SDL_Texture *textureTexteQuitterPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteQuitterPrincipale);
    if (textureTexteQuitterPrincipale == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'un texte > %s\n", SDL_GetError());

        programLaunched = SDL_FALSE;
    }
    
    SDL_FreeSurface(surfaceTexteQuitterPrincipale);

    SDL_QueryTexture(textureTexteQuitterPrincipale, NULL, NULL, &positionTexteQuitterPricipale.w, &positionTexteQuitterPricipale.h);

    positionTexteQuitterPricipale.x = (FENETRE_LARGEUR / 2) - (positionTexteQuitterPricipale.w / 2);
    positionTexteQuitterPricipale.y = 550;

    SDL_Point positionClicSouriMenuP = {0, 0};
    SDL_Point positionSouriMenuP = {0, 0};
    Bool colorationTexteJouerMP = false;
    Bool colorationTexteQuitterMP = false;

                                                        ///////////////////////
/* -----------------------------------------------------// Boucle principale //--------------------------------------------------------------*/
                                                        ///////////////////////
    while (programLaunched) {
        SDL_Event events;

        /**
         * Color l'écran en noir et affiche
         */
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);

        /**
         * Affichage du texte Menu
         */
        SDL_RenderCopy(pRenderer, textureTexteMenuPrincipale, NULL, &positionTexteMenuPrincipale);

        /**
         * Permet mettre en rouge le texte "Jouer" lorsque la souri passe dessus dessus
         */
		if (SDL_PointInRect(&positionSouriMenuP, &positionTexteJouerPrincipale) && !colorationTexteJouerMP) {
			colorationTexteJouerMP = true;
			SDL_DestroyTexture(textureTexteJouerPrincipale);

			surfaceTexteJouerPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Jouer", couleurRougeTexteMenu); 
			textureTexteJouerPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteJouerPrincipale);

			SDL_FreeSurface(surfaceTexteJouerPrincipale);
			
		} else if (colorationTexteJouerMP && !SDL_PointInRect(&positionSouriMenuP, &positionTexteJouerPrincipale)) {
			colorationTexteJouerMP = false;
			SDL_DestroyTexture(textureTexteJouerPrincipale);

			surfaceTexteJouerPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Jouer", couleurBlancheTexteMenu); 
			textureTexteJouerPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteJouerPrincipale);

			SDL_FreeSurface(surfaceTexteJouerPrincipale);
		}

		/**
         * Permet de colorer en rouge le cadre du texte "Jouer"
         */
		if (colorationTexteJouerMP) {
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteJouerPrincipale);
		} else {
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteJouerPrincipale);
		}

		/**
         * Affiche le texte "Jouer"
         */
		SDL_RenderCopy(pRenderer, textureTexteJouerPrincipale, NULL, &positionTexteJouerPrincipale);

        /**
         * Permet mettre en rouge le texte "Quitter" lorsque la souri passe dessus dessus
         */
		if (SDL_PointInRect(&positionSouriMenuP, &positionTexteQuitterPricipale) && !colorationTexteQuitterMP) {
			colorationTexteQuitterMP = true;
			SDL_DestroyTexture(textureTexteQuitterPrincipale);

			surfaceTexteQuitterPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Quitter", couleurRougeTexteMenu); 
			textureTexteQuitterPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteQuitterPrincipale);

			SDL_FreeSurface(surfaceTexteQuitterPrincipale);
			
		} else if (colorationTexteQuitterMP && !SDL_PointInRect(&positionSouriMenuP, &positionTexteQuitterPricipale)) {
			colorationTexteQuitterMP = false;
			SDL_DestroyTexture(textureTexteQuitterPrincipale);

			surfaceTexteQuitterPrincipale = TTF_RenderText_Blended(policeMenuPrcipale70, "Quitter", couleurBlancheTexteMenu); 
			textureTexteQuitterPrincipale = SDL_CreateTextureFromSurface(pRenderer, surfaceTexteQuitterPrincipale);

			SDL_FreeSurface(surfaceTexteQuitterPrincipale);
		}

		/**
         * Permet de colorer en rouge le cadre du texte "Quitter"
         */
		if (colorationTexteQuitterMP) {
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteQuitterPricipale);
		} else {
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(pRenderer, &positionTexteQuitterPricipale);
		}

		/**
         * Affiche le texte "Quitter"
         */
		SDL_RenderCopy(pRenderer, textureTexteQuitterPrincipale, NULL, &positionTexteQuitterPricipale);

        SDL_RenderPresent (pRenderer);

       while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_MOUSEBUTTONUP:
                    positionClicSouriMenuP.x = events.button.x;
                    positionClicSouriMenuP.y = events.button.y;
                    if (SDL_PointInRect(&positionClicSouriMenuP, &positionTexteJouerPrincipale)) {
                        jouer(pRenderer, &programLaunched);
                    } else if (SDL_PointInRect(&positionClicSouriMenuP, &positionTexteQuitterPricipale)) {
                        programLaunched = SDL_FALSE;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    positionSouriMenuP.x = events.motion.x;
                    positionSouriMenuP.y = events.motion.y;
                    break;
                default:
                    break;
            }
        }

        SDL_Delay(FPS_LIMITE);
    }

                                                    /////////////////////////////////
/*--------------------------------------------------// Fin de la boucle principale //-----------------------------------------------------*/
                                                    ////////////////////////////////

    SDL_DestroyTexture(textureTexteJouerPrincipale);
    SDL_DestroyTexture(textureTexteQuitterPrincipale);
    TTF_CloseFont(policeMenuPrcipale70);
    SDL_DestroyTexture(textureTexteMenuPrincipale);
    SDL_DestroyRenderer (pRenderer);
    SDL_DestroyWindow (pWindow);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
