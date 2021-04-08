#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"

class Asteroid
{
public:
	Asteroid(int nb_points, int rayon);
	void affiche();
	int envelopFindInitPoint();
	void envelopFindList();
	std::vector<int> getEnvelopList();
	std::vector<Point> getPoints();
	bool pointDansEnveloppe(Point point);
	void renduAsteroid();
	void setPosition(int x, int y);
	double getPosX();
	double getPosY();
	void move();
	int getRayon();

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
