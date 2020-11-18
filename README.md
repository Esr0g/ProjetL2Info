# Tower Defence en 2D

## But du projet 
Faire un tower defence fonctionnel en 2D au début tout simple  
  
Puis l'améliorer au fur et à mesure du projet avec :  
- Menu avec choix (quitter, jouer).  
  
- Definition d'une base (vie et forme (SDL_Rect)):   
	- La base perd 1 point de vie lorsque un ennemis la touche.`  
  
- Ennemis qui se déplacent en temps réels :  
	- Struct ennemi définis par sa vie et sa forme (SDL_Rect)  
	- Les "ennemis" sont ajoutés au fur et à mesure dans une liste à l'aide d'un timer au début de la partie.  
	- Il peuvent arriver par 2 endroits différents sur l'écran:  
		- 2 chemins différents pour les ennemis  
	- Les ennemis dissparaissent de l'écran et de la liste lorsque qu'il rentrent en collision avec la base  
	- Les ennemis dispparaissent de l'ecran et de la liste lorsque leurs points de vie atteint 0  
  
- Tourelle:  
	- Ajouter sur l'ecran avec un clic  
	- tourelle ajoutée à une liste  
	- On ne peut pas placer plusieurs tourelles au même endroit  
	- Elles tirent toutes les x secondes sur un ennemis proche  
  		
(Cette liste va surement évoluée)  

## Prérequis 
- SDL2 
- SDL2_gfx (sudo apt install libsdl2-gfx-1.0-0 libsdl2-gfx-dev)  
- SDL2_ttf (sudo apt install libsdl2-ttf-dev)  

## Usage

git clone https://github.com/Esr0g/ProjetL2Info.git  
se placer dans un terminale dans ProjetL2Info  
make   
./towerDefence  

## Suivi


### Semaine -1

Implémentation de la SDL pour afficher uniquement le fond  
Création de la boucle principale dans main.c avec le code de bases pour quitter.  
Ajout d'une fonction jeu dans jeu.c avec son header. Boucle principale d'une partie  
Ajout d'un menu dans main avec choix pour jouer.

### Semaine 0

Ajout d'un fichier constantes.h avec les constantes du jeu  
Ajout d'un fichier structure.c et structure.h avec les définitions des ennemis, des tourelles et des listes ainsi que toutes les fonctions associées  
Affichage des ennemis avec ajout à une liste les uns après les autres. Ils se déplacent à une vitesse constante à l'aide d'un timer et disparraissent (de la liste et de l'écran) lorsqu'ils rentrent en collision avec la base.  

### Semaine 1

Ajout des fonctions pour gérer la liste de tourelle  
Ajout de la librairie SDL2_gfx qui permet de gérer l'affichage de cercle  
Ajout d'une structure cerlce  
Les tourelles sont maintenant définis en plus par un cercle qui est leur portée d'attaque: le cercle s'afficher sur la map avec de la transparence  
Ajout d'une structure case qui représentent le terrain de jeu: un case est défini par un rectgle et des boolean  
La map est maintenant représentée par un tableau de case (Ajout des fonction pour allouer la mémoire au tableau à double entrée et pour libérer la mémoire)  
Il est maintenant possible d'ajouter une tourelle avec un clic de la souris sur les cases de la map (impossible d'en mettre plusieurs sur une même case, impossible de poser une tourelle sur le chemin des ennemis ou sur la base)  

### Semaine 2

Ajout des fonctions pour permet de savoir si il y'a une collison entre un ennemi ou une tourelle  
source des algo : http://sdz.tdct.org/sdz/eorie-des-collisions.html  
Les tourelles attaques maintenant en fonction de leur vitesse d'attaque  
Ajout de la librairie SDL_ttf  (affichage de texte)  

### Semaine 3

Ajout d'une page "défaite" lorsque la vie de la base atteint 0  
Il est possible de quitter ou de retourner au menu à l'aide d'un clique de la souris sur le bon boutton  
Lorsque l'on survole les bouttons avec la souri, ceux-ci se mettent en rouge  
On peut maintenant choisir plusieurs manche (pas encore ajouter à l'une à la suite des autre: il faut choisir manuellement dans le code)  
Le nombre d'ennemis qui commencent par le haut ou par la gauche est écrit dans un fichier texte  
Problème rencontré: les attaques des tourelles sur les ennemis sont plutot hasardeuse et on n'arrive pas à trouver le problème..  
Les manches s'enchainent maintenant automatiquement (elles sont gérée dans un fichier texte, on peut changer facilement le nombre d'ennemis et on peut rajouter des manches facilement, pour l'instant il y'en a 20)  
Il y'a maintenant le début d'un sytème de gestion d'argent (on ne peut pas poser une tourelle lorsque l'on a pas assez d'argent)  
Il y'a aussi le début de géstion du score (+50 à chaque tourelle tuée, +150 à chaque fin de manche)  