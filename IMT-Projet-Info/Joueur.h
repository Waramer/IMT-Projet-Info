#pragma once
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include <iostream>
#include <string>

class Joueur
{
public:
	Joueur();
	std :: string getnom();
	int getScore();
	int getBestScore();
	void setNom(std::string nom);
	void setScore(int score);
	void setBestScore(int score);

private:
	std::string m_nom;
	int m_score;
	int m_best_score;
};


#endif JOUEUR_H_INCLUDED 