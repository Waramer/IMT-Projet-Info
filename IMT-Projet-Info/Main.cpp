#include <iostream>
#include <raylib.h>
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

	aste.setPosition(350, 250);

	int height = GetScreenHeight() * 0.05;
	int width = GetScreenWidth() * 0.05;
	cout <<  "\n"<<" La taille est : " << height << width;
	InitWindow(700, 500,"Ceci est une fenetre");
	while (!WindowShouldClose()) { 
		EnableCursor(); 
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Vous etes un genie", 50, 40, 30, WHITE);
		aste.renduAsteroid();
		EndDrawing();
	}
	CloseWindow();
}