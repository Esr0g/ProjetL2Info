/*
char *n = "123";
int nombre = atoi(n);
//nombre vaut 123
 
//par contre
char *nimp = "salut";
int nawak = atoi(nimp);

//strlen( const char * theString );

https://waytolearnx.com/2019/08/concatener-des-chaines-de-caracteres-en-c.html
*/

//INCLUDE STANDAR
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//INCLUDE PROJET
#include "map.h"

//DEFINE
//#define HAUTEUR 20
//#define LARGEUR 50


/**
 * Methode qui cree un nouveau fichier text d'une map de TowerDefense vierge
 * @param nomDuFichier, le nom a donner a la nouvelle map
 * @param largeur, la largeur de la futur map
 * @param hauteur, la hauteur de la futur map
 */
void map_new(const char* nomDuFichier, int hauteur, int largeur){
	// --- Creation d'un tableau 2D qui symbolise une map vierge
	int** tabMap =tableau_map_new(hauteur, largeur);
	

	// ---- Attribution des noms des futur fichiers .txt
	//* Initialisation des chaine de charcarteres
	char nomDuFichier_et_extention[100];
	char nomDuFichier_et_valeur[100];
	char extention_txt[] = ".txt";
	char extention_valeur_txt[] = "_valeur.txt";
	//* Attribution des chaines de charcteres
	strcpy(nomDuFichier_et_extention, nomDuFichier);
	strcat(nomDuFichier_et_extention, extention_txt);
	strcpy(nomDuFichier_et_valeur, nomDuFichier);
	strcat(nomDuFichier_et_valeur, extention_valeur_txt);

	// ---- Creation des fichier
	FILE* map =fopen(nomDuFichier_et_extention, "w+");
	if (map ==NULL){
		printf("fonction: map_new ERROR\n");
		printf("erreur: map ==fopen\n");
		exit(1);
	}fclose(map);
	FILE* map_valeur =fopen(nomDuFichier_et_valeur, "w+");
	if (map ==NULL){
		printf("fonction: map_new ERROR\n");
		printf("erreur: map_valeur==fopen\n");
		exit(1);
	}
	fprintf(map_valeur, "%d\n%d", hauteur, largeur );
	fclose(map_valeur);

	// ---- Transformation du tableau 2D tabMap en fichier texte
	map_from_tableau(nomDuFichier, tabMap);
	
	// ---- Libération mémoire tabMap
	tableau_2dimensions_free(tabMap, hauteur);
}

/**
 * Methode qui transforme une tabMap 2D en son équivalent map.txt
 * @param nomDuFichier, le  futur nom du .txt
 * @param tabMap, le tableau 2D qui contien la futur map
 * @param largeur, la largeur de la map
 * @param hauteur, la hauteur de la map
 */
void map_from_tableau(const char* nomDuFichier, int**tabMap){

	// ---- Attribution nom fichier
	//* Initialisation des chaine de charcarteres
	char nomDuFichier_et_extention[100];
	char nomDuFichier_et_valeur[100];
	char extention_txt[] = ".txt";
	char extention_valeur_txt[100] = "_valeur.txt";
	//* Attribution des chaines de charcteres
	strcpy(nomDuFichier_et_extention, nomDuFichier);
	strcat(nomDuFichier_et_extention, extention_txt);
	strcpy(nomDuFichier_et_valeur, nomDuFichier);
	strcat(nomDuFichier_et_valeur, extention_valeur_txt);

	// --- Ouverture du fichier en écriture
	FILE* map =fopen(nomDuFichier_et_extention, "w+");
	if (map ==NULL){
			printf("fonction: map_from_tableau ERROR\n");
			printf("erreur: map==fopen\n");
			exit(1);
	}
	FILE* map_valeur = fopen(nomDuFichier_et_valeur, "r");
	if(map_valeur ==NULL){
		printf("fonction: map_from_tableau ERROR\n");
		printf("erreur: map_valeur==fopen\n");
		exit(1);
	}

	int hauteur;
	int largeur;
	fscanf(map_valeur,"%d",&hauteur );
	printf("hauteur: %d\n",hauteur );
	fscanf(map_valeur,"%d",&largeur );
	printf("largeur: %d\n",largeur );
	/* Test: ca fonctionne

	FILE* file = fopen("file.txt", "r");
	if(file ==NULL){
		printf("sa a pas alloué pd\n" );
		exit(1);
	}
	int hauteur =1;
	int largeur =2;
	fscanf(file,"%d", &hauteur);
	printf("hauteur: %d\n",hauteur );
	fscanf(file,"%d",&largeur);
	printf("largeur: %d\n",largeur );

	fclose(file);
	*/
	
	// --- Ecriture dans FILE* map
	// Transcription de tabMap en FILE* map
	int i,j=0;
	for (i =0; i < hauteur; ++i){
		for (j=0; j < largeur; j++){
			switch(tabMap[i][j]){
				case '0':
					fputc('#',map);
					break;
				case '1':
					fputc('A',map);
					break;
				default:
					fputc('$',map); // INDIQUE que rien n'a été reconnu
			}
		}
		fputc('\n',map);
	}

	// --- Fermeture File
	fclose(map);
	fclose(map_valeur);
}

