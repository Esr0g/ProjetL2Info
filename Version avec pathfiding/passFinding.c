//classique
#include <stdlib.h>
#include <stdio.h>
//projet
#include "map.h"
#include "niveau.h"


// initialisie dynamiquement un tableau
int ** init_tab_dynamic( int x, int y){
   int i,j;
   int ** tab = malloc( x*sizeof(int*) );
   for ( i = 0; i<x; i++ )
   {
      tab[i] = malloc( y*sizeof(int) );
      for ( j = 0; j<y; j++ ){
          tab[i][j] = 1;
      }
   }
   return tab;
}

//trouve les direction du chemain 1

int** PassFinding_chemain_1(const char* nomDuFichier){
	int** tab =tableau_from_map(nomDuFichier);

	int hauteur =hauteur_from_map(nomDuFichier);
	//printf("hauteur: %d\n",hauteur );
	int largeur =largeur_from_map(nomDuFichier);
	//printf("largeur: %d\n",largeur );
	//tableau_print(tab,hauteur,largeur);

	// ---- Creation du cheamin a suivre
	//int sur_chemain_1[4][0];//depart
	int x_ch =4;   int y_ch=0; //là où on est sur le chemain et valeur depart chemain 1
	//int arriver_chemain[14][8]; 
	int ariv_chemain =0;
	int x_ar =14; int y_ar=8;

	int** chemain_1 =init_tab_dynamic(30, 2);
	//int chemain_1[30][2];//[X] numero du croisement [][Y1] direction 1 2 3 4 pour prochain chemain
													//[Y2] nb pas dans cette direction pour prochain chemain
	//1:Bas 2:droit 3:gauche 4:haut
	chemain_1[0][0] =2;
	//printf("chemain: %d direction: %d\n",0, chemain_1[0][0] );

	int nb_croisement =0; int longueur_chemain =0; int nouveau_croisement=0;

	while(! ariv_chemain){
		nouveau_croisement=0;
		longueur_chemain =0;
		while(! nouveau_croisement){
			//printf("pas: %d\n",chemain_1[nb_croisement][1] );
			//if(x_ch ==4 && y_ch ==2){
			//	// ---- A completer
			//}
			//pr ne pas regarder au dela de la map && x_ch >hauteur
			if(tab[x_ch][y_ch] == tab[x_ch +1][y_ch] && x_ch <hauteur){//on regarde vers le BAS si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 1){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =1;
					//tab[x_ch][y_ch] ='#';
				}
				else if(chemain_1[nb_croisement][0] == 1){//c'est qu'on continue a aller vers le BAS
					longueur_chemain++;
					x_ch++;//on avance sur 1 case en BAS
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch -1][y_ch] ='B';// Block la case pour ne pas revenir dessus
					//print_chemain(tab);
					//tableau_print(tab,15,18);
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch][y_ch +1] && y_ch <largeur){//on regarde vers la DROITE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 2){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =2;
				}
				else if(chemain_1[nb_croisement][0] == 2){//c'est qu'on continue a aller vers la DROITE
					longueur_chemain++;
					y_ch++;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch][y_ch -1] ='B';// Block la case pour ne pas revenir dessus
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch ][y_ch-1] && y_ch >0){//on regarde vers la GAUCHE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 3){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =3;
				}
				else if(chemain_1[nb_croisement][0] == 3){//c'est qu'on continue a aller vers la GAUCHE
					longueur_chemain++;
					y_ch--;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch][y_ch +1] ='B';// Block la case pour ne pas revenir dessus
				}	
			}
			else if(tab[x_ch][y_ch] == tab[x_ch -1][y_ch] && x_ch >0){//on regarde vers le HAUT si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 4){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =4;
				}
				else if(chemain_1[nb_croisement][0] == 4){//c'est qu'on continue a aller vers le HAUT
					longueur_chemain++;
					x_ch--;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch +1][y_ch] ='B';// Block la case pour ne pas revenir dessus
				}
			}
		}
	}
	free(tab);
	return chemain_1;
}
/*
int** PassFinding_chemain_1(const char* nomDuFichier){
	int** tab =tableau_from_map(nomDuFichier);

	int hauteur =hauteur_from_map(nomDuFichier);
	//printf("hauteur: %d\n",hauteur );
	int largeur =largeur_from_map(nomDuFichier);
	//printf("largeur: %d\n",largeur );
	//tableau_print(tab,hauteur,largeur);

	// ---- Creation du cheamin a suivre
	//int sur_chemain_1[4][0];//depart
	int x_ch =4;   int y_ch=0; //là où on est sur le chemain et valeur depart chemain 1
	//int arriver_chemain[14][8]; 
	int ariv_chemain =0;
	int x_ar =14; int y_ar=8;

	int** chemain_1 =init_tab_dynamic(30, 2);
	//int chemain_1[30][2];//[X] numero du croisement [][Y1] direction 1 2 3 4 pour prochain chemain
													//[Y2] nb pas dans cette direction pour prochain chemain
	//1:Bas 2:droit 3:gauche 4:haut
	chemain_1[0][0] =2;
	//printf("chemain: %d direction: %d\n",0, chemain_1[0][0] );

	int nb_croisement =0; int longueur_chemain =0; int nouveau_croisement=0;

	while(! ariv_chemain){
		nouveau_croisement=0;
		longueur_chemain =0;
		while(! nouveau_croisement){
			//printf("pas: %d\n",chemain_1[nb_croisement][1] );
			//if(x_ch ==4 && y_ch ==2){
			//	// ---- A completer
			//}
			//pr ne pas regarder au dela de la map && x_ch >hauteur
			if(tab[x_ch][y_ch] == tab[x_ch +1][y_ch] && x_ch <hauteur){//on regarde vers le BAS si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 1){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =1;
				}
				else if(chemain_1[nb_croisement][0] == 1){//c'est qu'on continue a aller vers le BAS
					longueur_chemain++;
					x_ch++;//on avance sur 1 case en BAS
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch][y_ch +1] && y_ch <largeur){//on regarde vers la DROITE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 2){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =2;
				}
				else if(chemain_1[nb_croisement][0] == 2){//c'est qu'on continue a aller vers la DROITE
					longueur_chemain++;
					y_ch++;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch ][y_ch-1] && y_ch >0){//on regarde vers la GAUCHE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 3){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =3;
				}
				else if(chemain_1[nb_croisement][0] == 3){//c'est qu'on continue a aller vers la GAUCHE
					longueur_chemain++;
					y_ch--;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
				}	
			}
			else if(tab[x_ch][y_ch] == tab[x_ch -1][y_ch] && x_ch >0){//on regarde vers le HAUT si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_1[nb_croisement][0] != 4){// veut dire qu'on est sur un nouelle embranchement
					chemain_1[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_1[nb_croisement][0] =4;
				}
				else if(chemain_1[nb_croisement][0] == 4){//c'est qu'on continue a aller vers le HAUT
					longueur_chemain++;
					y_ch++;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_1[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
				}
			}
		}
	}
	free(tab);
	return chemain_1;
}
*/

