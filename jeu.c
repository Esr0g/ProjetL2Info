#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct Ennemis1 Ennemis1;
struct Ennemis1
{
    int vie; 
	
	
	int getVie(void)
	{
		return vie;
	}		
};


typedef struct Base Base;
struct Base
{
	int vie;
	SDL_Rect rect;
};