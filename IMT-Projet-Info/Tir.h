#pragma once
#ifndef TIR_H_INCLUDED
#define TIR_H_INCLUDED

#include "Point.h"
//Classe cod?e par Cl?ment Kieffer et Quentin Delezenne
class Tir
{
public:
	Tir(double x, double y, double angle);
	void move();
	void rendu();
	double getX();
	double getY();

private:
	double position[2];
	double direction[2];
};
#endif



