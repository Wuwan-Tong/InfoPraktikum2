#pragma once
#include<string>
using namespace std;
class Fahrzeug
{
protected://private bei Vererbung nicht erlaubt
	string p_sName;
    const int p_iID;
	static int p_iMaxID;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dZeit;
public:
	Fahrzeug();
	Fahrzeug(string name);
	Fahrzeug(string name, const double maxgeschwindigkeit);
	virtual ~Fahrzeug();	
	virtual void vAusgeben();
	virtual void vAusgeben(ostream&);
	virtual void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge);
	virtual double dGeschwindigkeit();
	bool operator<(const Fahrzeug&);
	virtual void operator=(Fahrzeug&);
};
ostream& operator<<(ostream&, Fahrzeug&);//3 Operanden sind nicht erlaubt.Wenn innerhalb class Fahrzeug, 
                                               //es gibt 3 Operanden, also ostream&, const Fahrzeug& und this
