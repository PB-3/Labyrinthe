
#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"
#include <math.h>
#include <windows.h>
#include <ctime>

// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

 
enum ecran { ECRAN_ACCEUIL, ECRAN_JEU, ECRAN_GAME_OVER,ECRAN_VICTOIRE};
using namespace std;

struct _ecran
{
	ecran ECRAN = ECRAN_ACCEUIL;
	bool load = true;
	V2 loading = V2(100, 100);
	bool restart = false;
};
	
	


struct _Heros
{
	string texture =
		"[RRR  ]"
		"[RRWR ]"
		"[RRR  ]"
		"[YY   ]"
		"[YYY  ]"
		"[YY YG]"
		"[GG   ]"
		"[CC   ]"
		"[CC   ]"
		"[C C  ]"
		"[C C  ]";
	string texture2=
		"[RRR  ]"
		"[RRWR ]"
		"[RRR  ]"
		"[YY   ]"
		"[YYY  ]"
		"[YY YG]"
		"[GG   ]"
		"[CC   ]"
		"[CC   ]"
		"[CC   ]"
		"[CC   ]";
		

	V2 Size=V2(10,10);
	int IdTex; 
	int IdTex2;
	V2 Pos = V2(45,45);
};

struct _Key
{
	string texture =
		"[                      ]"
		"[     W W         WWWW ]"
		"[     W W        W    W]"
		"[   WWWWWWWWWWWWWW    W]"
  	    "[                W    W]"
		"[                 WWWW ]";


	V2 Size;
	int IdTex;

	V2 Pos = V2(440, 450);
};


struct _Chest
{
	string chest_closed =
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDWWWWWWWWWWWDDDDDIII]"
		"[IIIIIIIIWWWWWWWWWWWIIIIIIII]"
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]";

	string chest_openned=
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[                           ]"
		"[                           ]"
		"[                           ]"
		"[                           ]"
		"[                           ]"
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIDDDDDDDDDDDDDDDDDDDDDIII]"
		"[IIIIIIIIIIIIIIIIIIIIIIIIIII]";

	bool Open = false;
	V2 Size;
	int IdTex;
	int IdTex2;
	V2 Pos = V2(400, 40);
};
struct Momie
{
	string texture_momie=
		"[WWW  ]"
		"[WWW  ]"
		"[WWW  ]"
		"[WW   ]"
		"[WWW  ]"
		"[WW WW]"
		"[WW   ]"
		"[WW   ]"
		"[WW   ]"
		"[W W  ]"
		"[W W  ]";
	V2 Pos;
	V2 Dir=V2(1,0);
	int idText;
	V2 Size=V2(10,10);
	Momie() {}
	Momie(V2 Position)
	{
		Pos = Position;
	}
	
	
};
struct _Jeu
{
	string Map =
		"MMMMMMMMMMMMMMM"
		"M M           M"
		"M M M MMM MMM M"
		"M   M       M M"
		"MMM M M MMM M M"
		"M   M M     M M"
		"M MMM MMM MMMMM"
		"M   M  M      M"
		"M M M  M M MM M"
		"M M M  M M M  M"
		"M M M MM M MMMM"
		"M M M    M    M"
		"M M M MMMMMMM M"
		"M M      M    M"
		"MMMMMMMMMMMMMMM";

	// indique la présence d'un mur à la case (x,y)
	bool Mur(int x, int y) const { return Map[(15 - y - 1) * 15 + x] == 'M'; }  // les fonctions const ne modifient pas les données




	int Lpix = 40;  // largeur en pixels des cases du labyrinthe
	int IdFrame = 0;
	_Heros Heros;   // data du héros
	_Key   Key;
	_Chest Chest;
	bool chest_is_open = false;
	int Life = 3;
	bool win = false;
	int NombreDeMomies = 1;
	vector<Momie> Momies = {};
	vector <Momie> MomieInitiale = {};
	_Jeu()
	{
		while (NombreDeMomies!=0)
		
			{
				int x = rand() % 14;
				int y = rand() % 14;
				if (!Mur(x, y))
				{
					int xx = x * Lpix;
					int yy = y * Lpix;
					Momie M1 = Momie(V2(xx,yy));
					Momies.push_back(M1);
					MomieInitiale.push_back(M1);
					NombreDeMomies--;
				}
			}
		
		
	}
	
};
struct GameData
{

	_Jeu Jeu;
	_ecran Screen;
	GameData() {}

};
 
ecran gestion_ecran_accueil(GameData &G)
{
	
	if (G.Screen.loading.x>=380)
	{
		G.Screen.load = false;
	}
	else
	{
		G.Screen.load = true;
		G.Screen.loading.x+= 1;
	}
	
	return ECRAN_ACCEUIL;

}
void gestion_ecran_options() {}

