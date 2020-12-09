#pragma once
#include<string>
#include"Simulationsobjekt.h"
#include "Verhalten.h"
#include<memory>
using namespace std;

class Fahrzeug: public Simulationsobjekt
{
protected://private bei Vererbung nicht erlaubt
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	shared_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke;
	
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
	double dGetGesamtStrecke();
	double dGetAbschnittStrecke();
	void vNeueStrecke(Weg&);
	void vNeueStrecke(Weg&, double);

	friend class Parken;
	friend class Weg;
	friend class Streckenende;
	friend class Losfahren;
};
ostream& operator<<(ostream&, Fahrzeug&);//3 Operanden sind nicht erlaubt.Wenn innerhalb class Fahrzeug, 
											   //es gibt 3 Operanden, also ostream&, const Fahrzeug& und this
