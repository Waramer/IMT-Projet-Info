#pragma once
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <iostream>
#include <string>

class Asteroid
{
public :
	Asteroid();
	void affiche();


private:
	int m_position[2];
	int m_forme[20][2];
	int m_nb_points;

};

#endif ASTEROID_H_INCLUDED 
