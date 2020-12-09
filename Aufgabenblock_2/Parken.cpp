#include "Parken.h"
#include"Weg.h"
#include<iostream>
#include"Fahrzeug.h"
#include"Losfahren.h"

using namespace std;
Parken::Parken()
	:Verhalten(), p_dStart(0)
{
}
Parken::Parken(Weg& weg, double p_dStart)
	:Verhalten(weg), p_dStart(p_dStart)
{
}

Parken::~Parken()
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double pdstart)
{
	if (dGlobaleZeit <= p_dStart)
		return 0.0;
	else
	{
		cout << "Startzeit erreicht" << endl;
		aFzg.p_dZeit = pdstart;
		throw new Losfahren(aFzg, *p_pWeg);
	}
		
}

