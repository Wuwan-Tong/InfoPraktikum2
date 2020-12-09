#pragma once
#include"Simulationsobjekt.h"
#include<list>
#include<memory>
#include"Tempolimit.h"

class Fahrzeug;
class Weg:public Simulationsobjekt
{
private:
	
	double p_dLeange;//lange in km
	list<unique_ptr<Fahrzeug>> p_pFahrzeuge;//fahrzeuge aktuelle auf dem Weg befinden
	Tempolimit p_eTempolimit;//max. zulaessige Geschwindigkeit
	
public:
	Weg();
	Weg(const string pname, double pdleange, Tempolimit ptempolimit= Tempolimit::Autobahn);
	~Weg();
	void vSimulieren();
	void vAusgeben()override;
	void vAusgeben(ostream&);
	void vKopf();
	double getTempolimit();
	double getLaenge();
	void vAnnahme(unique_ptr<Fahrzeug>);
	void vAnnahme(unique_ptr<Fahrzeug>,double);
	friend class Streckenende;
};
