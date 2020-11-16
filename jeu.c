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

void jouer(SDL_Renderer* pRenderer, SDL_bool *programLaunched) {

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

	/* Initialisation de la base */
	Base base01; base01.base.h = 64; base01.base.w = 128 ; base01.base.x = 448; base01.base.y = 896; base01.vie = 3;
	
	
	ListeEnnemi *listeEnnemi = NULL; // initialisation de la liste d'ennemis
	int nbEnnemi = 5; // nombre d'ennmis choisi

	ListeTourelle *listeTourelle = NULL; // initialisation de la liste de tourelle

	/* Initialisation des cases du jeu */
	Cases **tabCase = allouerTab2D (15, 18);
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

	/*Recupère la position de la souris ou la position du clic de la souris */
	SDL_Point positionClicSouris;
	SDL_Point positionSouri;

	/* Initialisation du texte*/
	TTF_Font* font = TTF_OpenFont("textures/design.collection2.toontiei.ttf", 25);
	if (font == NULL) {
		//Creation de l'erreur ?
		  SDL_Log("ERREUR: Creation de la police à partir d'une d'un fichier  > %s\n", TTF_GetError());
	}
	
	SDL_Rect positionTexteVie;
    SDL_Color maCouleurNoir = {0, 0, 0, 255};
	

	char strTexteVie[100]   =   "Vie : " ;
	char strNbVie[10];
	sprintf(strNbVie, "%d", base01.vie); //convertit la vie de la base (int) en char[] 
	strcat(strTexteVie,strNbVie); //concaténe les 2 chaines de caractères 

	
    SDL_Surface *police = TTF_RenderText_Blended(font, strTexteVie, maCouleurNoir); 
	if (police == NULL) {
		//Creation de l'erreur ?
		  SDL_Log("ERREUR: Creation de la surface du texte > %s\n", TTF_GetError());
	}
	
    SDL_Texture *textureTexteVie = SDL_CreateTextureFromSurface(pRenderer, police);
	if (textureTexteVie == NULL) {
		//Creation de l'erreur ?
		  SDL_Log("ERREUR: Creation de la texture a partir de la surface du texte > %s\n", TTF_GetError());
	}
	
    SDL_QueryTexture(textureTexteVie, NULL, NULL, &positionTexteVie.w, &positionTexteVie.h);

    positionTexteVie.x = FENETRE_LARGEUR  - positionTexteVie.w -100;
    positionTexteVie.y = 0;
	//FENETRE_HAUTEUR / 2 - positionTexteVie.h / 2;

    SDL_FreeSurface(police);
    TTF_CloseFont(font);
	
	/* Recupère le numero de la tourelle dans la liste pour afficher ça range */
	int indexTourelle = 0;

	/* Initialisation de quelques données concernant la partie */
	int killTotal = 0;
	int score = 0;
	// int argent = 400;

/*---------------------------------------------------- Boucle principale d'une partie ----------------------------------------------------------------*/
	while (partieContinuer && programLaunched) {
		SDL_Event eventsJeu;
		 
		SDL_RenderCopy(pRenderer, pTextureFond, NULL, NULL);

		/* Active le timer de spawn si il n'est pas activé*/
		if (!initialisationListeEnnemiBool) {
			initialisationListeEnnemi = SDL_AddTimer((VITESSE_DEPLACEMENT_ENNEMI * (TAILLE_ENNEMI + 20)), creationEnnemi, &listeEnnemi);
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
		} else if (listeTailleEn(listeEnnemi) == 0 && mouvementEnnemiBool) {
			SDL_RemoveTimer(mouvementEnnemi);
		}

		/** Supprime un ennemi lorsqu'il rentre en collision avec la base ou lorsque ses point de vie atteigent 0*/
		if (!listeEstVideEnnemi(listeEnnemi)) {
			for (int i = 0; i < listeTailleEn(listeEnnemi); i++) {
				if (SDL_HasIntersection(&getEnnemi(listeEnnemi, i)->forme, &base01.base)) {
					supprimerEnnemi(&listeEnnemi, i);
					base01.vie--;
				} else if (getEnnemi(listeEnnemi, i)->vie <= 0) {
					supprimerEnnemi(&listeEnnemi, i);
					killTotal++;
				}
			}
		}

		limite = SDL_GetTicks() + FPS_LIMITE;

		/* Color les cerlces lorsque la souri est dessus */
		if (souriSurTourelle(&positionSouri, listeTourelle, &indexTourelle)) {
			filledCircleRGBA (pRenderer, getTourelle(listeTourelle, indexTourelle)->range.x, 
								getTourelle(listeTourelle, indexTourelle)->range.y, 
								getTourelle(listeTourelle, indexTourelle)->range.rayon,
								149, 126, 118, 100);
		}

		/* Color les énnemis lorsqu'il y'en a */
		limiteFPS(limite);
		if (!listeEstVideEnnemi(listeEnnemi)) {
			colorationEnnemi(pRenderer, listeEnnemi);
		}

		/* Color les tourelles lorsqu'il y'en a */
		if(!listeEstVideTourelle(listeTourelle)) {
			colorationTourelle(pRenderer, listeTourelle);
		}

		/* Attaque des ennemis par les tourelles */
		if (!listeEstVideEnnemi(listeEnnemi) && !listeEstVideTourelle(listeTourelle)) {
			attaqueEnnemi (listeEnnemi, listeTourelle);
		}

		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		//mettre a jour puis afficher le texte 
		
        SDL_RenderCopy(pRenderer, textureTexteVie, NULL, &positionTexteVie);

		/* Lorsque les points de vie de la base atteignent 0, la partie est perdu */
		if (base01.vie <= 0) {
			menuDefaite(pRenderer, &partieContinuer, programLaunched);
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
					break;
				case SDL_MOUSEBUTTONDOWN:
					positionClicSouris.x = eventsJeu.button.x;
					positionClicSouris.y = eventsJeu.button.y;
					ligne = 15; colone = 18;
					if (possibilitePositionnerTourelle(&positionClicSouris, tabCase, &ligne, &colone)) {
						ajouterTourelleEtPositionnement (&listeTourelle, tabCase, ligne, colone);
					}
					break;
				case SDL_MOUSEMOTION:
					positionSouri.x = eventsJeu.motion.x;
					positionSouri.y = eventsJeu.motion.y;
					break;
            	default:
                	break;
			}
		}

		SDL_RenderPresent (pRenderer);
		
	}
