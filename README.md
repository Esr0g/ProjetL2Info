# ProjetL2Info
Tower Defence

jeu.c
	Struct Ennemi
		int vie =1
		int pos 
		
	Struct Base 
		int vie = 3
		
	
	Fonction Initialisation ()
	{
		creation d'une liste qui copie une liste d'ennemi qui se trouve dans constance.c
		
		
	}
	
	
	Fonction Suivant () // Effectue un tour 
	{
		regarder toute la liste D'ennemi (boucle)
		{
			si position == 24 
			{
				EnleverUneVie()
			}
			sinon
			{
				position ++
			}
		}fin regarder toute la liste 
		
		Afficher tous les ennemis sur sdl avec leurs nouvelles positions
	}

constance.c
	switch PositionNiveau1
	{
		case 0 : Pas de position pas d'affichege 
		case 1 : x=0 , y=263
		case 2 : x=64 , y=263
	}
	
	liste Ennemi 
		e1 : Vie = 1 , Position = 0
		e2 : Vie = 1 , Position = -1
		e3 : Vie = 1 , Position = -2
		e4 : Vie = 1 , Position = -3
	
	
	
	
	
	
