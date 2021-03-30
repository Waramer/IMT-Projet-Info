#include <iostream>
#include <raylib.h>
#include "Asteroid.h"
#include "Point.h"
#include <random>

using namespace std;

void main() {
	Asteroid asteroid1;
	asteroid1.affiche();
	int height = GetScreenHeight() * 0.05;
	int width = GetScreenWidth() * 0.05;
	cout <<  "\n"<<" La taille est : " << height << width;
	InitWindow(700, 500,"Ceci est une fenetre");
	while (!WindowShouldClose()) { 
		EnableCursor(); 
		BeginDrawing();
		ClearBackground(RED);
		DrawText("Vous etes un genie", 50, 40, 30, WHITE);
		EndDrawing();
	}
	CloseWindow();
}