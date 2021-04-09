#pragma once
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "Asteroid.h"
#include "Point.h"
#include "Tir.h"

class Jeu
{
public:
	Jeu();
	void nextFrame();
	void avancement(int curs_x, int curs_y, double angle);
	void avancementCurseur(int curs_x, int curs_y, double angle);
	void avancementTirs(int curs_x, int curs_y, double angle);
	void avancementAsteroid();
	bool collisionCurseur(int curs_x, int curs_y, double angle);
	bool pointDansCurseur(Point point);

	void tirsAuBut();

private:
	std::vector<Asteroid> j_asteroids;
	std::vector<Tir> j_tirs;
	std::vector<Point>j_curseur;
	int j_timer;
	int j_nbAsteroids;
	bool j_etat;

};
#endif