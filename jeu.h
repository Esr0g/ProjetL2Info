#ifndef DEF_JEU
#define DEF_JEU

void jouer(SDL_Renderer* pRenderer);

typedef struct s_Liste
{
	int val;
    List* suivant;
    void* donnee; 
}Liste;

#endif