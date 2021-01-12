#pragma once
#include"Fahrausnahme.h"
class Streckenende:public Fahrausnahme
{
public:
	Streckenende(Fahrzeug&, Weg&);
	void vBearbeiten();
};

