#pragma once
#include"Simulationsobjekt.h"
#include<list>
#include<memory>
#include"Tempolimit.h"
#include"vertagt_liste - Vorlage.h"

class Fahrzeug;
class Weg:public Simulationsobjekt
{
private:
	
	double p_dLeange;//lange in km
	list<unique_ptr<Fahrzeug>> p_pFahrzeuge;//fahrzeuge aktuelle auf dem Weg befinden
	//vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
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
	string sGetName()const;
	double dGetLeange()const;
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

};
