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

	Base base01; base01.base.h = 64; base01.base.w = 128 ; base01.base.x = 448; base01.base.y = 896; base01.vie = 3;
	
	
	ListeEnnemi *listeEnnemi = NULL; // initialisation de la liste d'ennemis
	int nbEnnemi = 5; // nombre d'ennmis choisi

	ListeTourelle *listeTourelle = NULL; // initialisation de la liste de tourelle

	/* Initialisation des cases du jeu */
	Case **tabCase = allouerTab2D (15, 18);
	int ligne;
	int colone;

	/* Permet de faire un timer pour le spawn des énnemis */
	SDL_TimerID initialisationListeEnnemi;
	Bool initialisationListeEnnemiBool = false;
	
	/* Permet de faire un timer pour le déplacement des énnemis */
	SDL_TimerID mouvementEnnemi;
	Bool mouvementEnnemiBool = false;

	/* Pour la limite des FPS */
	unsigned int limite = 0;

	SDL_Point positionClicSouris;

/*----------------------------- Boucle principale d'une partie -------------------------*/
	while (partieContinuer) {
		SDL_Event eventsJeu;
		 
		SDL_RenderCopy(pRenderer, pTextureFond, NULL, NULL);

		/* Active le timer de spawn si il n'est pas activé*/
		if (!initialisationListeEnnemiBool) {
			initialisationListeEnnemi = SDL_AddTimer((VITESSE_DEPLACEMENT_ENNEMI * (H_ENNEMI + 20)), creationEnnemi, &listeEnnemi);
			initialisationListeEnnemiBool = true;
		}

		/* Désactive le timer de spaxn lorsque le nombre d'énnemis est atteint */
		if (listeTailleEn(listeEnnemi) == nbEnnemi) {
			SDL_RemoveTimer(initialisationListeEnnemi);
		}

		/* Active le timer de déplcaement uniquement lorsque il y a des énnemis */
		if ((listeTailleEn(listeEnnemi) > 0) && (!mouvementEnnemiBool)) {
			mouvementEnnemi = SDL_AddTimer(VITESSE_DEPLACEMENT_ENNEMI, bougerEnnemis, &listeEnnemi);
			mouvementEnnemiBool = true;
		} else if (listeTailleEn == 0 && mouvementEnnemiBool) {
			SDL_RemoveTimer(mouvementEnnemi);
		}

		for (int i = 0; i < listeTailleEn(listeEnnemi); i++) {
			if (SDL_HasIntersection(&getEnnemi(listeEnnemi, i)->forme, &base01.base)) {
				supprimerEnnemi(&listeEnnemi, i);
				base01.vie--;
			}
		}

		limite = SDL_GetTicks() + FPS_LIMITE;

		/* Color les énnemis lorsqu'il y'en a */
		limiteFPS(limite);
		if (!listeEstVideEnnemi(listeEnnemi)) {
			colorationEnnemi(pRenderer, listeEnnemi);
		}
		
		/* Color les tourelles lorsqu'il y'en a */
		if(!listeEstVideTourelle(listeTourelle)) {
			colorationTourelle(pRenderer, listeTourelle);
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
				case SDL_MOUSEBUTTONDOWN:
					positionClicSouris.x = eventsJeu.button.x;
					positionClicSouris.y = eventsJeu.button.y;
					ligne = 15; colone = 18;
					if (possibilitePositionnerTourelle(&positionClicSouris, tabCase, &ligne, &colone)) {
						ajouterTourelleEtPositionnement (&listeTourelle, tabCase, ligne, colone);
					}
					continue;
            	default:
                	continue;
			}
		}

		SDL_RenderPresent (pRenderer);
		
	}
