#pragma once
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include <iostream>
#include <string>

//Classe codée par Hugo Vanhille et Louis Delacour
class Joueur
{
public:
	Joueur();
	std :: string getnom();
	int getScoreEasy();
	int getScoreMedium();
	int getScoreHard();

	void setNom(std::string nom);
	void setScoreEasy(int score);
	void setScoreMedium(int score);
	void setScoreHard(int score);


private:
	std::string m_nom;
	int m_scoreEasy;
	int m_scoreMedium;
	int m_scoreHard;

};


#endif JOUEUR_H_INCLUDED 