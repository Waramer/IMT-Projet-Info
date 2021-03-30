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
	Asteroid(int nb_points);
	void affiche();
	int envelopFindInitPoint();
	void envelopFindList();
	std::vector<int> getEnvelopList();
	int* getPosition();
	int* newPosition();

private:
	std::vector<Point> a_points;
	std::vector<int> a_enveloppe;
	int a_nbPoints;
	int a_position[2];
	int a_nb_points;
	int a_vitesse;
	int a_direction[5][5];
};
#endif ASTEROID_H_INCLUDED 
