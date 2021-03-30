#define _USE_MATH_DEFINES
#include <raylib.h>
#include <iostream>
#include "Ecran.h"
#include <cmath>

using namespace std;

Ecran::Ecran() 

{
	int width = 900;
	int height = 600;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(width, height, "test");

	SetWindowPosition(0, 100);

	MaximizeWindow();

	cout << "\n" << " La taille est : " << height << width << "\n";

	double x = GetScreenWidth();

	double y = GetScreenHeight();

	Vector2 pointeur = { x*0.5, y*0.5 };



	while (!WindowShouldClose()) {
		EnableCursor();
		BeginDrawing();
		ClearBackground(BLACK);
		int test = MeasureText("Asteroids", 30);
		DrawText("Asteroids", GetScreenWidth() * 0.5 - (test * 0.5), GetScreenHeight() * 0.05, 30, WHITE);

		DrawLine(0, GetScreenHeight() * 0.1, GetScreenWidth(), GetScreenHeight() * 0.1, WHITE);
		EndDrawing();


		float angle = GetGestureDragAngle();

		double pi = M_PI;

		int sourisx = GetMouseX();
		int sourisy = GetMouseY();

		if (sourisx == pointeur.x) {
			if (sourisy < pointeur.y) {
				angle = 360;
			}
			else if (sourisy > pointeur.y) {
				angle = 180;
			}
			else angle = 180;

		}
		else {
			if (sourisx > pointeur.x) {
				angle = 360 - (90 - 180 / pi * atan((float)(pointeur.y - sourisy) / (float)(pointeur.x - sourisx)));
			}
			else if (sourisx < pointeur.x) {
				angle =360 - ( 270 - 180 / pi * atan((float)(pointeur.y - sourisy) / (float)(pointeur.x - sourisx)));

			}else
			angle = 0;
		}
		
		cout << (int)y * 0.1 << "\n";
		if (IsKeyDown(265) && ((int)pointeur.y == (int)(y*0.1) || (int)(pointeur.y - 1) == (int)(y*0.1))) pointeur.y = y;
		else if(IsKeyDown(265))pointeur.y -= 2;

		if (IsKeyDown(262) && pointeur.x == x)pointeur.x =0;
		else if(IsKeyDown(262))pointeur.x += 2;

		if (IsKeyDown(263) && pointeur.x == 0)pointeur.x=x;
		else if(IsKeyDown(263))pointeur.x -= 2;

		if (IsKeyDown(264) && ((int)pointeur.y == y || (int)(pointeur.y+1 == y))) {
			pointeur.y = y * 0.1;
		}
		else if(IsKeyDown(264))pointeur.y += 2 ;


	
		
		

		DrawPolyLines( pointeur, 3, 20, angle, WHITE);

	}
	CloseWindow();
}


