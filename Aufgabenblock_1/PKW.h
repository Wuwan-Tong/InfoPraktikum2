#pragma once
#include "Fahrzeug.h"
class PKW : public Fahrzeug
{
private:
	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;
public:
	PKW();
	PKW(string name);
	PKW(string name, const double maxgeschwindigkeit);
	PKW(string name, const double maxgeschwindigkeit, double verbrauch, double tankvolumen=551);
	~PKW();
	double dTanken(double dMenge = 0.0)override;
	void vSimulieren()override;
	void vAusgeben();
	void vAusgeben(ostream&)override;	
};
ostream& operator<<(ostream& o, PKW& f);
