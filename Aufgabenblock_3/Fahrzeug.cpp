#include "Fahrzeug.h"
#include<iostream>
#include<iomanip>
#include<memory>
#include"Weg.h"
#include"Fahren.h"
#include"Parken.h"
using namespace std;


extern double dGlobaleZeit;
/*
* Default-konstruktor
*/
Fahrzeug::Fahrzeug()
	:Simulationsobjekt(), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), 
	p_dGesamtZeit(0), p_dAbschnittStrecke(0)
{
	cout << "Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;

}


/*
* konstruktor mit gegebenen name
*/
Fahrzeug::Fahrzeug(string name)
	:Simulationsobjekt(name), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), 
	p_dGesamtZeit(0), p_dAbschnittStrecke(0)
{
	cout << "Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}

/*
* konstruktor mit gegebenen Name und maximaler Geschwindigkeit
*/
Fahrzeug::Fahrzeug(string name, const double maxgeschwindigkeit)
	:Simulationsobjekt(name), p_dMaxGeschwindigkeit((maxgeschwindigkeit > 0) ? maxgeschwindigkeit : 0),
	p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0)
{
	cout << "Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}


/*
* Destruktor
*/
Fahrzeug::~Fahrzeug()
{
	
}


/*
* Daten des Fahrzeuges ausgeben
*/
void Fahrzeug::vAusgeben()
{
	Simulationsobjekt::vAusgeben();
	//cout << setiosflags(ios::left) << setw(6) << p_iID
		//<< setw(23) << p_sName
	cout<< resetiosflags(ios::left) << setiosflags(ios::fixed) << setprecision(2)
		<< setw(16) << dGeschwindigkeit()
		<< setw(8) << p_dGesamtStrecke;

}
void Fahrzeug::vAusgeben(ostream& o)
{
	o << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(23) << p_sName
		<< resetiosflags(ios::left) << setiosflags(ios::fixed) << setprecision(2)
		<< setw(16) << dGeschwindigkeit()
		<< setw(8) << p_dGesamtStrecke;
	return;
}
/*
* operator << ueberladung
*/
ostream& operator<<(ostream& o, Fahrzeug& f)
{
	f.vAusgeben(o);
	return o;
}

/*
* Kopf des Ausgebatabelles ausgeben
*/
void Fahrzeug::vKopf()
{
	cout << setiosflags(ios::left);
	cout << setw(6) << "ID"
		<< setw(10) << "Name"
		<< setw(20) << "Geschwindigkeit"
		<< setw(16) << "Gesamtstrecke"
		<< setw(20) << "Gesamtverbrauch"
		<< setw(25) << "aktueller Tankinhalt"
		<< endl;
	cout << "-----------------------------------------------------------------------------" << endl;
}


/*
* die Funktion sorgt, dass die Fahrzeuge sich fortbewegen
*/
void Fahrzeug::vSimulieren()
{
	if (p_dZeit == dGlobaleZeit)//falls mehrmal innerhalb eines Zeitschritts aufgerufen wird
		return;
	double dZeitIntervall = dGlobaleZeit - p_dZeit;
	double dTempStrecke= p_pVerhalten->dStrecke(*this, dZeitIntervall);
	p_dGesamtStrecke += dTempStrecke;
	p_dAbschnittStrecke += dTempStrecke;
	p_dGesamtZeit += dZeitIntervall;
	p_dZeit = dGlobaleZeit;
	Weg* weg = p_pVerhalten->get_weg();
	vZeichen(*weg);
}


/*
* Die Funktion sorgt um Tanken. PKW: tanken,geben wie viel getankt zuruck, Fahrrad: tanken nicht, geben 0 Liter zurueck
*/
double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

/*
* Die Funktion gibt die Geschwindigkeit des Fahrzeuges zurueck.
* PKW:return maxGeschwindigkeit,Fahrrad: wird in Fahrrad.cpp berechnet
*/
double Fahrzeug::dGeschwindigkeit()
{
	return p_dMaxGeschwindigkeit;
}
/*
* operator ueberladung,entscheidet, ob die gesamte Strecke des gegebenen Fahrzeuges grosser ist
*/
bool Fahrzeug::operator<(const Fahrzeug& f)
{
	if (this->p_dGesamtStrecke < f.p_dGesamtStrecke)
		return true;
	else
		return false;
}
/*
* operator ueberladung,this fahrzeug in gegebene Fahrzeug zuweisen
*/
void Fahrzeug::operator =(Fahrzeug& f)
{
	this->p_sName = f.p_sName + "new";
	this->p_dGesamtStrecke = f.p_dGesamtStrecke;
	this->p_dMaxGeschwindigkeit = f.p_dMaxGeschwindigkeit;
	this->p_dGesamtZeit = f.p_dGesamtZeit;
}

double Fahrzeug::dGetGesamtStrecke()
{
	return p_dGesamtStrecke;
}

double Fahrzeug::dGetAbschnittStrecke()
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten =make_shared<Fahren>(weg);
	this->p_dAbschnittStrecke = 0;
	this->p_dGesamtZeit = 0;
	this->p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double pdstart)
{
	p_pVerhalten = make_shared<Parken>(weg, pdstart);
	this->p_dAbschnittStrecke = 0;
	this->p_dGesamtZeit = 0;
	this->p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vZeichen(const Weg&) const
{
}
istream& Fahrzeug::vEinlesen(istream& i)
{
	//i >> p_sName;
	
	//cout << "enter the MaxGeschwindigkeit in km/h: ";
	Simulationsobjekt::vEinlesen(i) >> p_dMaxGeschwindigkeit;
	return i;
}


