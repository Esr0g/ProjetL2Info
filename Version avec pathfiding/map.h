#ifndef MAP_H
#define MAP_H

// --- METHODE SUR MAP FILE
void map_new(const char* nomDuFichier, int hauteur, int largeur);
void map_from_tableau(const char* nomDuFichier, int**tabMap);
void map_from_tableau_new(const char* nomDuFichier, int**tabMap, int hauteur, int largeur);
int** tableau_from_map(const char* nomDuFichier);
int hauteur_from_map(const char* nomDuFichier);
int largeur_from_map(const char* nomDuFichier);

// --- METHODE SUR TABLEAU 2D
void tableau_print(int** tab, int hauteur, int largeur);
int** tableau_map_new(int hauteur, int largeur);
int** tableau_dynamique(int hauteur, int largeur);
void tableau_2dimensions_free(int **tab, int hauteur);


#endif