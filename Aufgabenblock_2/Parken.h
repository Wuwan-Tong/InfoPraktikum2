#pragma once
#include"Verhalten.h"
#include"Tempolimit.h"
class Parken:public Verhalten
{
private:
	double p_dStart;//startzeitpunkt des Fahrzeugs
public:
	Parken();
	Parken(Weg& weg, double p_dStart=0);
	~Parken();
	double dStrecke(Fahrzeug& , double )override;

};

