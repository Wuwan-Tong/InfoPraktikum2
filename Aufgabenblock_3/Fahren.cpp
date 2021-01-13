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
	else
	{
		double temp;
		if (abs(dRestVirtuelleSchranke) < 0.01)
		{
			temp = min(dTempStrecke, dRestWeg);
		}
		else
		{
			temp = min(min(dTempStrecke, dRestWeg), dRestVirtuelleSchranke);
		}
		
		p_pWeg->setVirtuelleSchranke(temp+ aFzg.dGetAbschnittStrecke());
		return temp;
	}
	/*else if (dTempStrecke > min(dRestWeg, dRestVirtuelleSchranke))
	{
		p_pWeg->setVirtuelleSchranke(min(dRestWeg, dRestVirtuelleSchranke)*2 + aFzg.dGetAbschnittStrecke());
		return min(dRestWeg, dRestVirtuelleSchranke);
	}
	else
	{
		p_pWeg->setVirtuelleSchranke(dTempStrecke*2 + aFzg.dGetAbschnittStrecke());
		return dTempStrecke;
	}*/
		
}
