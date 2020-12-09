#include "Fahrzeug.h"
#include<iostream>
#include<iomanip>
using namespace std;

int Fahrzeug::p_iMaxID = 1;
extern double dGlobaleZeit;
/*
* Default-konstruktor
*/
Fahrzeug::Fahrzeug()
	:p_iID(p_iMaxID), p_sName(""), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(0)
{
	p_iMaxID += 1;
	cout<<"Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;

}


/*
* konstruktor mit gegebenen name
*/
Fahrzeug::Fahrzeug(string name)
	:p_iID(p_iMaxID), p_sName(name), p_dMaxGeschwindigkeit(0), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(0)
{
	p_iMaxID += 1;
	cout << "Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}

/*
* konstruktor mit gegebenen Name und maximaler Geschwindigkeit
*/
Fahrzeug::Fahrzeug(string name, const double maxgeschwindigkeit)
	:p_iID(p_iMaxID), p_sName(name), p_dMaxGeschwindigkeit((maxgeschwindigkeit>0)?maxgeschwindigkeit:0),
	p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dZeit(0)
{
	p_iMaxID += 1;
	cout << "Fahrzeug erzeugt: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}


/*
* Destruktor
*/
Fahrzeug::~Fahrzeug()
{
	p_iMaxID -= 1;
	cout << "\nFahrzeug geloescht: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}


/*
* Daten des Fahrzeuges ausgeben
*/
void Fahrzeug::vAusgeben()
{
	cout << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(15) << p_sName
		//<< resetiosflags(ios::left)
		<< setiosflags(ios::fixed) 
		<< setprecision(2)
		<< setw(17) << dGeschwindigkeit()
		<< setw(18) << p_dGesamtStrecke;
	
}
void Fahrzeug::vAusgeben(ostream& o)
{
	/*
	cout  << setiosflags(ios::left) 
	    << setw(6) << p_iID
		<< setw(23) << p_sName
		 <<setiosflags(ios::fixed)<< setprecision(2)
		<< setw(16) << p_dMaxGeschwindigkeit
		<< setw(8) << p_dGesamtStrecke;
		*/
	o << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(15) << p_sName
		<< setiosflags(ios::fixed) << setprecision(2)
		<< setw(17) << dGeschwindigkeit()
		<< setw(18) << p_dGesamtStrecke;
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
	double dtempZeit = dGlobaleZeit - p_dZeit;
	p_dGesamtStrecke += dtempZeit * dGeschwindigkeit();
	p_dGesamtZeit += dtempZeit;
	p_dZeit = dGlobaleZeit;
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