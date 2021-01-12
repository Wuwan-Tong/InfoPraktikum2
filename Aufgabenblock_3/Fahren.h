#pragma once
#include"Verhalten.h"
class Fahren :public Verhalten
{
public:
	Fahren();
	Fahren(Weg& weg);
	~Fahren();
	double dStrecke(Fahrzeug&, double)override;
};