ecran gestion_jeu(GameData &G)
{
	
	
	return ECRAN_JEU;
}
void timer(int remain)
{
	
		int b = 0;
		int t = G2D::elapsedTimeFromStartSeconds();
		while (b <= (t + remain)) { 
			b = G2D::elapsedTimeFromStartSeconds(); 
		}
}
ecran gestion_GameOver(GameData & G)
{

	G.Screen.restart = true;
	
	return ECRAN_GAME_OVER;
}

void InitPartie(GameData& G) // Remise a zero de tout les éléments du jeu
{

	// Restart du jeu 
	if (G.Jeu.win && G.Screen.ECRAN == ECRAN_JEU)
	{
		timer(3);
		G.Screen.ECRAN = ECRAN_VICTOIRE;
		

		
	}

	// Jeu
	G.Jeu.chest_is_open = false;
	G.Jeu.win = false;
	G.Jeu.Heros.Pos = V2(45, 45);
	G.Jeu.Key.Pos = V2(440, 450);
	G.Jeu.Chest.Open = false;
	// Momies
	if (G.Jeu.Life<=0)
	{
		for (int i = 0; i < G.Jeu.Momies.size(); i++)
		{
			G.Jeu.Momies[i].Pos = G.Jeu.MomieInitiale[i].Pos;
		}
	}
	// Ecrans
	G.Screen.load = true;
	G.Screen.restart = false;
	G.Screen.loading = V2(100, 100);
	
	
}

void Render(const GameData& G)  // const ref => garantit que l'on ne modifie pas les donnes de G
{
	if (G.Screen.ECRAN == ECRAN_JEU || G.Screen.ECRAN == ECRAN_JEU && G.Screen.restart)
	{

		G2D::clearScreen(Color::Black);
		
		for (int x = 0; x < 15; x++)
			for (int y = 0; y < 15; y++)
			{
				int xx = x * G.Jeu.Lpix;
				int yy = y * G.Jeu.Lpix;
				if (G.Jeu.Mur(x, y))
					G2D::drawRectangle(V2(xx, yy), V2(G.Jeu.Lpix, G.Jeu.Lpix), Color::Gray, true);
			}

		// affichage du héro avec boite englobante et zoom x 2
		G2D::drawRectangle(G.Jeu.Heros.Pos, G.Jeu.Heros.Size, Color::Red);
		int d = G2D::elapsedTimeFromStartSeconds();
		if (d%2==0 )
		{
			G2D::drawRectWithTexture(G.Jeu.Heros.IdTex, G.Jeu.Heros.Pos, G.Jeu.Heros.Size);
			
		}
		else
		{
			G2D::drawRectWithTexture(G.Jeu.Heros.IdTex2, G.Jeu.Heros.Pos, G.Jeu.Heros.Size);

		}
		// affichage de la clef
		G2D::drawRectWithTexture(G.Jeu.Key.IdTex, G.Jeu.Key.Pos, G.Jeu.Key.Size);

		// affichage du coffre

		
		if(!G.Jeu.chest_is_open) G2D::drawRectWithTexture(G.Jeu.Chest.IdTex, G.Jeu.Chest.Pos, G.Jeu.Chest.Size);

		// affichage des momies 
		for (int i = 0; i < G.Jeu.Momies.size(); i++)
		{
			G2D::drawRectangle(G.Jeu.Momies[i].Pos, G.Jeu.Momies[i].Size, Color::Red);

			G2D::drawRectWithTexture(G.Jeu.Momies[i].idText, G.Jeu.Momies[i].Pos, G.Jeu.Momies[i].Size);
		}
		

	}
	// affichage de l'écran d'acceuil

	else if (G.Screen.ECRAN == ECRAN_ACCEUIL)
	{

		G2D::clearScreen(Color::Black);
		G2D::drawRectangle(V2(120, 390), V2(360, 50), Color::Green, false);
		G2D::drawStringFontMono(V2(120, 400), "W E L C O M E", 40.0, 5, Color::Red);

		if (G.Screen.load)
		{

			G2D::drawRectangle(V2(100, 100), V2(380, 100), Color::Green, false);

			G2D::drawRectangle(G.Screen.loading, V2(70, 100), Color::Red, true);

		}
		else G2D::drawStringFontMono(V2(100, 250), "Press W to play", 40.0, 5, Color::Red);


	}
	// affichage de l'écran Game over
	else if (G.Screen.ECRAN == ECRAN_GAME_OVER)
	{
		G2D::clearScreen(Color::Black);
		G2D::drawRectangle(V2(100, 390), V2(420, 50), Color::Green, false);
		G2D::drawStringFontMono(V2(110, 400), "G A M E O V E R", 40.0, 5, Color::Red);
		G2D::drawStringFontMono(V2(100, 250), "Press R to restart", 40.0, 5, Color::Red);


	}
	// affichage des vies 
	if (G.Screen.ECRAN == ECRAN_JEU)
	{
		G2D::drawStringFontMono(V2(10, 565), "Lifes:", 40.0, 5, Color::Black);
		G2D::drawStringFontMono(V2(170, 565), to_string(G.Jeu.Life), 40.0, 5, Color::Black);

	}
	if (G.Screen.ECRAN == ECRAN_VICTOIRE)
	{
		G2D::clearScreen(Color::Black);
		G2D::drawStringFontMono(V2(100, 250), "G G W P", 40.0, 5, Color::Red);
		G2D::drawRectWithTexture(G.Jeu.Chest.IdTex2, G.Jeu.Chest.Pos, G.Jeu.Chest.Size);
	}

	G2D::Show();
}
bool Proximite(int x1, int y1, int x2, int y2, int distmin)
{
	return pow(x1 - x2, 2) + pow(y1 - y2, 2) < distmin * distmin;
}

