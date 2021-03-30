#include <iostream>
#include "Asteroid.h"
#include "Point.h"
#include <random>

using namespace std;

void main() {
	Asteroid aste(20);
	cout << "point de depart de l'enveloppe : " << aste.envelopFindInitPoint() << endl;
	aste.envelopFindList();
	vector<int> liste = aste.getEnvelopList();
	cout << "[" << liste[0];
	for (int k = 1; k < liste.size(); k++) {
		cout << "," << liste[k];
	}
	cout << "]" << endl;
}