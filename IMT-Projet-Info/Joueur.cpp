#include "Joueur.h"


Joueur::Joueur() {
	m_score = 0;
	m_best_score = 0;
}

std :: string Joueur :: getnom() {
	return m_nom ;
}
int Joueur :: getScore() {
	return m_score;
}
int Joueur :: getBestScore() {
	return m_best_score;
}

void Joueur::setNom(std::string nom) {
	m_nom = nom;
}
void Joueur::setScore(int score) {
	m_score = score;
}
void Joueur::setBestScore(int score) {
	m_best_score = score;
}