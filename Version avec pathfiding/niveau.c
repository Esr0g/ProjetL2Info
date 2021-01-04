//INCLUDE STANDAR
#include <stdlib.h>
#include <stdio.h>
//INCLUDE PROJET
#include "map.h"
//#include "niveau.h"
void map_niveau_1();

//DEFINE
#define HAUTEUR_NIVEAU_1 15
#define LARGEUR_NIVEAU_1 18


/**
 * Methode qui crée le niveau1 du jeu TowerDefense
 */
void map_niveau_1(){
	int** tab =tableau_map_new(HAUTEUR_NIVEAU_1 , LARGEUR_NIVEAU_1);

	// ---Placement a la main de la route
	tab[4][0]='1';   tab[4][1]='1';   tab[4][2]='1';
	tab[4][3]='1';   tab[4][4]='1';   tab[4][5]='1'; 
	tab[4][6]='1';   tab[5][6]='1';   tab[6][6]='1';
	tab[7][6]='1';   tab[8][6]='1';   tab[9][6]='1';
	tab[9][7]='1';   tab[9][8]='1';   tab[9][9]='1'; 
	tab[8][9]='1';   tab[7][9]='1';   tab[7][10]='1';
	tab[7][11]='1';  tab[7][12]='1';  tab[8][12]='1';
	tab[9][12]='1';  tab[10][12]='1'; tab[11][12]='1';
	tab[12][12]='1'; tab[12][13]='1'; tab[12][14]='1';
	tab[12][15]='1'; tab[11][15]='1'; tab[10][15]='1';
	tab[9][15]='1';  tab[8][15]='1';  tab[7][15]='1';
	tab[6][15]='1';  tab[5][15]='1';  tab[4][15]='1';
	tab[4][14]='1';  tab[4][13]='1';  tab[4][12]='1'; 
	tab[4][11]='1';  tab[4][10]='1';  tab[3][10]='1';
	tab[2][10]='1';  tab[1][10]='1';  tab[0][10]='1';
	tab[10][8]='1';  tab[11][8]='1';  tab[12][8]='1';
	tab[13][8]='1';  tab[14][8]='1';  tab[14][7]='1';
	tab[14][9]='1';

	//conversion tableau en map
	map_new("niveau/niveau_1", HAUTEUR_NIVEAU_1, LARGEUR_NIVEAU_1);// creation des fichier
	map_from_tableau("niveau/niveau_1", tab);//mise en forme des fichier
}		






/*------------------------------------------------------------------------------------------*/
/*                               QUELQUE TEST                                               */
/*------------------------------------------------------------------------------------------*/
/*
int main(int argc, char const *argv[]){
	map_niveau_1(HAUTEUR, LARGEUR);

	return EXIT_SUCCESS;
}
*/