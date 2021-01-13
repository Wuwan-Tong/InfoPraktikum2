#include "Kreuzung.h"
#include"Fahrzeug.h"
#include"Weg.h"

Kreuzung::Kreuzung()
	:Simulationsobjekt(),p_dTankstelle(0.0)
{
}

Kreuzung::Kreuzung(string name, double dTankstelle)
	:Simulationsobjekt(name), p_dTankstelle(dTankstelle)
{
}

Kreuzung::~Kreuzung()
{
}

void Kreuzung::vVerbinde(string hinweg, string rueckweg, double weglaenge, weak_ptr<Kreuzung> startkreuzung, const weak_ptr<Kreuzung> zielkreuzung, Tempolimit tempolimit, bool uberholverbot)
{
	shared_ptr<Weg> hinWeg = make_shared<Weg>(hinweg, weglaenge, zielkreuzung, tempolimit, uberholverbot);
	shared_ptr<Weg> rueckWeg = make_shared<Weg>(rueckweg, weglaenge, startkreuzung, tempolimit, uberholverbot);
	hinWeg->setRueckWeg(rueckWeg);
	rueckWeg->setRueckWeg(hinWeg);
	zielkreuzung.lock()->p_pWege.push_back(rueckWeg);
	p_pWege.push_back(hinWeg);
	
}

void Kreuzung::vTanken(Fahrzeug& fzg)
{
	if (p_dTankstelle > 0)
	{
		p_dTankstelle -= fzg.dTanken(0);
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> fzg, double zeit)
{
	vTanken(*fzg);
	p_pWege.front()->vAnnahme(move(fzg), zeit);
}

void Kreuzung::vSimulieren()
{
	for (auto it = p_pWege.begin();it != p_pWege.end();it++)
	{
		(*it)->vSimulieren();
	}
}

Weg& Kreuzung::pZufalligerWeg(Weg& weg)
{
	
	Weg& rueckweg = weg.getRueckWeg();
	int r = rand() % p_pWege.size();
	if (p_pWege.size() == 1)
	{
		return rueckweg;
	}
	list<shared_ptr<Weg>>::iterator it=p_pWege.begin();
	for (int i = 0;i < r;i++)
	{
		it++;
	}
	if (*(*it) == rueckweg)
	{
		return pZufalligerWeg(weg);
	}
	else
		return *(*it);
}

double Kreuzung::getTankstelle()
{
	return p_dTankstelle;
}