/*--------------------- Fin de la boucle principale d'une partie ------------------*/

	SDL_DestroyTexture(pTextureFond);
	listeEnnemi = supprimerToutEn(&listeEnnemi);
	listeTourelle = supprimerToutTour(&listeTourelle);
	desallouerTab2D (tabCase, 15);
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
	ListeEnnemi **li = parametre;
	Ennemi *e = NULL;
	for (int i = 0; i < listeTailleEn(*li); i++) {
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
void colorationEnnemi(SDL_Renderer *pRenderer, ListeEnnemi *li) {
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
	
	for (int i = 0; i < listeTailleEn(li); i++) {
		SDL_RenderFillRect(pRenderer, &getEnnemi(li, i)->forme);
	}
}

/**
 * Fonction de callback pour le timer qui permet de créer les énnemis
 * qui arrivent par la gauche les après les autres et de définir 
 * leur position de départ
 */
Uint32 creationEnnemi(Uint32 intervalle, void *parametre) {
	ListeEnnemi **li = parametre;

	ajouterEnnemi(&(*li));
	definirEnnemiListe(*li, 0, VIE_ENNEMI_1, X_DEPART_ENNEMI_1, Y_DEPART_ENNEMI_1, W_ENNEMI, H_ENNEMI);
	return intervalle;
}

/* Initialise le terrain au début de la partie */
Case **allouerTab2D (int n, int m) {
    Case **tabCase = malloc(sizeof(Case*) * n);

    for (int i = 0; i < n; i++) {
        tabCase[i] = malloc(sizeof(Case) * m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tabCase[i][j].occupationEmplacement = false;
			tabCase[i][j].emplacementInterdi = false;
			tabCase[i][j].position.x = j*64;
			tabCase[i][j].position.y = i*64;
			tabCase[i][j].position.w = 64;
			tabCase[i][j].position.h = 64;
        }
    }

	tabCase[4][0].emplacementInterdi = true; tabCase[4][1].emplacementInterdi = true; tabCase[4][2].emplacementInterdi = true;
	tabCase[4][3].emplacementInterdi = true; tabCase[4][4].emplacementInterdi = true; tabCase[4][5].emplacementInterdi = true; 
	tabCase[4][6].emplacementInterdi = true; tabCase[5][6].emplacementInterdi = true; tabCase[6][6].emplacementInterdi = true;
	tabCase[7][6].emplacementInterdi = true; tabCase[8][6].emplacementInterdi = true; tabCase[9][6].emplacementInterdi = true;
	tabCase[9][7].emplacementInterdi = true; tabCase[9][8].emplacementInterdi = true; tabCase[9][9].emplacementInterdi = true; 
	tabCase[8][9].emplacementInterdi = true; tabCase[7][9].emplacementInterdi = true; tabCase[7][10].emplacementInterdi = true;
	tabCase[7][11].emplacementInterdi = true; tabCase[7][12].emplacementInterdi = true; tabCase[8][12].emplacementInterdi = true;
	tabCase[9][12].emplacementInterdi = true; tabCase[10][12].emplacementInterdi = true; tabCase[11][12].emplacementInterdi = true;
	tabCase[12][12].emplacementInterdi = true; tabCase[12][13].emplacementInterdi = true; tabCase[12][14].emplacementInterdi = true;
	tabCase[12][15].emplacementInterdi = true; tabCase[11][15].emplacementInterdi = true; tabCase[10][15].emplacementInterdi = true;
	tabCase[9][15].emplacementInterdi = true; tabCase[8][15].emplacementInterdi = true; tabCase[7][15].emplacementInterdi = true;
	tabCase[6][15].emplacementInterdi = true; tabCase[5][15].emplacementInterdi = true; tabCase[4][15].emplacementInterdi = true;
	tabCase[4][14].emplacementInterdi = true; tabCase[4][13].emplacementInterdi = true; tabCase[4][12].emplacementInterdi = true; 
	tabCase[4][11].emplacementInterdi = true; tabCase[4][10].emplacementInterdi = true; tabCase[3][10].emplacementInterdi = true;
	tabCase[2][10].emplacementInterdi = true; tabCase[1][10].emplacementInterdi = true; tabCase[0][10].emplacementInterdi = true;
	tabCase[10][8].emplacementInterdi = true; tabCase[11][8].emplacementInterdi = true; tabCase[12][8].emplacementInterdi = true;
	tabCase[13][8].emplacementInterdi = true; tabCase[14][8].emplacementInterdi = true; tabCase[14][7].emplacementInterdi = true;
	tabCase[14][9].emplacementInterdi = true;

    return tabCase;
}

/* Libère la mémoire à la fin de la partie */
void desallouerTab2D(Case **tab, int n) {
    for (int i = 0; i < n; i++) {
        free(tab[i]);
    }

    free(tab);
}

/** 
 * Permet de savoir si il y a la possibilité de placer une tourelle;
 * impossible de placer une tourelle sur un chemin, sur la bases ou si il y'a déjà une tourelle
 * @param point pointeur sur le clic la position du clic de la souris
 * @param tab tableau représentant la surface de la carte
 * @param n correspond au début au nombre de ligne et à la fin à l'index de la case
 * @param m correspond au début au nombre de colone et à la fin à l'index de la case
 */
Bool possibilitePositionnerTourelle (SDL_Point *point, Case **tab, int *n, int *m) {
	Bool trouve = false;
	int i = 0;
	int j = 0;
	SDL_bool b = SDL_FALSE;

	while (i < *n && !trouve) {
		j = 0;
		while (j < *m && !trouve) {
			if (SDL_PointInRect(point, &tab[i][j].position)) {
				trouve = true;
				i--;
				j--;
			}
			j++;
		}
		i++;
	}

	*n = i;
	*m = j;

	if (tab[i][j].emplacementInterdi == true) {

		return false;
	} else if (tab[i][j].occupationEmplacement == true) {
		return false;
	} else {

		return true;
	}
}

void ajouterTourelleEtPositionnement (ListeTourelle **li, Case **tab, int n, int m) {
	ajouterTourelle(&(*li));
	(*li)->tourelle.forme.x = tab[n][m].position.x + 15;
	(*li)->tourelle.forme.y = tab[n][m].position.y + 15;
	(*li)->tourelle.forme.w = 34;
	(*li)->tourelle.forme.h = 34;
}

/**
 * Permet de colorer toutes les tourelles qui sont dans une liste
 */
void colorationTourelle(SDL_Renderer *pRenderer, ListeTourelle *li) {
	SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);
	
	for (int i = 0; i < listeTailleTour(li); i++) {
		SDL_RenderFillRect(pRenderer, &getTourelle(li, i)->forme);
	}
}