/*-------------------------------------------------------- Fin de la boucle principale d'une partie ------------------------------------------------------*/

	SDL_DestroyTexture(pTextureFond);
	SDL_DestroyTexture(textureTexteVie);
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

	for (int i = 0; i < listeTailleEn(li); i++) {
				boxRGBA(pRenderer, getEnnemi(li, i)->forme.x + TAILLE_ENNEMI, 
				getEnnemi(li, i)->forme.y, 
				getEnnemi(li, i)->forme.x, 
				getEnnemi(li, i)->forme.y + TAILLE_ENNEMI,
				 0, 0, 0, 255 );
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
	definirEnnemiListe(*li, 0, VIE_ENNEMI_1, -TAILLE_ENNEMI, Y_DEPART_ENNEMI_1 + ((64 - TAILLE_ENNEMI)/2) , TAILLE_ENNEMI, TAILLE_ENNEMI);
	return intervalle;
}

/* Initialise le terrain au début de la partie */
Cases **allouerTab2D (int n, int m) {
    Cases **tabCase = malloc(sizeof(Cases*) * n);

    for (int i = 0; i < n; i++) {
        tabCase[i] = malloc(sizeof(Cases) * m);
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
void desallouerTab2D(Cases **tab, int n) {
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
Bool possibilitePositionnerTourelle (SDL_Point *point, Cases **tab, int *n, int *m) {
	Bool trouve = false;
	int i = 0;
	int j = 0;

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

/**
 * Permet d'ajouter les tourelles à la position du clic et de les initialiser avec leur valeur de départ
 */
void ajouterTourelleEtPositionnement (ListeTourelle **li, Cases **tab, int n, int m) {
	ajouterTourelle(&(*li));
	(*li)->tourelle.forme.x = tab[n][m].position.x + ((64 - TAILLE_TOURELLE )/2);
	(*li)->tourelle.forme.y = tab[n][m].position.y + ((64 - TAILLE_TOURELLE)/2);
	(*li)->tourelle.forme.w = TAILLE_TOURELLE;
	(*li)->tourelle.forme.h = TAILLE_TOURELLE;
	(*li)->tourelle.range.x = tab[n][m].position.x + 32;
	(*li)->tourelle.range.y = tab[n][m].position.y + 32;
	(*li)->tourelle.range.rayon = RAYON_DEPART_TOURELLE;
	(*li)->tourelle.degats = 30;
	(*li)->tourelle.vitesseAttaque = VITESSE_D_ATTAQUE_TOURELLE_DEPART;
	(*li)->tourelle.tpsEntre2Tire = SDL_GetTicks();
	
	tab[n][m].occupationEmplacement = true;

}

/**
 * Permet de colorer toutes les tourelles qui sont dans une liste
 */
void colorationTourelle(SDL_Renderer *pRenderer, ListeTourelle *li) {
	
	for (int i = 0; i < listeTailleTour(li); i++) {
		boxRGBA(pRenderer, getTourelle(li, i)->forme.x + TAILLE_TOURELLE, 
				getTourelle(li, i)->forme.y, 
				getTourelle(li, i)->forme.x, 
				getTourelle(li, i)->forme.y + TAILLE_TOURELLE,
				 0, 255, 0, 255 );
	}
}

/**
 * Renvoi un boolean pour savoir si la souris est sur une tourelle
 * Retourne aussi l'index de la tourelle
 */
Bool souriSurTourelle(SDL_Point *p, ListeTourelle *li, int *tourelle) {
	Bool souriToucheTourelle =  false;
	int i = 0;

	if (!listeEstVideTourelle(li)) {
		while (i < listeTailleTour(li) && !souriToucheTourelle) {
			if (SDL_PointInRect(p, &getTourelle(li, i)->forme)) {
				souriToucheTourelle = true;
			} else {
				i++;
			}
		}
	}
	
	*tourelle = i;

	return souriToucheTourelle;
}

/*-----------------------------------------------------------------Collision cercle - Rectangle ------------------------------------------------------*/

/**
 * Colision entre un point et un cercle
 * source: http://sdz.tdct.org/sdz/eorie-des-collisions.html
 */
Bool collisionPointCercle(int x, int y, Cercle C) {
   int d2 = (x-C.x)*(x-C.x) + (y-C.y)*(y-C.y);

   if (d2>C.rayon*C.rayon) {

      return false;
   } else {

      return true;
   }
}

/**
 * Permet de vérifier un des cas de colision avec un cercle
 * source : http://sdz.tdct.org/sdz/eorie-des-collisions.html
 */
int projectionSurSegment(int Cx,int Cy,int Ax,int Ay,int Bx,int By) {
   int ACx = Cx-Ax;
   int ACy = Cy-Ay; 
   int ABx = Bx-Ax;
   int ABy = By-Ay; 
   int BCx = Cx-Bx;
   int BCy = Cy-By; 
   int s1 = (ACx*ABx) + (ACy*ABy);
   int s2 = (BCx*ABx) + (BCy*ABy); 

   if (s1*s2>0) {

    return 0;
   }

   return 1;
}

/**
 * Renvoie true si il y'a une collision entre un cercle et un rectangle
 * source: http://sdz.tdct.org/sdz/eorie-des-collisions.html
 */
Bool collisionCercleRectangle(Cercle C1, SDL_Rect box1) {

   SDL_Rect boxCercle;
   boxCercle.h = C1.rayon * 2;
   boxCercle.w = C1.rayon * 2;
   boxCercle.x = C1.x - C1.rayon;
   boxCercle.y = C1.y - C1.rayon;
   SDL_Point p;
   p.x = C1.x;
   p.y = C1.y;

   if (SDL_HasIntersection(&box1, &boxCercle) == 0) {

    	return false;
   }

   if (collisionPointCercle(box1.x,box1.y,C1)==1
    || collisionPointCercle(box1.x,box1.y+box1.h,C1)==1
    || collisionPointCercle(box1.x+box1.w,box1.y,C1)==1
    || collisionPointCercle(box1.x+box1.w,box1.y+box1.h,C1)==1) {

    	return true;
	}

   if (SDL_PointInRect(&p, &box1)) {

		return true;
   }

   int projvertical = projectionSurSegment(C1.x,C1.y,box1.x,box1.y,box1.x,box1.y+box1.h);
   int projhorizontal = projectionSurSegment(C1.x,C1.y,box1.x,box1.y,box1.x+box1.w,box1.y); 

   if (projvertical==1 || projhorizontal==1) {

    	return true; 
   }

   return false; 
}

/*-----------------------------------------------------------------Fin collision cercle - Rectangle ------------------------------------------------------*/

/**
 * Les tourelles attaque les ennemis en fonction de leur vitesse d'attaque
 */
void attaqueEnnemi (ListeEnnemi *le, ListeTourelle *lt) {
	int tempsAuTick = SDL_GetTicks();
	Bool collision = false;
	int j = 0;

	for (int i = 0; i < listeTailleTour(lt); i++) {
		j = 0;

		while (j < listeTailleEn(le) && !collision) {

			if (collisionCercleRectangle (getTourelle(lt, i)->range, getEnnemi(le, j)->forme)) {
				if ((tempsAuTick - getTourelle(lt, i)->tpsEntre2Tire) > getTourelle(lt, i)->vitesseAttaque) {
					getEnnemi(le, j)->vie = getEnnemi(le, j)->vie - getTourelle(lt, i)->degats;
					printf ("ennemi: %d, vie: %d\n", j, getEnnemi(le, j)->vie);
					getTourelle(lt, i)->tpsEntre2Tire = SDL_GetTicks();
				}
				collision = true;
			} else {
				j++;
			}
		}	
	}
}
