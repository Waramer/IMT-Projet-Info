#include "Asteroid.h"
#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

Asteroid::Asteroid(int nb_points)
{
	srand((unsigned)time(0));
	a_nbPoints = nb_points;
	a_points.reserve(nb_points);
	for (int pt = 0; pt < a_nbPoints; pt++) {
		a_points.push_back(Point());
	}
	//initialise la position de l'astéroide sur le bord de l'écran
	int const TAILLE_FENETRE = 1000;         //à modifier avec la valeur max de la fenètre
	int a = rand() % TAILLE_FENETRE;
	int b = rand() % 2;
	if (b == 0)
	{
		a_position[0] = a;
		if (rand() % 2 == 0)
			a_position[1] = TAILLE_FENETRE - 1;
		else
			a_position[1] = 0;
	}
	else
	{
		a_position[1] = a;
		if (rand() % 2 == 0)
			a_position[0] = TAILLE_FENETRE - 1;
		else
			a_position[0] = 0;
	}
}

int* Asteroid::getPosition()
{
	return a_position;
}

int* Asteroid::newPosition()
{
	return nullptr;
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
		int angle = 360;
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


// Code de collision
/*
bool Point::estDansEnveloppe(vector<int> enveloppe,vector<Point> points) {
	// V1
	// On va tester si le point satisfait toutes les conditions pour se trouver dans l'enveloppe, i.e. se trouve à l'interieur de tous les segments.
	// Si le point se trouve "à gauche" du segment, quand on le parcours, alors il ne se trouve pas dans l'enveloppe (car elle est créée en sesn horaire).
	for (int pt = 0 ; pt < enveloppe.size() - 1 ; pt++) {
		// nous regardons ici le segment entre deux point consécutifs
		Point p1 = points[pt]; // première extrémité du segment
		Point p2 = points[pt + 1]; // deuxième extrémité du segment

		float alpha = p1.angle(p2) - (angle(p1) - 180); // angle entre (p1,point à tester) et (p1,p2)  =  angle de p1 vers p2 - angle de p1 vers le point à tester

		if (alpha >= 0) { // équivalent à "le point est à gauche du segment lorsqu'on le regarde en étant sur p1 et en regardant vers p2 en parcourant l'enveloppe en sens horaire"
			return false;
		}
	}
	return true;

	// V2
	// On va tester si le point satisfait toutes les conditions pour se trouver dans l'enveloppe, i.e. se trouve à l'interieur de tous les segments.
	// Si le point se trouve "à gauche" du segment, quand on le parcours, alors il ne se trouve pas dans l'enveloppe (car elle est créée en sesn horaire).
	for (int pt = 0; pt < a_enveloppe.size() - 1; pt++) {
		// nous regardons ici le segment entre deux point consécutifs
		int alpha = (a_points[a_enveloppe[pt]].angle(a_points[a_enveloppe[pt + 1]]) - (point.angle(a_points[a_enveloppe[pt]]) - 180));
		cout << pt << ";" << alpha << endl;
		if ( alpha >= 0) { // équivalent à "le point est à gauche du segment lorsqu'on le regarde en étant sur p1 et en regardant vers p2 en parcourant l'enveloppe en sens horaire"
			return false;
		}
	}
	return true;



}
*/
