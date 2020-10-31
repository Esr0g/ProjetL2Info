#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "jeu.h"
#include "structures.h"
#include "constantes.h"

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
	
	Liste *listeEnnemi = NULL; // initialisation de la liste
	int nbEnnemi = 5; // nombre d'ennmis choisi

	/* Permet de faire un timer pour le spawn des énnemis */
	SDL_TimerID initialisationListeEnnemi;
	Bool initialisationListeEnnemiBool = false;
	
	/* Permet de faire un timer pour le déplacement des énnemis */
	SDL_TimerID mouvementEnnemi;
	Bool mouvementEnnemiBool = false;

	/* Pour la limite des FPS */
	unsigned int limite = 0;

/*----------------------------- Boucle principale d'une partie -------------------------*/
	while (partieContinuer) {
		SDL_Event eventsJeu;

		limite = SDL_GetTicks() + FPS_LIMITE;

		SDL_RenderCopy(pRenderer, pTextureFond, NULL, NULL);

		/* Active le timer de spawn si il n'est pas activé*/
		if (!initialisationListeEnnemiBool) {
			initialisationListeEnnemi = SDL_AddTimer((VITESSE_DEPLACEMENT_ENNEMI * (H_ENNEMI + 20)), creationEnnemi, &listeEnnemi);
			initialisationListeEnnemiBool = true;
		}

		/* Désactive le timer de spaxn lorsque le nombre d'énnemis est atteint */
		if (listeTaille(listeEnnemi) == nbEnnemi) {
			SDL_RemoveTimer(initialisationListeEnnemi);
		}

		/* Active le timer de déplcaement uniquement lorsque il y a des énnemis */
		if ((listeTaille(listeEnnemi) > 0) && (!mouvementEnnemiBool)) {
			mouvementEnnemi = SDL_AddTimer(VITESSE_DEPLACEMENT_ENNEMI, bougerEnnemis, &listeEnnemi);
			mouvementEnnemiBool = true;
		} else if (listeTaille == 0 && mouvementEnnemiBool) {
			SDL_RemoveTimer(mouvementEnnemi);
		}

		/* Color les énnemis lorsqu'il y'en a */
		if (!estVide(listeEnnemi)) {
			colorationEnnemi(pRenderer, listeEnnemi);
		}
		
		while (SDL_PollEvent(&eventsJeu)) {
			switch (eventsJeu.type) {
				case SDL_KEYDOWN:
						switch (eventsJeu.key.keysym.sym) {
							case SDLK_ESCAPE:
								partieContinuer =  SDL_FALSE;
								break;
							default:
								break;
						}
					continue;
            	default:
                	continue;
			}
		}


		limiteFPS(limite);
		SDL_RenderPresent (pRenderer);
		limite =  SDL_GetTicks() + FPS_LIMITE;

		
	}
/*--------------------- Fin de la boucle principale d'une partie ------------------*/

	SDL_DestroyTexture(pTextureFond);
	listeEnnemi = supprimerTout(&listeEnnemi);
	SDL_RemoveTimer(initialisationListeEnnemi);
	SDL_RemoveTimer(mouvementEnnemi);
}

/*------------------------------------------------------------------------------------*/

/**
 * Permet de limiter les FPS
 * @param limite
 */
void limiteFPS(unsigned int limite) {
	unsigned int ticks = SDL_GetTicks();

	if (limite < ticks) {
		return;
	} else if (limite > ticks + FPS_LIMITE) {
		SDL_Delay(FPS_LIMITE);
	} else {
		SDL_Delay(limite - ticks);
	}
}

/**
 * Fonction de callback pour le timer qui permet de bouger les énnemis qui viennent
 * de la gauche
 */
Uint32 bougerEnnemis(Uint32 intervalle, void *parametre) {
	Liste **li = parametre;
	Ennemi *e = NULL;
	for (int i = 0; i < listeTaille(*li); i++) {
		e = getEnnemi(*li, i);

		if (e->forme.x < 396 && e->forme.y == 268) {
			e->forme.x++;
		} else if (e->forme.x == 396 && e->forme.y < 588) {
			e->forme.y++;
		} else if (e->forme.x < 524 && e->forme.y == 588) {
			e->forme.x++;
		} else if (e->forme.x == 524) {
			e->forme.y++;
		}
	}

	return intervalle;
}

/**
 * Permet de colorer tous les ennemis qui sont dans une liste
 */
void colorationEnnemi(SDL_Renderer *pRenderer, Liste *li) {
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
	
	for (int i = 0; i < listeTaille(li); i++) {
		SDL_RenderFillRect(pRenderer, &getEnnemi(li, i)->forme);
	}
}

/**
 * Fonction de callback pour le timer qui permet de créer les énnemis
 * qui arrivent par la gauche les après les autres et de définir 
 * leur position de départ
 */
Uint32 creationEnnemi(Uint32 intervalle, void *parametre) {
	Liste **li = parametre;

	ajouterEnnemi(&(*li));
	definirEnnemiListe(*li, 0, VIE_ENNEMI_1, X_DEPART_ENNEMI_1, Y_DEPART_ENNEMI_1, W_ENNEMI, H_ENNEMI);
	return intervalle;
}
