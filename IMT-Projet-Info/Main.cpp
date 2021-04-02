#include <iostream>
#include "Asteroid.h"
#include "Point.h"
#include <random>

using namespace std;

void main() {
	Asteroid aste(10);
	aste.affiche();
	aste.envelopFindList();

	vector<int> liste = aste.getEnvelopList();

	cout << "L'enveloppe trouvee est : [" << liste[0];
	for (int k = 1; k < liste.size(); k++) {
		cout << "," << liste[k];
	}
	cout << "]" << endl;

	Point test(-4,4);
	test.affiche();
	if (aste.pointDansEnveloppe(test)) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
}