void DeplacementHeros(GameData& G)
{
	if (G2D::isKeyPressed(Key::RIGHT))
	{

		G.Jeu.Heros.Pos.x++;
	}
	if (G2D::isKeyPressed(Key::LEFT))
	{
		G.Jeu.Heros.Pos.x--;
	}
	if (G2D::isKeyPressed(Key::UP))
	{
		G.Jeu.Heros.Pos.y++;
	}
	if (G2D::isKeyPressed(Key::DOWN))
	{
		G.Jeu.Heros.Pos.y--;
	}
}

void DeplacementMomies(Momie& M, GameData& G)
{

	M.Pos = M.Pos + M.Dir;
}
V2 deplacementRandom(V2 dep)
{
	V2 v;
	
	
	int a = rand() % 4;
	
	if (a == 0)
	{
		v = V2(1, 0); // gauche
		return v;
	}
	if (a == 1)
	{
		v = V2(0, 1); // Monte 
		return v;
	}
	if (a == 2)
	{
		v = V2(0, -1); // Descend
		return v;
	}
	if (a == 3)
	{
		v = V2(-1, 0); // Descend
		return v;
	}

}

bool CollisionMur(GameData& G,V2 Pos)
{
	V2 PosHeros = V2(G.Jeu.Heros.Pos);
	
	
	int x = Pos.x;
	int y = Pos.y;

	int sizex = G.Jeu.Heros.Size.x;
	int sizey = G.Jeu.Heros.Size.y;
	int pix = G.Jeu.Lpix;
	
	
	


			if (G.Jeu.Mur(x / pix, (y + sizey) / pix) && G.Jeu.Mur((x + sizex) / pix, (y + sizey) / pix))// essaye d'aller en haut 
				return true;
			if (G.Jeu.Mur((x) / pix, (y + sizey) / pix) && G.Jeu.Mur((x) / pix, (y) / pix)) // en haut a gauche et en bas a gauche
			{
				return true;
			}
			
			if (G.Jeu.Mur((x + sizex) / pix, (y + sizey) / pix) && G.Jeu.Mur((x + sizex) / pix, (y) / pix)) // en haut a droite et en bas a droite
			{
				return true;
			}

			if (G.Jeu.Mur((x + sizex) / pix, (y) / pix) && G.Jeu.Mur((x) / pix, (y) / pix))// En bas a droite
			{
				return true;
			}
			if (G.Jeu.Mur((x + sizex) / pix, (y) / pix)) // coin en bas a droite
			{
				return true;
			}
			if (G.Jeu.Mur((x) / pix, (y) / pix)) //  coin en bas a gauche
			{
				return true;
			}
			if (G.Jeu.Mur((x + sizex) / pix, (y + sizey) / pix)) // coin en haut a droite
			{
				return true;
			}
			if (G.Jeu.Mur((x) / pix, (y + sizey) / pix)) // coin en haut a gauche 
			{
				return true;
			}

			return false;
	

	

}
void CollisionJoueurMomie(GameData& G)
{
	for (int i = 0; i < G.Jeu.Momies.size(); i++)
	{

		if (Proximite(G.Jeu.Heros.Pos.x, G.Jeu.Heros.Pos.y, G.Jeu.Momies[i].Pos.x, G.Jeu.Momies[i].Pos.y, 50))
		{
			G.Jeu.Life--;
			InitPartie(G);
		}
	}
}


