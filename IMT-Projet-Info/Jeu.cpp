#include "Jeu.h"
#include "raylib.h"
#include "Ecran.h"
#include <iostream>
using namespace std;

Sound sound4 = LoadSound("explosion.wav");
Sound sound3 = LoadSound("tir.wav");

Jeu::Jeu(int difficult, Joueur j)
{
	srand((unsigned)time(0));
	j_difficulte = difficult;
	j_etat = true;
	j_timer = 0;
	j_tirColldown = 0;
	j_nbAsteroids = 10;
	j_asteroids.push_back(Asteroid(10, 50));
	j_asteroids.push_back(Asteroid(10, 50));
	j_asteroids.push_back(Asteroid(10, 50));
	j_asteroids.push_back(Asteroid(10, 50));
	j_asteroids.push_back(Asteroid(10, 50));
	j_curseur.push_back(Point(500, 490));
	j_curseur.push_back(Point(510, 500));
	j_curseur.push_back(Point(490, 500));

	Joueur j_joueur;

}

void Jeu::nextFrame() {
}

// Avanvancement du jeu en général
void Jeu::avancement(int curs_x, int curs_y, double angle)
{
	avancementTirs(curs_x, curs_y, angle);
	avancementAsteroid();
	collisionCurseur(curs_x, curs_y, angle);
	tirsAuBut();
	j_timer += 1;
	if (j_tirColldown < 20 * (j_difficulte + 1)) {
		j_tirColldown += 1;
	}
	if (j_timer == 1000) { j_timer = 0; }
	//Augmentation du score
	if (j_timer % 40 * (j_difficulte + 1) == 0 && j_timer != 0) {
		switch (j_difficulte) {
		case 0:
			j_joueur.setScoreEasy(j_joueur.getScoreEasy() + 100);
			break;

		case 1:
			j_joueur.setScoreMedium(j_joueur.getScoreMedium() + 100);
			break;
		case 2:
			j_joueur.setScoreHard(j_joueur.getScoreHard() + 100);
			break;
		default:
			break;
		}
	}
}



// avancement des tirs
void Jeu::avancementTirs(int curs_x, int curs_y, double angle) {
	for (int i = 0; i < j_tirs.size(); i++) {
		// mouvement
		j_tirs[i].move();
		// rendu graphique
		j_tirs[i].rendu();
		// sortie d'écran
		if ((j_tirs[i].getX() < 0) || (j_tirs[i].getX() > GetScreenWidth()) || (j_tirs[i].getY() < GetScreenHeight() * 0.09) || (j_tirs[i].getY() > GetScreenHeight())) {
			j_tirs.erase(j_tirs.begin() + i);
		}
	}
	// ajout de tir
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && j_tirColldown == 20 * (j_difficulte + 1)) {
		j_tirs.push_back(Tir(curs_x, curs_y, angle));
		j_tirColldown = 0;
		PlaySoundMulti(sound3);
	}
}

// avancement des asteroids
void Jeu::avancementAsteroid() {
	// ajout asteroid
	if (j_timer % (int)(100 / (1 + pow(j_difficulte, 2))) == 0) {
		j_asteroids.push_back(Asteroid(10, 50));
		j_asteroids.push_back(Asteroid(10, 80));
	}
	for (int i = j_asteroids.size() - 1; i >= 0; i--) {
		// mouvement
		j_asteroids[i].move();
		// Sortie d'écran
		if ((j_asteroids[i].getPosX() < 0) || (j_asteroids[i].getPosX() > GetScreenWidth()) || (j_asteroids[i].getPosY() < GetScreenHeight() * 0.09) || (j_asteroids[i].getPosY() > GetScreenHeight())) {
			j_asteroids.erase(j_asteroids.begin() + i);
		}
	}
	//DrawText(TextFormat("Nb Asteroids : %i", j_asteroids.size()), GetScreenWidth() * 0.05, GetScreenHeight() * 0.06, 30, WHITE);
	for (int i = 0; i < j_asteroids.size(); i++) {
		j_asteroids[i].renduAsteroid();

	}
}

