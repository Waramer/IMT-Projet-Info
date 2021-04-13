#include "Asteroid.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

Asteroid::Asteroid(int nb_points, int rayon)
{
	a_rayon = rayon;
	a_nbPoints = nb_points;
	a_points.reserve(nb_points);

	for (int pt = 0; pt < a_nbPoints; pt++) {
		a_points.push_back(Point(rayon));
	}

	// Initialisation de la position
	int const fen_x = GetScreenWidth();
	int const fen_y = GetScreenHeight();
	int num = rand() % 4;
	if (num == 0) {
		a_position[0] = 50;
		a_position[1] = rand() % (int)(fen_y*0.9) + (int)fen_y*0.1;
	}
	else if (num == 1) {
		a_position[0] = fen_x - 50;
		a_position[1] = rand() % (int)(fen_y * 0.9) + (int)fen_y * 0.1;
	}
	else if (num == 2) {
		a_position[0] = rand() % fen_x;
		a_position[1] = 0.1 * fen_y + 50;
	}
	else if (num == 3) {
		a_position[0] = rand() % fen_x;
		a_position[1] = fen_y - 50;
	}

	// Initialisation de la direction
	double deltax = rand() % (int)(fen_x * 0.8) - fen_x * 0.4 + fen_x/2;
	double deltay = rand() % (int)(fen_y * 0.8) - fen_y * 0.4 + fen_y/2;
	a_direction[0] = (deltax - a_position[0]) / sqrt(pow((deltax - a_position[0]), 2) + pow((deltay - a_position[1]), 2)) ;
	a_direction[1] = (deltay - a_position[1]) / sqrt(pow((deltax - a_position[0]), 2) + pow((deltay - a_position[1]), 2)) ;

	// Création de l'enveloppe
	envelopFindList();
}

void Asteroid::setPosition(int x, int y)
{
	a_position[0] = x;
	a_position[1] = y;
}
double Asteroid::getPosX() {
	return a_position[0];
}
double Asteroid::getPosY() {
	return a_position[1];
}

double Asteroid::getDirX()
{
	return a_direction[0];
}

double Asteroid::getDirY()
{
	return a_direction[1];
}

void Asteroid::setDirection(double dirX, double dirY)
{
	a_direction[0] = dirX;
	a_direction[1] = dirY;
}


void Asteroid::affiche()
{
	cout << "Voici les points de l'Asteroid : " << endl;
	for (int pt = 0; pt < a_nbPoints; pt++) {
		a_points[pt].affiche();
		cout << endl;
	}
}

// Code de l'enveloppe

int Asteroid::envelopFindInitPoint() {
	int m = 0;
	for (int n = 1; n < a_nbPoints; n++) {
		if (a_points[n].get_x() <= a_points[m].get_x()) {
			if (a_points[n].get_x() == a_points[m].get_x()) {
				if (a_points[n].get_y() > a_points[m].get_y()) {
					m = n;
				}
			}
			else
			{
				m = n;
			}
		}
	}
	return m;
}

void Asteroid::envelopFindList() {
	int initPoint = this->envelopFindInitPoint();
	int actualPoint = initPoint;
	bool retour = false;
	a_enveloppe.push_back(actualPoint); // début de l'enveloppe
	while (true){
		double angle = 360;
		int nextPoint = actualPoint;
		for (int pt = 0; pt < a_nbPoints; pt++) {
			if (!(a_points[actualPoint].estEgal(a_points[pt]))) { // on considère uniquement les points différents de celui actuel pour poursuivre l'enveloppe
				if (retour) {
					if (((a_points[actualPoint].angle(a_points[pt])) <= angle)&&((a_points[actualPoint].angle(a_points[pt])) > 180 )) {
						angle = a_points[actualPoint].angle(a_points[pt]);
						nextPoint = pt;
					}
				}
				else{
					if ((a_points[actualPoint].angle(a_points[pt])) <= angle) {
						angle = a_points[actualPoint].angle(a_points[pt]);
						nextPoint = pt;
					}
				}
			}
		}
		a_enveloppe.push_back(nextPoint);
		actualPoint = nextPoint;
		if (angle > 180) { retour = true; }
		if (a_points[actualPoint].estEgal(a_points[initPoint])) {
			break;
		}
	}
}