void CollisionJoueurObjet(GameData& G)
{
	
	if (Proximite(G.Jeu.Heros.Pos.x, G.Jeu.Heros.Pos.y, G.Jeu.Key.Pos.x, G.Jeu.Key.Pos.y, 20)) // Heros Cle
		G.Jeu.Key.Pos = G.Jeu.Heros.Pos;

	if (Proximite(G.Jeu.Chest.Pos.x, G.Jeu.Chest.Pos.y, G.Jeu.Key.Pos.x, G.Jeu.Key.Pos.y, 20)) // Cle Heros
	{
		G.Jeu.chest_is_open = true;
		G.Jeu.win = true;
		InitPartie(G);

	}
}


void Logic(GameData& G)
{
	G.Jeu.IdFrame += 1;
	V2 lastPos = G.Jeu.Heros.Pos; // aquisition de la derniere pos du joueur pour les collisions
	

	if (G.Screen.load)
		gestion_ecran_accueil(G);// lancer la barre de chargement

	if (G2D::isKeyPressed(Key::W) && !G.Screen.load)
		G.Screen.ECRAN = gestion_jeu(G); // lancer le jeu

	if (G.Screen.ECRAN == ECRAN_VICTOIRE) 
	{
		timer(3);
		G.Screen.ECRAN = ECRAN_ACCEUIL;
		
	}
	if (G.Jeu.Life <= 0)
		G.Screen.ECRAN = gestion_GameOver(G); // game over

	if (G.Screen.ECRAN == ECRAN_JEU)
	{
		DeplacementHeros(G);

		if (CollisionMur(G,G.Jeu.Heros.Pos))
		{
			G.Jeu.Heros.Pos = lastPos;// replacement du joueur
		}

	
		for (int i=0;i<G.Jeu.Momies.size();i++) // replacement des momies
		{

			V2 MomieLastPos = G.Jeu.Momies[i].Pos;
			DeplacementMomies(G.Jeu.Momies[i], G);
			if (CollisionMur(G,G.Jeu.Momies[i].Pos))
			{
				G.Jeu.Momies[i].Pos = MomieLastPos;

				G.Jeu.Momies[i].Dir = deplacementRandom(G.Jeu.Momies[i].Dir);
			}

		}
		
	}

	 if (G.Screen.restart&&G2D::isKeyPressed(Key::R)) // restart
	{
		G.Screen.ECRAN = gestion_ecran_accueil(G);
	
			InitPartie(G);
			G.Jeu.Life = 3;
		
		
	} // relancer le jeu
	 
	CollisionJoueurObjet(G); // test collision
	CollisionJoueurMomie(G);

	
}
 

void AssetsInit(GameData & G)
{
   // Size passé en ref et texture en param
	
	G.Jeu.Heros.IdTex = G2D::initTextureFromString(G.Jeu.Heros.Size, G.Jeu.Heros.texture);
	G.Jeu.Heros.Size = G.Jeu.Heros.Size * 3; // on peut zoomer la taille du sprite
		
	G.Jeu.Heros.IdTex2 = G2D::initTextureFromString(G.Jeu.Heros.Size, G.Jeu.Heros.texture2);
	G.Jeu.Heros.Size = G.Jeu.Heros.Size * 3; // on peut zoomer la taille du sprite
	
   G.Jeu.Key.IdTex   = G2D::initTextureFromString(G.Jeu.Key.Size, G.Jeu.Key.texture);
   G.Jeu.Key.Size    = G.Jeu.Key.Size * 1.5; // on peut zoomer la taille du sprite

   G.Jeu.Chest.IdTex = G2D::initTextureFromString(G.Jeu.Chest.Size, G.Jeu.Chest.chest_closed);
   G.Jeu.Chest.Size = G.Jeu.Chest.Size * 1.5; // on peut zoomer la taille du sprite

	G.Jeu.Chest.IdTex2 = G2D::initTextureFromString(G.Jeu.Chest.Size, G.Jeu.Chest.chest_openned);
   G.Jeu.Chest.Size = G.Jeu.Chest.Size * 1.5; // on peut zoomer la taille du sprite
 for (int i = 0; i < G.Jeu.Momies.size(); i++)
   {
	   G.Jeu.Momies[i].idText = G2D::initTextureFromString(G.Jeu.Momies[i].Size, G.Jeu.Momies[i].texture_momie);
	   G.Jeu.Momies[i].Size = G.Jeu.Momies[i].Size * 3; // on peut zoomer la taille du sprite
   }
   
   

}


int main(int argc, char* argv[])
{ 
		GameData G;
		srand(NULL);
		G2D::initWindow(V2(G.Jeu.Lpix * 15, G.Jeu.Lpix * 15), V2(0, 0), string("Labyrinthe"));
	

		AssetsInit(G);
		InitPartie(G);
		int nbcalltologicpersec = 50;
	

	G2D::Run(Logic,Render,G,nbcalltologicpersec,true);
	
 
}
 
  
 