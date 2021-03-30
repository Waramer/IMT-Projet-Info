#include "Asteroid.h"
#include <random>
#include <iostream>

Asteroid::Asteroid()
{
	srand((unsigned)time(NULL));

	for (int i = 0;i < 20;i++) 
	{
		for (int j = 0; j < 2; j++)
		{
			
			m_forme[i][j] = rand()%10-5;
		}
	}

	//initialise la position de l'astéroide sur le bord de l'écran
	int const TAILLE_FENETRE=1000;         //à modifier avec la valeur max de la fenètre
	int a = rand() % TAILLE_FENETRE;  
	std :: cout << a <<std::endl;
	int b = rand() %2;
		if (b == 0)
		{
			m_position[0] =a;
			if(rand()%2==0)
				m_position[1] = TAILLE_FENETRE-1;
			else
				m_position[1] = 0;
		}
		else
		{
			m_position[1] = a;
			if (rand() % 2 == 0)
				m_position[0] = TAILLE_FENETRE-1;
			else
				m_position[0] = 0;
		}

}

void Asteroid::affiche()
{
	std::cout << "la liste des points est :";
	for (int i = 0; i < 20; i++)
	{
		std::cout << "[" << m_forme[i][0] << "," << m_forme[i][1] << "], ";
	}

}

int* Asteroid::getPosition()
{
	return m_position;
}
