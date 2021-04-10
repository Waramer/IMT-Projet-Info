#include "Tir.h"
#include "Point.h"
#include "raylib.h"

Tir::Tir(double x, double y, double angle)
{
	position[0] = x;
	position[1] = y;
	direction[0] = sin(-angle * 3.14159 / 180);
	direction[1] = cos(-angle * 3.14159 / 180);
}

void Tir::move()
{
	position[0] += 7*direction[0];
	position[1] += 7*direction[1];
}

void Tir::rendu()
{
	DrawCircle(position[0], position[1],2,WHITE);
}

double Tir::getX()
{
	return position[0];
}

double Tir::getY()
{
	return position[1];
}
