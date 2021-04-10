#include "Joueur.h"


Joueur::Joueur() {
	m_scoreEasy = 0;
	m_scoreMedium = 0;
	m_scoreHard = 0;

}

std :: string Joueur :: getnom() {
	return m_nom ;
}
int Joueur :: getScoreEasy() {
	return m_scoreEasy;
}
int Joueur :: getScoreMedium() {
	return m_scoreMedium;
}
int Joueur::getScoreHard() {
	return m_scoreHard;
}

void Joueur::setNom(std::string nom) {
	m_nom = nom;
}
void Joueur::setScoreEasy(int score) {
	m_scoreEasy = score;
}
void Joueur::setScoreMedium(int score) {
	m_scoreMedium = score;
}
void Joueur::setScoreHard(int score) {
	m_scoreHard = score;
}
