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
	while (!WindowShouldClose()) {
		EnableCursor();
		BeginDrawing();
		ClearBackground(BLACK);
		int test = MeasureText("Asteroids", 30);
		DrawText("Asteroids", GetScreenWidth() * 0.5 - (test * 0.5), GetScreenHeight() * 0.05, 30, WHITE);
		DrawLine(0, GetScreenHeight() * 0.1, GetScreenWidth(), GetScreenHeight() * 0.1, WHITE);
		EndDrawing();
		Vector2 farm;
		farm.x = GetScreenWidth() * 0.2;
		farm.y = GetScreenHeight() * 0.2;

		float angle = GetGestureDragAngle();
		DrawPolyLines(farm, 7, 30, angle, WHITE);
		double pi = M_PI;

		int sourisx = GetMouseX();
		int sourisy = GetMouseY();
		float x = GetScreenWidth() * 0.5;
		float y = GetScreenHeight() * (float)0.50;

		if (sourisx == x) {
			if (sourisy < y) {
				angle = 360;
			}
			else if (sourisy > y) {
				angle = 180;
			}
			else angle = 180;

		}
		else {
			if (sourisx < x) {
				angle = 90 - 180 / pi *
			}
		}


		DrawPolyLines(Vector2{ x, y } , 3, 20, angle, WHITE);

	}
	CloseWindow();
}


