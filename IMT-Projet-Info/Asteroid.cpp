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
	a_Xpos = 0;
	a_Ypos = 0;
}

void Asteroid::affiche()
{
	cout << "Voici les points de l'Asteroid : " << endl;
	for (int pt = 0; pt < a_nbPoints; pt++) {
		a_points[pt].affiche();
		cout << endl;
	}
}


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
	cout << "debut recherhce enveloppe" << endl;
	int initPoint = this->envelopFindInitPoint();
	int actualPoint = initPoint;
	bool retour = false;
	a_enveloppe.push_back(actualPoint); // d�but de l'enveloppe
	while (true){
		int angle = 360;
		int nextPoint = actualPoint;
		for (int pt = 0; pt < a_nbPoints; pt++) {
			if (!(a_points[actualPoint].estEgal(a_points[pt]))) { // on consid�re uniquement les points diff�rents de celui actuel pour poursuivre l'enveloppe
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