#include "Streckenende.h"
#include<list>
#include<memory>
#include"Weg.h"
#include"Fahrzeug.h"
#include"Parken.h"
#include<iostream>
#include"Kreuzung.h"

using namespace std;
Streckenende::Streckenende(Fahrzeug& ppfahrzeug, Weg& ppweg)
	:Fahrausnahme(ppfahrzeug, ppweg)
{
}

void Streckenende::vBearbeiten()
{
	
	cout << p_pFahrzeug.p_sName << " am Streckenende" << endl;

	list<unique_ptr<Fahrzeug>>::iterator it;
	Kreuzung& zielKreuzung = p_pWeg.getZielKreuzung();
	Weg& nextWeg = zielKreuzung.pZufalligerWeg(p_pWeg);

	for (it = p_pWeg.p_pFahrzeuge.begin();it != p_pWeg.p_pFahrzeuge.end();it++)
	{
		if (*(*it) == p_pFahrzeug)
		{
		    //(*it)->p_pVerhalten = make_shared<Parken>();
			zielKreuzung.vTanken(p_pFahrzeug);
			nextWeg.vAnnahme(move(*it));
			p_pWeg.p_pFahrzeuge.erase(it);
			//p_pWeg.p_pFahrzeuge.vAktualisieren();
			break;
		}			
	}
	
	cout << "ZEIT      :" << dGlobaleZeit << endl;
	cout << "KREUZUNG  :" << zielKreuzung.getName() << zielKreuzung.getTankstelle() << endl;
	cout << "WECHSEL   :" << p_pWeg.getName() << "->" << nextWeg.getName() << endl;
	cout << "FAHRZEUG  :" << p_pFahrzeug.getName() << endl;

}
