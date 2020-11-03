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

## Usage

git clone https://github.com/Esr0g/ProjetL2Info.git  
se placer dans un terminale dans ProjetL2Info  
make   
./towerDefence  

## Suivi


### Semaine 1

On a implémenté la base de l'affichage  
Création d'une vague d'ennemis qui se déplace  
Difficulté  : gestion de la liste d'ennemi    

### Semaine 2
	
	
	
