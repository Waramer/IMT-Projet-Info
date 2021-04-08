#include "Tir.h"
#include "Point.h"
#include "raylib.h"

Tir::Tir(double x, double y, double angle)
{
	point = Point(x, y);
	direction[0] = sin(-angle * 3.14159 / 180);
	direction[1] = cos(-angle * 3.14159 / 180);
}

void Tir::move()
{
	point.set_x(point.get_x() + direction[0]);
	point.set_y(point.get_y() + direction[1]);
}

void Tir::rendu()
{
	DrawCircle(point.get_x(), point.get_y(),2,WHITE);
}

Point Tir::getPoint()
{
	return point;
}
