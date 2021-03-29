#include "Point.h"
#include <random>
#include <iostream>
#include <ctime>

using namespace std;

Point::Point()
{
	p_x = rand() % 11 - 5;
	p_y = rand() % 11 - 5;
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