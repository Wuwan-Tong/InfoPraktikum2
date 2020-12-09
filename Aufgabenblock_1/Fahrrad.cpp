#include "Fahrrad.h"
#include<iomanip>
#include<iostream>

using namespace std;

/*
* Default-konstruktor
*/
Fahrrad::Fahrrad()
	:Fahrzeug()
{
}

/*
* konstruktor mit gegebenen Name
*/
Fahrrad::Fahrrad(string name)
	:Fahrzeug(name)
{
}
/*
* konstruktor mit gegebenen Name und maximaler Geschwindigkeit
*/
Fahrrad::Fahrrad(string name, const double maxgeschwindigkeit)
	:Fahrzeug(name, maxgeschwindigkeit)
{
}

/*
* Destruktor
*/
Fahrrad::~Fahrrad()
{
}
/*
* Die Funktion berechnet die aktuelle Geschwindigkeit von Fahrrad
*/
double Fahrrad::dGeschwindigkeit()
{
    double dAktuellGschwindigkeit = p_dMaxGeschwindigkeit;
    dAktuellGschwindigkeit = p_dMaxGeschwindigkeit * pow(0.9, floor(p_dGesamtStrecke / 20));
    if (dAktuellGschwindigkeit < 12)
        dAktuellGschwindigkeit = 12;
    return dAktuellGschwindigkeit;
}



