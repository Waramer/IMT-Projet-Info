#include "Point.h"
#include <random>
#include <iostream>
#include <cmath>

using namespace std;

Point::Point()
{
	p_x = rand() % 61 - 30;
	p_y = rand() % 61 - 30;
}
Point::Point(int x, int y) {
	p_x = x;
	p_y = y;
}

int Point::get_x() {
	return p_x;
}
int Point::get_y() {
	return p_y;
}
void Point::set_x(int x) {
	p_x = x;
}
void Point::set_y(int y) {
	p_y = y;
}
void Point::affiche() {
	cout << "[" << this->get_x() << "," << this->get_y() << "]";
}

float Point::angle(Point p2)
{
	if (get_x() == p2.get_x()) { // si les deux points ont la même abscisse
		if (get_y() < p2.get_y()) {
			return 360; // p2 au dessus
		}
		else if (get_y() > p2.get_y()) {
			return 180; // p2 en dessous
		}
		return 360;
	}
	else
	{
		if (get_x() < p2.get_x()) {
			return 90 - 180 / 3.14159265358979323846 * atan((float)(p2.get_y() - get_y()) / (float)(p2.get_x() - get_x()));
		}
		else if (get_x() > p2.get_x()) {
			return 270 - 180 / 3.14159265358979323846 * atan((float)(p2.get_y() - get_y()) / (float)(p2.get_x() - get_x()));
		}
		return 0;
	}
}

// Points supperposés

bool Point::estEgal(Point p2)
{
	if ((get_x() == p2.get_x()) && (get_y() == p2.get_y())) { return true; }
	return false;
}


