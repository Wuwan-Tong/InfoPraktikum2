#include "Streckenende.h"
#include<list>
#include<memory>
#include"Weg.h"
#include"Fahrzeug.h"
#include"Parken.h"
#include<iostream>

using namespace std;
Streckenende::Streckenende(Fahrzeug& ppfahrzeug, Weg& ppweg)
	:Fahrausnahme(ppfahrzeug, ppweg)
{
}

void Streckenende::vBearbeiten()
{
	cout << p_pFahrzeug.p_sName << " am Streckenende" << endl;
	list<unique_ptr<Fahrzeug>>::iterator it;
	for (it = p_pWeg.p_pFahrzeuge.begin();it != p_pWeg.p_pFahrzeuge.end();it++)
	{
		if (*(*it) == p_pFahrzeug)
		{
		    (*it)->p_pVerhalten = make_shared<Parken>();
			p_pWeg.p_pFahrzeuge.erase(it);
			//p_pWeg.p_pFahrzeuge.vAktualisieren();
			break;
		}			
	}

}
