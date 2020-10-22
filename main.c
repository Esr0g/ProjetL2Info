#include "main.h"
/* https://github.com/Esr0g/ProjetL2Info.git */

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;

    if (SDL_Init (SDL_INIT_VIDEO) != 0) {
        SDL_Log ("ERREUR: Initialisation SDL > %s\n", SDL_GetError());

        exit(EXIT_FAILURE);
    }

    pWindow = SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FENETRE_LARGEUR, FENETRE_HAUTEUR, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("ERREUR: Creation de la fenêtre > %s\n", SDL_GetError());

        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    pRenderer = SDL_CreateRenderer (pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL) {
        SDL_Log("ERREUR: Creation du Rendu > %s\n", SDL_GetError());

        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Surface *image = SDL_LoadBMP ("textures/Terrain.bmp");
    if (image == NULL) {
        SDL_Log("ERREUR: Chargement de l'image > %s\n", SDL_GetError());

        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture *pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);
    if (pTextureImage == NULL) {
        SDL_Log("ERREUR: Creation du rendu à partir d'une image > %s\n", SDL_GetError());

        SDL_FreeSurface(image);
        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow (pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(image);

    SDL_bool program_launched = SDL_TRUE;

    while (program_launched) {
        SDL_Event events;

        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    continue;
            }
        }

        SDL_RenderCopy(pRenderer, pTextureImage, NULL, NULL);

        SDL_RenderPresent (pRenderer);
    }

    SDL_DestroyTexture(pTextureImage);
    SDL_DestroyWindow (pWindow);
    SDL_DestroyRenderer (pRenderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
