#pragma once
class Weg;
class Fahrzeug;
class Verhalten
{
protected:
	Weg* p_pWeg;

public:
	Verhalten();
	Verhalten(Weg& weg);
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall)=0;
	Weg* get_weg();

};

