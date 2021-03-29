#include "Asteroid.h"
#include <random>
#include <functional>
#include<chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

Asteroid::Asteroid()
{
	//std::default_random_engine a;
	//std::uniform_int_distribution<int> distrib{ 1,6 };
	srand((unsigned)time(NULL));

	for (int i = 0;i < 20;i++) 
	{
		for (int j = 0; j < 2; j++)
		{
			
			m_forme[i][j] = rand()%10-5;
		}
	}

	m_position[0] = 0;
	m_position[1] = 0;
}

void Asteroid::affiche()
{
	std::cout << "la liste des points est :";
	for (int i = 0; i < 20; i++)
	{
		std::cout << "[" << m_forme[i][0] << "," << m_forme[i][1] << "], ";
	}

}