#pragma once
#include "Fahrzeug.h"
class Fahrrad : public Fahrzeug
{
private:

public:
	Fahrrad();
	Fahrrad(string name);
	Fahrrad(string name, const double maxgeschwindigkeit);
	~Fahrrad();
	double dGeschwindigkeit()const;
	void vZeichen(const Weg&)const override;
};

