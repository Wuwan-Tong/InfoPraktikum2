#pragma once
#include<exception>

using namespace std;
class Fahrzeug;
class Weg;
class Fahrausnahme: exception
{
protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
public:
	Fahrausnahme(Fahrzeug&, Weg&);
	virtual void vBearbeiten()=0;

};

