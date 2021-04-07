#include <iostream>
#include <raylib.h>
#include "Asteroid.h"
#include "Point.h"
#include <random>
#include "physac.h"

using namespace std;

void main() {
	Asteroid asteroid1(20);
	asteroid1.affiche();
	asteroid1.envelopFindList();
	vector<int> liste = asteroid1.getEnvelopList();
	cout << "L'enveloppe trouvee est : [" << liste[0];
	for (int k = 1; k < liste.size(); k++) {
		cout << "," << liste[k];
	}
	cout << "]" << endl;

	int height = GetScreenHeight() * 0.05;
	int width = GetScreenWidth() * 0.05;
	cout <<  "\n"<<" La taille est : " << height << width;
	InitWindow(700, 500,"Ceci est une fenetre");
	while (!WindowShouldClose()) { 
		EnableCursor(); 
		// Initialize physics and default physics bodies
		InitPhysics();

		BeginDrawing();
		//ClearBackground(RED);
		//DrawText("Vous etes un genie", 50, 40, 30, WHITE);
		ClearBackground(WHITE);
		EndDrawing();
	}
	CloseWindow();
}