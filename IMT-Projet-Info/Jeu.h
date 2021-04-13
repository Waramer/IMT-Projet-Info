#pragma once
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "Asteroid.h"
#include "Point.h"
#include "Tir.h"
#include "Joueur.h"

//Classe codée par Quentin Delezenne, et Hugo Vanhille (sons)
class Jeu
{
public:
	Jeu(int difficult, Joueur j);
	void nextFrame();
	void avancement(int curs_x, int curs_y, double angle);    //avec contribution de Louis Delacour
	void avancementTirs(int curs_x, int curs_y, double angle);
	void avancementAsteroid();
	bool collisionCurseur(int curs_x, int curs_y, double angle);
	bool pointDansCurseur(Point point);
	Joueur j_joueur;
	void tirsAuBut();										//avec contribution de louis Delacour

private:
	std::vector<Asteroid> j_asteroids;
	std::vector<Tir> j_tirs;
	std::vector<Point>j_curseur;
	int j_timer;
	int j_nbAsteroids;
	bool j_etat;
	int j_difficulte;
	int j_tirColldown;


};
#endif