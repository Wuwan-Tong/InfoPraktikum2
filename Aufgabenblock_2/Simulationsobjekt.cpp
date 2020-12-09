#include "Simulationsobjekt.h"
#include<iomanip>
#include<iostream>

using namespace std;
int Simulationsobjekt::p_iMaxID = 0;
extern double dGlobaleZeit;
Simulationsobjekt::Simulationsobjekt()
	: p_sName(""), p_iID(++p_iMaxID)
{
}

Simulationsobjekt::Simulationsobjekt(const string pname)
	: p_sName(pname), p_iID(++p_iMaxID)
{
}

Simulationsobjekt::~Simulationsobjekt()
{
	p_iMaxID -= 1;
	cout << "\nSimulationsobjekt geloescht: \n" << "Name: " << p_sName << "\nID: " << p_iID << endl;
}


void Simulationsobjekt::vAusgeben()
{
	cout << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(23) << p_sName;
}

void Simulationsobjekt::vAusgeben(ostream& o)
{
	o << setiosflags(ios::left) << setw(6) << p_iID
		<< setw(23) << p_sName;
}
ostream& operator<<(ostream& o,  Simulationsobjekt& f)
{
	f.vAusgeben(o);
	return o;
}

bool Simulationsobjekt::operator==(Simulationsobjekt& s)
{
	if (this->p_iID == s.p_iID)
		return true;
	else
		return false;
}