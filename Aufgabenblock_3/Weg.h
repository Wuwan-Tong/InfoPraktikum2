#pragma once
#include"Simulationsobjekt.h"
#include<list>
#include<memory>
#include"Tempolimit.h"
#include"vertagt_liste - Vorlage.h"

class Fahrzeug;
class Kreuzung;
class Weg:public Simulationsobjekt
{
private:
	
	double p_dLeange;//lange in km
	list<unique_ptr<Fahrzeug>> p_pFahrzeuge;//fahrzeuge aktuelle auf dem Weg befinden
	//vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;//max. zulaessige Geschwindigkeit

	bool p_bUeberholverbot;
	double p_dVirtuelleSchranke = numeric_limits<double>::max();
	weak_ptr<Weg> p_pRueckWeg;
	const weak_ptr<Kreuzung> p_pZielKreuzung;

public:
	Weg();
	Weg(const string pname, double pdleange, Tempolimit ptempolimit = Tempolimit::Autobahn, bool pUeberholverbot=true);
	Weg(const string pname, double pdleange, weak_ptr<Kreuzung> pKreuzung= weak_ptr<Kreuzung>(),
		Tempolimit ptempolimit = Tempolimit::Autobahn, bool pUeberholverbot = true);
	//default parameter shoule at the end of the list
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
	double dGetVirtuelleSchranke();

	Weg& getRueckWeg();
	Kreuzung& getZielKreuzung();
	void setRueckWeg(weak_ptr<Weg>);

};
