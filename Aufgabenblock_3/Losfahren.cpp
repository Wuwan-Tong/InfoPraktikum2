#include "Losfahren.h"
#include"Weg.h"
#include"Fahrzeug.h"
#include"Fahren.h"
Losfahren::Losfahren(Fahrzeug& ppfahrzeug, Weg& ppweg)
	:Fahrausnahme(ppfahrzeug, ppweg)
{
}

void Losfahren::vBearbeiten()
{
	/*
	unique_ptr<Fahrzeug> fzg;
	fzg.reset(&p_pFahrzeug);	
	p_pWeg.vAnnahme(move(fzg));
	*/
	//p_pFahrzeug.vNeueStrecke(p_pWeg);
	unique_ptr<Fahrzeug> pfzg = p_pWeg.pAbgabe(p_pFahrzeug);
	p_pWeg.vAnnahme(move(pfzg));
}
