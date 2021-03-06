#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"

/*Classe cod?e par Quentin Delezenne */

class Asteroid
{
public:
	Asteroid(int nb_points, int rayon);

	int envelopFindInitPoint();
	void envelopFindList();
	bool pointDansEnveloppe(Point point);
	bool collisionEntreAsteroid(Asteroid aste);
	void postCollisionTrajectoire(Asteroid aste);
	void renduAsteroid();
	void move();									//avec contribution de Hugo Vanhille

	void affiche();

	std::vector<int> getEnvelopList();
	std::vector<Point> getPoints();
	int getRayon();
	void setPosition(int x, int y);
	void setDirection(double dirX, double dirY);
	double getPosX();
	double getPosY();
	double getDirX();
	double getDirY();

private:
	std::vector<Point> a_points;
	std::vector<int> a_enveloppe;
	int a_rayon;
	int a_nbPoints;
	double a_position[2];
	int a_vitesse;
	double a_direction[2];
};
#endif ASTEROID_H_INCLUDED 
