#include "main.h"
/* https://github.com/Esr0g/ProjetL2Info.git */

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;

    /* Initialisation de la SDL*/
    if (SDL_Init (SDL_INIT_VIDEO) != 0) {
        SDL_Log ("ERREUR: Initialisation SDL > %s\n", SDL_GetError());

        exit(EXIT_FAILURE);
    }

    /* Creation de la fenêtre*/
    pWindow = SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FENETRE_LARGEUR, FENETRE_HAUTEUR, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("ERREUR: Creation de la fenêtre > %s\n", SDL_GetError());

        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /*Créationdu Rendu*/
    pRenderer = SDL_CreateRenderer (pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL) {
        SDL_Log("ERREUR: Creation du Rendu > %s\n", SDL_GetError());

        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /*Chargement du Menu*/
    SDL_Surface *pMenu = SDL_LoadBMP ("textures/Menu.bmp");
    if (pMenu == NULL) {
        SDL_Log("ERREUR: Chargement de l'image > %s\n", SDL_GetError());

        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture *pTextureMenu = SDL_CreateTextureFromSurface(pRenderer, pMenu);
    if (pTextureMenu == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'une image > %s\n", SDL_GetError());

        SDL_FreeSurface(pMenu);
        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(pMenu);

    SDL_bool program_launched = SDL_TRUE;

/* ---------------------------------------------- Boucle principale ---------------------------------------------*/
    while (program_launched) {
        SDL_Event events;

        SDL_RenderCopy(pRenderer, pTextureMenu, NULL, NULL);
        SDL_RenderPresent (pRenderer);

        SDL_WaitEvent(&events);
        switch (events.type) {
            case SDL_KEYDOWN:
                switch (events.key.keysym.sym) {
                    case SDLK_1:
                     /*Ajouter la fonction jouer*/
                        continue;
                    case SDLK_ESCAPE:
                        program_launched = SDL_FALSE;
                        break;
                    case SDLK_q:
                        program_launched = SDL_FALSE;
                        break;
                    default:
                        continue;
                }
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            default:
                continue;
        }
    }

/*-------------------------------------- Fin de la boucle principale --------------------------------------------*/

    SDL_DestroyTexture(pTextureMenu);
    SDL_DestroyWindow (pWindow);
    SDL_DestroyRenderer (pRenderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