/**
 * Methode qui cree un tableau 2Dimension a partir d'un fichier text, qui sert de map
 * @param nomDuFichier, le nom du fichier txt qui stock la map
 * @param hauteur, la hauteur de la map
 * @param largeur, la largeur de la map
 * @return tab, le tableau 2D qui est utilisé comme map du TowerDefense
 */
int** tableau_from_map(const char* nomDuFichier){

	// ---- Attribution nom fichier
	//* Initialisation des chaine de charcarteres
	char nomDuFichier_et_extention[100];
	char nomDuFichier_et_valeur[100];
	char extention_txt[] = ".txt";
	char extention_valeur_txt[100] = "_valeur.txt";
	//* Attribution des chaines de charcteres
	strcpy(nomDuFichier_et_extention, nomDuFichier);
	strcat(nomDuFichier_et_extention, extention_txt);
	strcpy(nomDuFichier_et_valeur, nomDuFichier);
	strcat(nomDuFichier_et_valeur, extention_valeur_txt);

	// --- Ouverture du fichier en lecture seul
	FILE* map =fopen(nomDuFichier_et_extention, "r");
	if (map ==NULL){
		printf("fonction: tableau_from_map ERROR\n");
		printf("erreur: map==fopen\n");
		exit(1);
	}
	FILE* map_valeur = fopen(nomDuFichier_et_valeur, "r");
	if(map_valeur ==NULL){
		printf("fonction: tableau_from_map ERROR\n");
		printf("erreur: map_valeur==fopen\n");
		exit(1);
	}

	// ---- Recuperation de la hauteur et de la largeur
	int hauteur=10;
	int largeur=10;
	fscanf(map_valeur,"%d",&hauteur );
	fscanf(map_valeur,"%d",&largeur );

	int ** tab;
	tab =tableau_map_new(hauteur, largeur); // Sécurité que chaque element du tableau soit initialisé
	

	// --- Utilisation des données de nomDuFichier.txt pour crée les données correspondante dans un tableau2D
	int i,j=0;
	for (i=0; i < hauteur; i++){ // Charactere INVALIDE si hauteur et largeur sont plus grande que celle du File (l'une ou l'autre)
			
			for (j=0; j < largeur; j++){
				tab[i][j] =fgetc(map);
				//printf("on est a:%c curseur:%ld\n",tab[i][j] ,ftell(map)); //connetre POSITION curseur
			}
			fgetc(map);
		}



	// --- Fermeture File
	fclose(map);
	fclose(map_valeur);

	return tab;
}

int hauteur_from_map(const char* nomDuFichier){

	// ---- Attribution nom fichier
	//* Initialisation des chaine de charcarteres
	char nomDuFichier_et_valeur[100];
	char extention_valeur_txt[100] = "_valeur.txt";
	//* Attribution des chaines de charcteres
	strcpy(nomDuFichier_et_valeur, nomDuFichier);
	strcat(nomDuFichier_et_valeur, extention_valeur_txt);

	// --- Ouverture du fichier en lecture seul
	FILE* map_valeur = fopen(nomDuFichier_et_valeur, "r");
	if(map_valeur ==NULL){
		printf("fonction: hauteur_from_map ERROR\n");
		printf("erreur: map_valeur==fopen\n");
		exit(1);
	}

	// ---- Recuperation de la hauteur et de la largeur
	int hauteur=10;
	fscanf(map_valeur,"%d",&hauteur );

	fclose(map_valeur);
	return hauteur;
}

int largeur_from_map(const char* nomDuFichier){
	// ---- Attribution nom fichier
	//* Initialisation des chaine de charcarteres
	char nomDuFichier_et_valeur[100];
	char extention_valeur_txt[100] = "_valeur.txt";
	//* Attribution des chaines de charcteres
	strcpy(nomDuFichier_et_valeur, nomDuFichier);
	strcat(nomDuFichier_et_valeur, extention_valeur_txt);

	// --- Ouverture du fichier en lecture seul
	FILE* map_valeur = fopen(nomDuFichier_et_valeur, "r");
	if(map_valeur ==NULL){
		printf("fonction: tableau_from_map ERROR\n");
		printf("erreur: map_valeur==fopen\n");
		exit(1);
	}

	// ---- Recuperation de la hauteur et de la largeur
	int hauteur=10;
	int largeur=10;
	fscanf(map_valeur,"%d",&hauteur );
	fscanf(map_valeur,"%d",&largeur );

	fclose(map_valeur);
	return largeur;
}

