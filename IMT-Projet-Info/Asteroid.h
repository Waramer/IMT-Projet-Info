#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <iostream>
#include <string>


class Asteroid
{
public:
	Asteroid();
	void affiche();
	int* getPosition();
	int* newPosition();

private:
	int m_forme[20][2];
	int m_position[2];
	int m_nb_points;
	int m_vitesse;
	int direction[5][5];

};

#endif ASTEROID_H_INCLUDED 
