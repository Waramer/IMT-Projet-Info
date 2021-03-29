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

float Asteroid::direction(int p1, int p2)
{
	if (((float)a_points[p1].get_x() - (float)a_points[p2].get_x()) == 0) {
		return 0;
	}
	float direct = ((float)a_points[p1].get_y() - (float)a_points[p2].get_y())/((float)a_points[p1].get_x() - (float)a_points[p2].get_x()); // Calcul du coefficient de la droite entre les deux points
	return direct;
}

int Asteroid::envelopFindInitPoint() {
	int m = 0;
	for (int n = 1; n < a_nbPoints; n++) {
		if (a_points[n].get_x() < a_points[m].get_x()) {
			m = n;
		}
	}
	return m;
}