/**
 * Methode qui print un tableau pour regarder son contenu dans l'invite de commande
 * @param tab, le tableau qu'on va regarder
 * @param hauteur, la hauteur du tableau
 * @param largeur, la largeur du tableau
 */
// ---- FONCTIONNE PAS ---- //
void tableau_print(int** tab, int hauteur, int largeur){
	int i,j=0;
	for (i=0; i < hauteur; ++i){
		for (j=0; j < largeur; ++j){
			printf("%c",tab[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}


/**
 * Methode qui fournie tableau mape vierge de TowerDefense
 * @param largeur, la largeur de la map
 * @param hauteur, la heuteur de la map
 * @return tabMap, tableau 2D qui symbolise la mape dans un tableau
 */
int** tableau_map_new(int hauteur ,int largeur){
	// --- Creation tableau 2D dynamique
	int** tabMap =tableau_dynamique(hauteur, largeur);
	
	// --- Rempli chacunoaque element du tableau par "0"
		// "0" symbole de sol basique du TowerDefense
	int i=0;
	int j=0;
	for (i=0; i < hauteur ; i++){
			for(j=0; j< largeur; j++){
				tabMap[i][j] = '0';

			}
		}
	return tabMap;
}

/**
 * Methode qui creer un tableau a 2 dimensions dynamique
 * @param largeur, largeur du tableau attendu
 * @param hauteur, hauteur du tableau attendu
 * @return tab[][]
 */
int** tableau_dynamique(int hauteur, int largeur){
	/* On veut avoir int * tab[N], sauf que tab sera créé dynamiquement */ 
	int ** tab = malloc(hauteur * sizeof(int *)); 
	/* On crée maintenant les N tableaux de M éléments chacun */ 
	int i=0;
	for(i = 0; i < hauteur; i++){
		tab[i] = malloc(largeur * sizeof(int ));
		//tab[i] = calloc(largeur, sizeof(int) ); //peut aussi passer par un calloc 
													//pout tt initialisé a 0 	
	}

	return tab;
	
}

/**
 * Methode qui libère la mémoire d'un tableau a 2 dimensions
 * @param tab[][], le tableau a 2 dimension a libéré
 */
void tableau_2dimensions_free(int **tab, int hauteur){
	int i=0;
	for(i =0; i < hauteur; i++){
		free(tab[i]);
	}
	free(tab); 
}

/*
void char_copy(char* nom_destination, char* nom_a_copier){
	if( strlen(nom_destination)+1 <strlen(nom_a_copier)+1 ){
		printf("chaine destnation trop petite ERROR\n");
		printf("fonction char_copy arret\n");
		exit(0);
	}
}
*/


/*------------------------------------------------------------------------------------------*/
/*                               QUELQUE TEST                                               */
/*------------------------------------------------------------------------------------------*/

/*	

int main(int argc, char const *argv[]){



	FILE* map1 =fopen("map1.txt", "r");
	if (map1 ==NULL){
			exit(1);
	}
//--------------------------------------------------------------------
	////////////////
	//fputc("p\n",map1);
	fputc('a',map1);
	fputc('a',map1);
	fputc('a',map1);
	fputc('\n',map1);
	fputc('a',map1);
	fputc('a',map1);
	fputc('\n',map1);
	fputc('a',map1);
	fputc('\n',map1);

	int mot[4] ={ 2, 2, 4 ,4};

	while( (lettre =fgetc(map1)) != EOF){
		printf("%c",lettre );
		//if (feof(map1) ){
		//	break;
		//}
	}
	for (int i = 0; i < 4; ++i){
		switch(mot[i]){
			case 1:
				fputc('1',map1);
				break;
			case 2:
				fputc('2',map1);
				break;
			case 3:
				fputc('3',map1);
				break;
			case 4:
				fputc('4',map1);
				break;
		}
	}
	/////////////////



	/////////////
	char nom[]= "josef";
	char nom2[100];
	
	strcpy(nom2, nom);
	nom[1] = 'd';
	printf("pute\n");
	printf("%s\n",nom2 );
	printf("pute\n");
	printf("%ld\n",strlen(nom2) );
	/////////////



	return 0;
}
*/