// Détection d'une collision entre le joueur et un asteroid
bool Jeu::collisionCurseur(int curs_x, int curs_y, double angle) {
	for (int ast = 0; ast < j_asteroids.size(); ast++) {
		if (sqrt(pow(curs_x - j_asteroids[ast].getPosX(), 2) + pow(curs_y - j_asteroids[ast].getPosY(), 2)) <= (j_asteroids[ast].getRayon() * sqrt(2) + 20)) {
			j_curseur[0] = Point(curs_x - j_asteroids[ast].getPosX() + 20 * sin(-angle * 3.14159 / 180), curs_y - j_asteroids[ast].getPosY() + 20 * cos(-angle * 3.14159 / 180));
			j_curseur[1] = Point(curs_x - j_asteroids[ast].getPosX() + 20 * sin((240 - angle) * 3.14159 / 180), curs_y - j_asteroids[ast].getPosY() + 20 * cos((240 - angle) * 3.14159 / 180));
			j_curseur[2] = Point(curs_x - j_asteroids[ast].getPosX() + 20 * sin((120 - angle) * 3.14159 / 180), curs_y - j_asteroids[ast].getPosY() + 20 * cos((120 - angle) * 3.14159 / 180));
			if ((j_asteroids[ast].pointDansEnveloppe(j_curseur[0])) || (j_asteroids[ast].pointDansEnveloppe(j_curseur[1])) || (j_asteroids[ast].pointDansEnveloppe(j_curseur[2]))) {
				DrawText("Collision", GetScreenWidth() * 0.05, GetScreenHeight() * 0.15, 50, WHITE);
				return true;
			}
			for (int pt = 0; pt < j_asteroids[ast].getEnvelopList().size() - 1; pt++) {
				if (this->pointDansCurseur(j_asteroids[ast].getPoints()[j_asteroids[ast].getEnvelopList()[pt]])) {
					DrawText("Collision", GetScreenWidth() * 0.05, GetScreenHeight() * 0.15, 50, WHITE);
					return true;
				}
			}
		}
	}
	return false;
}

// Détection d'un point dans le curseur
bool Jeu::pointDansCurseur(Point point)
{
	//1e angle de vue
	int angle0p = j_curseur[0].angle(point);
	int angle01 = j_curseur[0].angle(j_curseur[1]);
	int angle02 = j_curseur[0].angle(j_curseur[2]);
	if (angle02 > 300) {
		if (angle0p < angle02 && angle0p > angle01) {
		}
	}
	else {
		if (angle0p < angle02 || angle0p > angle01) {
		}
	}
	// 2e angle de vue
	int angle1p = j_curseur[1].angle(point);
	int angle10 = j_curseur[1].angle(j_curseur[0]);
	int angle12 = j_curseur[1].angle(j_curseur[2]);
	if (angle10 > 300) {
		if (angle1p < angle10 && angle1p > angle12) {
			return false;
		}
	}
	else {
		if (angle1p < angle10 || angle1p > angle12) {
			return false;
		}
	}
	// 3e angle de vue
	int angle2p = j_curseur[2].angle(point);
	int angle20 = j_curseur[2].angle(j_curseur[0]);
	int angle21 = j_curseur[2].angle(j_curseur[1]);
	if (angle21 > 300) {
		if (angle2p < angle21 && angle2p > angle20) {
			return false;
		}
	}
	else {
		if (angle2p < angle21 || angle2p > angle20) {
			return false;
		}
	}
	return true;
}

// détection d'un tir dans un asteroid
void Jeu::tirsAuBut() {
	for (int aste = j_asteroids.size() - 1; aste >= 0; aste--) {
		for (int tir = 0; tir < j_tirs.size(); tir++) {
			if (j_asteroids[aste].pointDansEnveloppe(Point(j_tirs[tir].getX() - j_asteroids[aste].getPosX(), j_tirs[tir].getY() - j_asteroids[aste].getPosY()))) {
				j_asteroids.erase(j_asteroids.begin() + aste);
				j_tirs.erase(j_tirs.begin() + tir);
				if(rand()%2==0)
					j_asteroids.push_back(Asteroid(10, 50));
				else 
					j_asteroids.push_back(Asteroid(8,80));
				PlaySoundMulti(sound4);
				switch (j_difficulte) {
				case 0:
					j_joueur.setScoreEasy(j_joueur.getScoreEasy() + 25);
					break;

				case 1:
					j_joueur.setScoreMedium(j_joueur.getScoreMedium() + 25);
					break;
				case 2:
					j_joueur.setScoreHard(j_joueur.getScoreHard() + 25);
					break;
				default:
					break;
				}
				break;
			}
		}
	}
}