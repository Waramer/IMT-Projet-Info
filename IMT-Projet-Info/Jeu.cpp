#include "Jeu.h"
#include "raylib.h"

Jeu::Jeu()
{
	srand((unsigned)time(0));
	j_etat = true;
	j_timer = 0;
	j_nbAsteroids = 5;
	j_asteroids.push_back(Asteroid(10, 50));
	j_curseur.push_back(Point(500, 500));
	j_curseur.push_back(Point(500, 500));
	j_curseur.push_back(Point(500, 500));
}

void Jeu::nextFrame() {
	this->avancement();
	this->renduAsteroids();
}

void Jeu::avancement()
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
	for (int pt = 0; pt < 3; pt++) {
		DrawCircle(j_curseur[pt].get_x() + 300, j_curseur[0].get_y() + 300, 3, RED);
		DrawCircle(j_curseur[(pt + 1) % 3].get_x() + 300, j_curseur[(pt + 1) % 3].get_y() + 300, 3, RED);
		DrawCircle(j_curseur[(pt + 2) % 3].get_x() + 300, j_curseur[(pt + 2) % 3].get_y() + 300, 3, RED);
		DrawCircle(point.get_x() + 300, point.get_y() + 300, 3, GREEN);
		double angle0 = j_curseur[pt].angle(point); // angle avec le point à tester
		double angle1 = j_curseur[pt].angle(j_curseur[(pt+1)%3]); // avec le point suivant du curseur (sens horaire)
		double angle2 = j_curseur[pt].angle(j_curseur[(pt+2) % 3]); // avec le dernier point du curseur (sens horaire)
		if (angle1>=240) { // alors l'intervalle à tester est [angle1;360]U[0;angle2]
			if ((angle0 < angle1) && (angle0 > angle2)) {
				return false;
			}
		}
		else { // sinon c'est le cas classique et il faut tester l'intervalle [angle1;angle2]
			if ((angle0 < angle1)||(angle0 > angle2 )) {
				return false;
			}
		}

	}
	return true;
}