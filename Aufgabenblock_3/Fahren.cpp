#include "Fahren.h"
#include"Fahrzeug.h"
#include "Weg.h"
#include"Streckenende.h"
#include<iostream>

using namespace std;

Fahren::Fahren()
	:Verhalten()
{
}

Fahren::Fahren(Weg& weg)
	:Verhalten(weg)
{
}

Fahren::~Fahren()
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dTempStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
	double dRestWeg = p_pWeg->getLaenge() - aFzg.dGetAbschnittStrecke();

	double dVirtuelleSchranke = p_pWeg->dGetVirtuelleSchranke();
	double dRestVirtuelleSchranke = dVirtuelleSchranke - aFzg.dGetAbschnittStrecke();

	if (dRestWeg <0.1)//am wegende(double-double kann nicht genau = 0)
	{
		throw new Streckenende(aFzg, *p_pWeg);
		return 0;
	}
	else if (dTempStrecke > min(dRestWeg, dRestVirtuelleSchranke))
	{
		return min(dRestWeg, dRestVirtuelleSchranke);
	}
	else
		return dTempStrecke;
}
