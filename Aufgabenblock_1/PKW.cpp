#include "PKW.h"
#include<iostream>
#include<iomanip>

extern double dGlobaleZeit;
/*
* Default-konstruktor
*/
PKW::PKW()
	:Fahrzeug(), p_dVerbrauch(0), p_dTankvolumen(0), p_dTankinhalt(0)
{
}
/*
* konstruktor mit gegebenen Name
*/
PKW::PKW(string name)
	: Fahrzeug(name), p_dVerbrauch(0), p_dTankvolumen(0), p_dTankinhalt(0)
{
}
/*
* konstruktor mit gegebenen Name und maximaler Geschwindigkeit
*/
PKW::PKW(string name, const double maxgeschwindigkeit)
	: Fahrzeug(name, maxgeschwindigkeit), p_dVerbrauch(0), p_dTankvolumen(0), p_dTankinhalt(0)
{
}


/*
* konstruktor mit gegebenen Name, maximaler Geschwindigkeit und gegebenen Tankvolumen(default: 551)
*/
PKW::PKW(string name, const double maxgeschwindigkeit, double verbrauch, double tankvolumen)
	: Fahrzeug(name, maxgeschwindigkeit), p_dVerbrauch(verbrauch),
	p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen / 2)
{
}

/*
* Destruktor
*/
PKW::~PKW()
{
}


double PKW::dTanken(double dMenge)
{
	double dGetankt=0;
	//Wenn kein Wert uebergeben,also dMenge=0.0,soll vollgetankt werden
	if (dMenge == 0)
	{
		dGetankt = p_dTankvolumen;
		p_dTankinhalt = p_dTankvolumen;
	}
	else if (dMenge > 0)
	{
		dGetankt = dMenge;
		if (dMenge > p_dTankvolumen - p_dTankinhalt)//zu viel getankt
		{
			dGetankt = p_dTankvolumen - p_dTankinhalt;
			p_dTankinhalt = p_dTankvolumen;
		}
		else p_dTankinhalt += dGetankt;
	}
	return dGetankt;
}

/*
* Die Funktion simulieren die Bewegung des PKWs. PKW stopp wenn der Tanke leer ist, bis wieder nachgetankt
*/
void PKW::vSimulieren()
{
	if (p_dZeit == dGlobaleZeit)//falls mehrmal innerhalb eines Zeitschritts aufgerufen wird
		return;
	double dZeitIntervall = dGlobaleZeit - p_dZeit;
	//double dGeschwindigkeit = p_dMaxGeschwindigkeit;
	if (p_dTankinhalt > dZeitIntervall * p_dMaxGeschwindigkeit / 100 * p_dVerbrauch)//genug Tanke
	{
		Fahrzeug::vSimulieren();
		p_dTankinhalt -= dZeitIntervall * p_dMaxGeschwindigkeit / 100 * p_dVerbrauch;
	}
	else//der Tanke nicht genug
		p_dZeit = dGlobaleZeit;
}



/*
* Daten des PKWs mit operator ueberladung ausgeben
*/
void PKW::vAusgeben()
{
	Fahrzeug::vAusgeben();
	double dGesamtVerbrauch = p_dGesamtStrecke / 100 * p_dVerbrauch;
	cout << setw(20) << dGesamtVerbrauch
		<< setw(25) << p_dTankinhalt;
}

void PKW::vAusgeben(ostream& o)
{
	o << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(15) << p_sName
		<< setiosflags(ios::fixed) << setprecision(2)
		<< setw(17) << dGeschwindigkeit()
		<< setw(18) << p_dGesamtStrecke
		<<setiosflags(ios::fixed) << setprecision(2)
		<< setw(20) << p_dGesamtStrecke / 100 * p_dVerbrauch
		<< setw(25) << p_dTankinhalt;
	return;
}
ostream& operator<<(ostream& o, PKW& f)
{
	f.vAusgeben(o);
	return o;
}