//trouve les direction du chemain 2
int** PassFinding_chemain_2(const char* nomDuFichier){
	int** tab =tableau_from_map(nomDuFichier);

	int hauteur =hauteur_from_map(nomDuFichier);
	//printf("hauteur: %d\n",hauteur );
	int largeur =largeur_from_map(nomDuFichier);
	//printf("largeur: %d\n",largeur );
	//tableau_print(tab,hauteur,largeur);

	// ---- Creation du cheamin a suivre
	//int sur_chemain_2[0][10];//depart

	int x_ch =0;   int y_ch=10; //là où on est sur le chemain et valeur depart chemain 1
	//printf("debut: %c\n",tab[0][10] );// on est bien sur un A
	//int arriver_chemain[14][8]; 
	int ariv_chemain =0;
	int x_ar =14; int y_ar=8;

	int** chemain_2 =init_tab_dynamic(30, 2);
	//int chemain_2[30][2];//[X] numero du croisement [][Y1] direction 1 2 3 4 pour prochain chemain
													//[Y2] nb pas dans cette direction pour prochain chemain
	//1:Bas 2:droit 3:gauche 4:haut
	chemain_2[0][0] =1;
	//printf("chemain: %d direction: %d\n",0, chemain_2[0][0] );

	int nb_croisement =0; int longueur_chemain =0; int nouveau_croisement=0;

	while(! ariv_chemain){
		nouveau_croisement=0;
		longueur_chemain =0;
		while(! nouveau_croisement){
			//tableau_print(tab,15,18);
			//print_chemain(chemain_2);
			//pr ne pas regarder au dela de la map && x_ch >hauteur
			if(tab[x_ch][y_ch] == tab[x_ch +1][y_ch] && x_ch <hauteur){//on regarde vers le BAS si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_2[nb_croisement][0] != 1){// veut dire qu'on est sur un nouelle embranchement
					chemain_2[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_2[nb_croisement][0] =1;
				}
				else if(chemain_2[nb_croisement][0] == 1){//c'est qu'on continue a aller vers le BAS
					longueur_chemain++;
					x_ch++;//on avance sur 1 case en BAS
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_2[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch -1][y_ch] ='B';// Block la case pour ne pas revenir dessus
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch ][y_ch-1] && y_ch >0){//on regarde vers la GAUCHE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_2[nb_croisement][0] != 3){// veut dire qu'on est sur un nouelle embranchement
					chemain_2[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_2[nb_croisement][0] =3;
				}
				else if(chemain_2[nb_croisement][0] == 3){//c'est qu'on continue a aller vers la GAUCHE
					longueur_chemain++;
					y_ch--;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_2[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch][y_ch +1] ='B';// Block la case pour ne pas revenir dessus
				}	
			}
			else if(tab[x_ch][y_ch] == tab[x_ch -1][y_ch] && x_ch >0){//on regarde vers le HAUT si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_2[nb_croisement][0] != 4){// veut dire cqu'on est sur un nouelle embranchement
					chemain_2[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_2[nb_croisement][0] =4;
				}
				else if(chemain_2[nb_croisement][0] == 4){//c'est qu'on continue a aller vers le HAUT
					longueur_chemain++;
					x_ch--;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_2[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch +1][y_ch] ='B';// Block la case pour ne pas revenir dessus
					//tableau_print(tab,15,18);
				}
			}
			else if(tab[x_ch][y_ch] == tab[x_ch][y_ch +1] && y_ch <largeur){//on regarde vers la DROITE si il y a un chemain
															//si  la case d'apres est aussi une case chemain
				if(chemain_2[nb_croisement][0] != 2){// veut dire qu'on est sur un nouelle embranchement
					chemain_2[nb_croisement][1] =longueur_chemain;
					nb_croisement++;
					nouveau_croisement =1;
					chemain_2[nb_croisement][0] =2;
				}
				else if(chemain_2[nb_croisement][0] == 2){//c'est qu'on continue a aller vers la DROITE
					longueur_chemain++;
					y_ch++;//on avance sur 1 case en DROITE
					if(x_ch ==x_ar && y_ch ==y_ar){//si notre postion est sur l'arrivé
						chemain_2[nb_croisement][1] =longueur_chemain;
						ariv_chemain =1;
						nouveau_croisement =1;//pour stop la boucle  while(! nouveau_croisement)
					}
					tab[x_ch ][y_ch -1] ='B';// Block la case pour ne pas revenir dessus
				}
			}
		}
	}
	//tableau_print(tab,15,18);
	free(tab);

	return chemain_2;
}

//affiche le chemain
void print_chemain(int** chemain){
	for(int i=0;i<30;i++){
		if(chemain[i][0] ==1){
			printf("BAS : %d pas\n",chemain[i][1] );
		}
		else if(chemain[i][0] ==2){
			printf("Drt : %d pas\n",chemain[i][1] );
		}
		else if(chemain[i][0] ==3){
			printf("Gch : %d pas\n",chemain[i][1] );
		}
		else if(chemain[i][0] ==4){
			printf("Ho  : %d pas\n",chemain[i][1] );
		}	
	}
}

/*
int main(){
	int** tab;
	
	tab= PassFinding_chemain_1("niveau/niveau_1");	
	print_chemain(tab);
	printf("PassFinding executé\n" );
	return 0;
}
*/