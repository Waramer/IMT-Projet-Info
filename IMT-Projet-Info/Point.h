#pragma once
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <string>

class Point
{
private:
	int p_x;
	int p_y;

public:
	Point(int rayon);
	Point(int x, int y);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
	void affiche();
	double angle(Point p2);
	bool estEgal(Point p2);
};
#endif

