#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"

class Asteroid
{
public :
	Asteroid(int nb_points);
	void affiche();
	float direction(int p1, int p2);
	int envelopFindInitPoint();

private:
	std::vector<Point> a_points;
	std::vector<int> a_enveloppe;
	int a_nbPoints;
	int a_Xpos;
	int a_Ypos;
};

#endif ASTEROID_H_INCLUDED 
