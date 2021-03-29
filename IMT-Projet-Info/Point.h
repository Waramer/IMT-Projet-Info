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
	Point();
	Point(int x, int y);
	int get_x();
	int get_y();
	void affiche();
};
#endif

