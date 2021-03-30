#include <iostream>
#include "Asteroid.h"
#include "raylib.h"

using namespace std;

void main() {
	Asteroid asteroid1;
	int* a = asteroid1.getPosition();
	cout << a[0] <<";"<<a[1];

}