vector<int> Asteroid::getEnvelopList() {
	return a_enveloppe;
}

std::vector<Point> Asteroid::getPoints()
{
	return a_points;
}

// Code de collision

bool Asteroid::pointDansEnveloppe(Point point)
{
	for (int pt = 0; pt < a_enveloppe.size() - 1; pt++) {

		Point p1 = a_points[a_enveloppe[pt]];
		Point p2 = a_points[a_enveloppe[pt+1]];

		//on considère d'abord les partie "droite" à 0,90,180,270 qui sont des ectrémités de l'enveloppe par convexité de cette dernière.
		if (p1.get_x() == p2.get_x()) {
			if (p1.get_y() <= p2.get_y()) {
				if (point.get_x() <= p1.get_x()) {
					return false;
				}
			}
			if (p1.get_y() >= p2.get_y()) {
				if (point.get_x() >= p1.get_x()) {
					return false;
				}
			}
		}
		if (p1.get_y() == p2.get_y()) {
			if (p1.get_x() <= p2.get_x()) {
				if (point.get_y() >= p1.get_y()) {
					return false;
				}
			}
			if (p1.get_x() >= p2.get_x()) {
				if (point.get_y() <= p1.get_y()) {
					return false;
				}
			}
		}
		else {
			// il faut alors regarder un hyperplan ou hypoplan (suivant le gradient de x) de la droite caractérisé par les points p1 et p2.
			double a = ((float)(p2.get_y()-p1.get_y())/(p2.get_x()-p1.get_x()));
			double b = p1.get_y() - a * p1.get_x();
			if (p1.get_x() < p2.get_x()) {
				if (point.get_y() > a * point.get_x() + b) {
					return false;
				}
			}
			if (p1.get_x() > p2.get_x()) {
				if (point.get_y() < a * point.get_x() + b) {
					return false;
				}
			}
		}
	}
	return true;
}

// Colision entre astéroids
bool Asteroid::collisionEntreAsteroid(Asteroid aste) {
	if (sqrt(pow(aste.a_position[0] - a_position[0], 2) + pow(aste.a_position[1] - a_position[1], 2)) <= a_rayon + aste.a_rayon) {
		for (int pt = 0; pt < a_enveloppe.size()-1; pt++) {
			if (aste.pointDansEnveloppe(Point(a_points[a_enveloppe[pt]].get_x() + a_position[0] - aste.getPosX(), a_points[a_enveloppe[pt]].get_y() + a_position[1] - aste.getPosY()))) {
				//DrawText("Collision Asteroids", 100, 300, 50, WHITE);
				this->postCollisionTrajectoire(aste);
				this->move();
				aste.move();
				return true;
			}
		}
	}
	return false;
}
void Asteroid::postCollisionTrajectoire(Asteroid aste) {
	double tampon1 = a_direction[0];
	double tampon2 = a_direction[1];
	a_direction[0] = aste.getDirX();
	a_direction[1] = aste.getDirY();
	aste.setDirection(tampon1, tampon2);
}



// Code du rendu graphique

void Asteroid::renduAsteroid()
{
	for (int pt = 0; pt < a_enveloppe.size() - 1; pt++) {
		DrawLine(a_position[0]+a_points[a_enveloppe[pt]].get_x(), a_position[1] + a_points[a_enveloppe[pt]].get_y(), a_position[0] + a_points[a_enveloppe[pt+1]].get_x(), a_position[1] + a_points[a_enveloppe[pt+1]].get_y(), LIGHTGRAY);
	}
}

void Asteroid::move() {
	if (a_rayon == 50) {
		a_position[0] += 3 * a_direction[0];
		a_position[1] += 3 * a_direction[1];
	}
	if (a_rayon == 80) {
		a_position[0] += 1 * a_direction[0];
		a_position[1] += 1 * a_direction[1];
	}
}

int Asteroid::getRayon()
{
	return a_rayon;
}


