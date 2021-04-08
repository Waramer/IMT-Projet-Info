#include "Jeu.h"
#include "raylib.h"
#include <iostream>
using namespace std;
Jeu::Jeu()
{
	srand((unsigned)time(0));
	j_etat = true;
	j_timer = 0;
	j_nbAsteroids = 10;
	j_asteroids.push_back(Asteroid(10, 50));
	j_curseur.push_back(Point(500, 500));
	j_curseur.push_back(Point(500, 500));
	j_curseur.push_back(Point(500, 500));
}

void Jeu::nextFrame() {
}

void Jeu::avancement(int curs_x, int curs_y, double angle)
{
	if (j_asteroids.size() < j_nbAsteroids) {
		j_asteroids.push_back(Asteroid(10, 50));
	}
	DrawText(TextFormat("Nb Asteroids : %i", j_asteroids.size()), GetScreenWidth() * 0.05, GetScreenHeight() * 0.05, 50, WHITE);
	for (int i = j_asteroids.size() - 1; i >= 0; i--) {
		if ((j_asteroids[i].getPosX() < 0)||(j_asteroids[i].getPosX() > GetScreenWidth())||(j_asteroids[i].getPosY() < GetScreenHeight()*0.09)||(j_asteroids[i].getPosY() > GetScreenHeight())) {
			j_asteroids.erase(j_asteroids.begin()+i);
		}
		else {
			j_asteroids[i].move();
		}
	}
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		j_tirs.push_back(Tir(curs_x,curs_y,angle));
	}
	for (int i = 0; i < j_tirs.size(); i++) {
		j_tirs[i].move();
		j_tirs[i].rendu();
	}
}

void Jeu::renduAsteroids() {
	for (int i = 0; i < j_asteroids.size(); i++) {
		j_asteroids[i].renduAsteroid();
	}
}

bool Jeu::collisionCurseur(int curs_x,int curs_y,double angle) {
	for (int ast = 0; ast < j_asteroids.size(); ast++) {
		if (sqrt(pow(curs_x-j_asteroids[ast].getPosX(),2)+pow(curs_y - j_asteroids[ast].getPosY(),2)) <= (j_asteroids[ast].getRayon()*sqrt(2)+20) ) {
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

bool Jeu::pointDansCurseur(Point point)
{
	//1e angle de vue
	int angle0p = j_curseur[0].angle(point);
	int angle01 = j_curseur[0].angle(j_curseur[1]);
	int angle02 = j_curseur[0].angle(j_curseur[2]);
	if (angle02 > 300 ) {
		if ( angle0p < angle02 && angle0p > angle01 ) {
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