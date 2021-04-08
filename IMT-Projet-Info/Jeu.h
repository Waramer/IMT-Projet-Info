#pragma once
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "Asteroid.h"
#include "Point.h"

class Jeu
{
public:
	Jeu();
	void nextFrame();
	void avancement();
	void renduAsteroids();
	bool collisionCurseur(int curs_x, int curs_y, double angle);

	bool pointDansCurseur(Point point);

private:
	std::vector<Asteroid> j_asteroids;
	std::vector<Point>j_curseur;
	int j_timer;
	int j_nbAsteroids;
	bool j_etat;

};
#endif