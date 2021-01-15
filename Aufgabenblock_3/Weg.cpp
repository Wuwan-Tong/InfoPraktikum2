#include "Weg.h"
#include"Fahrzeug.h"
#include"vertagt_aktion - Vorlage.h"
#include<list>
#include<iomanip>
#include <iostream>
#include"Fahrausnahme.h"
#include"Kreuzung.h"
using namespace std;
Weg::Weg()
	:Simulationsobjekt(), p_dLeange(0), p_eTempolimit(Tempolimit::Autobahn)
{
	cout << "Weg erzeugt:" <<p_sName<< endl;
}


Weg::Weg(const string pname, double pdleange, Tempolimit ptempolimit, bool pUeberholverbot)
	: Simulationsobjekt(pname), p_dLeange(pdleange), p_eTempolimit(ptempolimit), p_bUeberholverbot(pUeberholverbot)
{
	cout << "Weg erzeugt:" << p_sName << endl;
}

Weg::Weg(const string pname, double pdleange, weak_ptr<Kreuzung> pKreuzung, Tempolimit ptempolimit, bool pUeberholverbot)
	: Simulationsobjekt(pname), p_dLeange(pdleange),
	p_pZielKreuzung(pKreuzung), p_eTempolimit(ptempolimit), p_bUeberholverbot(pUeberholverbot)
{
	cout << "Weg erzeugt:" << p_sName << endl;
}

Weg::~Weg()
{
}


void Weg::vAusgeben(ostream& o)
{
	//Simulationsobjekt::vAusgeben(o);
	cout<< setiosflags(ios::left) << setw(6) << p_iID
		<< setw(23) << p_sName;
	o << setiosflags(ios::fixed) << setprecision(2)
		<< ":" << setw(20) << p_dLeange<<"(";
	//list<unique_ptr<Fahrzeug>>::iterator i;
	for (auto i= p_pFahrzeuge.begin(); i != p_pFahrzeuge.end(); i++)
	{
		o << (*i)->p_sName << "\t";
	}
	o << ")";

}

void Weg::vKopf()
{
	cout << setiosflags(ios::left);
	cout << setw(6) << "ID" << "|" << setw(20) << "Name" << "|" << setw(20) << "GLaenge"
		<< "|" << setw(16) << "Fahrzeuge" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
}

void Weg::vSimulieren()
{
	list<unique_ptr<Fahrzeug>>::iterator i;
	for (i = p_pFahrzeuge.begin(); i != p_pFahrzeuge.end(); )
	{
		try
		{
			(*i)->vSimulieren();
			i++;
		}
		catch (Fahrausnahme* pfahrausnahme)
		{
			i++;
			pfahrausnahme->vBearbeiten();
		}
		
	}
}

void Weg::vAusgeben()
{
	Simulationsobjekt::vAusgeben();
	cout << setiosflags(ios::fixed) << setprecision(2)
		<< ":" << setw(20) << p_dLeange << "(";
	list<unique_ptr<Fahrzeug>>::iterator i;
	for (i = p_pFahrzeuge.begin(); i != p_pFahrzeuge.end(); i++)
	{
	    cout <<(*i)->p_sName<<"\t";
	}
	cout<< ")";
}

double Weg::getTempolimit()
{
	if (p_eTempolimit == Tempolimit::Innerorts)
		return 50;
	else if (p_eTempolimit == Tempolimit::Landstrasse)
		return 100;
	else if (p_eTempolimit == Tempolimit::Autobahn)
		return numeric_limits<int>::max();
}

double Weg::getLaenge()
{
	return p_dLeange;
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug_ptr)//fahrende fahrzeug
{
	fahrzeug_ptr->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(fahrzeug_ptr));	
	//p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug_ptr, double pdstart)//parkende fahrzeug
{
	fahrzeug_ptr->vNeueStrecke(*this, pdstart);
	p_pFahrzeuge.push_front(move(fahrzeug_ptr));
	//p_pFahrzeuge.vAktualisieren();
}

string Weg::sGetName() const
{
	return p_sName;
}

double Weg::dGetLeange() const
{
	return p_dLeange;
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg)
{
	//p_pFahrzeuge
	
	for (auto it = p_pFahrzeuge.begin();it != p_pFahrzeuge.end();it++)
	{
		if (&fzg == (*it).get())
		{		
			unique_ptr<Fahrzeug> abgabe = move(*it);
			p_pFahrzeuge.erase(it);
			//p_pFahrzeuge.vAktualisieren();
			return abgabe;
		}
	}
}

double Weg::dGetVirtuelleSchranke()
{
	if (p_bUeberholverbot)
	{
		return p_dVirtuelleSchranke;
	}
	else
		return numeric_limits<double>::max();
	
}

Weg& Weg::getRueckWeg()
{
	auto temp=p_pRueckWeg.lock();
	return *temp;
	
	//lock::creates a shared_ptr that manages the referenced object
}

Kreuzung& Weg::getZielKreuzung()
{
	auto temp=p_pZielKreuzung.lock();
	return *temp;
	
}

void Weg::setRueckWeg(weak_ptr<Weg> weg)
{
	p_pRueckWeg = weg;
}

void Weg::setVirtuelleSchranke(double vs)
{
	p_dVirtuelleSchranke = vs;
}
