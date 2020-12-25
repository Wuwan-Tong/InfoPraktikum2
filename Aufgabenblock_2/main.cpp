#include "Fahrzeug.h"
#include"Fahrrad.h"
#include"PKW.h"
#include"Weg.h"
#include"Tempolimit.h"
#include"SimuClient.h"
#include"vertagt_liste - Vorlage.h"
#include<iostream>
#include<memory>
#include<vector>
#include<limits>
#include<random>

using namespace std;
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();

extern double dGlobaleZeit = 0.0;
int main()
{
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();
	//vAufgabe_3();

	//vAufgabe_4();
	//vAufgabe_5();
	vAufgabe_6();
	//vAufgabe_6a();









	return 0;


}

void vAufgabe_1()
{
	string name = "n2";
	//new and delete
	Fahrzeug* fahrzeug1 = new Fahrzeug();
	Fahrzeug* fahrzeug2 = new Fahrzeug(name);
	delete fahrzeug1;
	delete fahrzeug2;

	//unique pointer
	unique_ptr<Fahrzeug> fahrzeug_unique_ptr[2];
	fahrzeug_unique_ptr[0] = make_unique<Fahrzeug>();
	fahrzeug_unique_ptr[1] = make_unique<Fahrzeug>(name);

	//shared pointer
	shared_ptr<Fahrzeug> fahrzeug_shared_ptr[2];
	fahrzeug_shared_ptr[0] = make_shared<Fahrzeug>();
	fahrzeug_shared_ptr[1] = make_shared<Fahrzeug>(name);

	//fahrzeug_shared_ptr[0] in fahrzeug_shared_ptr2 Speichern
	shared_ptr<Fahrzeug> fahrzeug_shared_ptr2 = fahrzeug_shared_ptr[0];

	//test fahrzeug2_ptr
	cout << (*fahrzeug_shared_ptr2) << endl;

	//reference Anzahl
	cout << fahrzeug_shared_ptr[0].use_count() << endl;
	cout << fahrzeug_shared_ptr[1].use_count() << endl;
	cout << fahrzeug_shared_ptr2.use_count() << endl;

	//vektor
	vector<unique_ptr<Fahrzeug>> v_fahrzeug_ptr;
	//direkt Speicherung in vector wird nicht erlaubt, aber nur mit move
	v_fahrzeug_ptr.push_back(move(fahrzeug_unique_ptr[0]));//after move,fahrzeug_unique_ptr[0] is empty
	v_fahrzeug_ptr.push_back(move(fahrzeug_unique_ptr[1]));
	v_fahrzeug_ptr.clear();

	vector<shared_ptr<Fahrzeug>> s_fahrzeug_ptr;
	s_fahrzeug_ptr.push_back(fahrzeug_shared_ptr[0]);
	s_fahrzeug_ptr.push_back(move(fahrzeug_shared_ptr[1]));

	//reference Anzahl
	cout << fahrzeug_shared_ptr[0].use_count() << endl;//0utput:3,
	cout << fahrzeug_shared_ptr[1].use_count() << endl;//output:0,after move,fahrzeug_shared_ptr[1] is empty
	cout << fahrzeug_shared_ptr2.use_count() << endl;
}

void vAufgabe_1a()
{
	string name[3];
	double maxgeschwindigkeit[3];
	vector<unique_ptr<Fahrzeug>> fahrzeug_ptr;
	for (int i = 1;i < 4;i++)
	{
		cout << "Geben der Name von " << i << ". Fahrzeug ein:" << endl;
		cin >> name[i - 1];
		cout << "Geben die Maximalgeschwindigkeit von 1. Fahrzeug ein:" << endl;
		cin >> maxgeschwindigkeit[i - 1];
		fahrzeug_ptr.push_back(make_unique<Fahrzeug>(name[i - 1], maxgeschwindigkeit[i - 1]));
	}
	for (int i = 0;i < 5;i++)
	{
		dGlobaleZeit = 1.0 * i;
		for (auto it = fahrzeug_ptr.begin();it != fahrzeug_ptr.end();it++)
		{
			(*it)->vSimulieren();
			cout << *(*it) << endl;
			cout << endl;
		}
	}
}

void vAufgabe_2()
{
	int iAnzahlPKW, iAnzahlFahrrad;
	vector<unique_ptr<Fahrzeug>> fahrzeuge_unique_ptr;
	cout << "geben die Anzahl der zu erzeugten PKWs:\n";
	cin >> iAnzahlPKW;//die Anzahl der zu erzeugten PKWs eingeben
	cout << "geben die Anzahl der zu erzeugten fahrraeder:\n";
	cin >> iAnzahlFahrrad;//die Anzahl der zu erzeugten FAhrraeder eingeben
	//in einem vector speichern
	for (int i = 0;i < iAnzahlPKW;i++)
	{
		string name = "pkw" + to_string(i + 1);
		double geschwindigkeit = 80;
		double verbrauch = 280;
		fahrzeuge_unique_ptr.push_back(make_unique<PKW>(name, geschwindigkeit, verbrauch));
	}
	for (int i = 0;i < iAnzahlFahrrad;i++)
	{
		string name = "fahrrad" + to_string(i + 1);
		double geschwindigkeit = 20;
		fahrzeuge_unique_ptr.push_back(make_unique<Fahrrad>(name, geschwindigkeit));
	}
	//test
	(*fahrzeuge_unique_ptr.begin())->vKopf();
	for (int i = 0;i < 15;i++)
	{
		dGlobaleZeit += 0.5;
		for (auto it = fahrzeuge_unique_ptr.begin(); it != fahrzeuge_unique_ptr.end();it++)
		{
			if (i % 6 == 0)//3 stunden
			{
				(*it)->dTanken(551);
			}
			(*it)->vSimulieren();
			(*it)->vAusgeben();//Ausgabe mit funktion			
			cout << endl;
			//cout << *(*it) << endl;//Ausgabe mit operator ueberladung
		}
	}
}
void vAufgabe_3()
{
	vector<shared_ptr<Fahrzeug>> fahrzeug_vec;
	fahrzeug_vec.push_back(make_shared<PKW>("pkw1", 70, 200));
	fahrzeug_vec.push_back(make_shared<PKW>("pkw2", 80, 200));
	fahrzeug_vec.push_back(make_shared<Fahrrad>("fahrrad1", 20));
	fahrzeug_vec.push_back(make_shared<Fahrrad>("fahrrad2", 21));
	fahrzeug_vec[1]->vKopf();
	for (auto it = fahrzeug_vec.begin(); it != fahrzeug_vec.end();it++)
		cout << *(*it) << endl;
	//test operator <
	bool b = (fahrzeug_vec[1] < fahrzeug_vec[2]);
	if (b == 0)
		cout << "GesamtStrecke von fahrzeug_vec[1] kleiner gleich GesamtStrecke von fahrzeug_vec[2]" << endl;
	else
		cout << "GesamtStrecke von fahrzeug_vec[1] groesser als GesamtStrecke von fahrzeug_vec[2]" << endl;

	//smartpointer
	shared_ptr<Fahrrad> fahrrad2_new = make_shared<Fahrrad>("fahrrad2_new", 2);
	cout << *fahrrad2_new << endl;
	//test Zuweisungsoperator
	Fahrrad* fahrrad3 = new Fahrrad("fahrrad3", 22);
	Fahrrad fahrrad3_new;
	cout << *fahrrad3 << endl << fahrrad3_new << endl;
	fahrrad3_new = *fahrrad3;
	cout << *fahrrad3 << endl << fahrrad3_new << endl;
	delete fahrrad3;
}
void vAufgabe_4()
{
	Weg* w1_ptr = new Weg("w1", 20,Tempolimit::Innerorts);
	cout << (*w1_ptr) << endl;
	w1_ptr->vAusgeben();
}

void vAufgabe_5()
{
	Weg* weg = new Weg("weg", 100);
	unique_ptr<Fahrzeug> fahrzeug_ptr[3];
	fahrzeug_ptr[0] = make_unique<Fahrzeug>("BMW");
	fahrzeug_ptr[1] = make_unique<Fahrzeug>("Audi");
	fahrzeug_ptr[2] = make_unique<Fahrzeug>("BMX");
	for (int i = 0;i < 3;i++)
	{
		weg->vAnnahme(move(fahrzeug_ptr[i]));
	}
	weg->vKopf();
	weg->vAusgeben();
	cout << endl;
	cout << (*weg) << endl;
	delete weg;
}

void vAufgabe_6()
{
	unique_ptr<Weg> weg1 = make_unique<Weg>("Weg1", 500, Tempolimit::Innerorts);
	unique_ptr<Weg> weg2 = make_unique<Weg>("Weg2", 500, Tempolimit::Autobahn);
	
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("F1", 50, 1, 200);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("F2", 200, 1, 200);
	unique_ptr<Fahrzeug> f3 = make_unique<PKW>("F3", 200, 1, 200);
	unique_ptr<Fahrzeug> f4 = make_unique<Fahrrad>("Fahrrad1", 30);
	unique_ptr<Fahrzeug> f5 = make_unique<Fahrrad>("Fahrrad2", 20);

	weg1->vAnnahme(move(f1), 0.5);
	weg1->vAnnahme(move(f2), 3.0);
	weg1->vAnnahme(move(f3));
	weg1->vAnnahme(move(f4));
	weg1->vAnnahme(move(f5), 2);

	unique_ptr<Fahrzeug> b1 = make_unique<PKW>("BMW1", 50, 1, 200);
	unique_ptr<Fahrzeug> b2 = make_unique<PKW>("BMW2", 200, 1, 200);
	unique_ptr<Fahrzeug> b3 = make_unique<Fahrrad>("Fahrrad3", 20);

	weg2->vAnnahme(move(b1));
	weg2->vAnnahme(move(b2), 0.7);
	weg2->vAnnahme(move(b3));

	weg1->vKopf();
	cout << *weg1 << endl << *weg2 << endl;

	bInitialisiereGrafik(800, 500);
	vSetzeZeit(dGlobaleZeit);
	int feld[] = { 700 ,250 ,100 ,250 };
	bZeichneStrasse("Weg1", "Weg2", 500, 2, feld);
	//bZeichnePKW("F1", "Weg1", 0.1, 50, 100);
	//bZeichneFahrrad("Fahrrad1", "Weg1", 0.2, 30);
	//bZeichnePKW("BMW1", "Weg2", 0.3, 50, 100);
	//bZeichneFahrrad("Fahrrad3", "Weg2", 0.4, 30);

	for (dGlobaleZeit = 0; dGlobaleZeit < 15; dGlobaleZeit += 0.5) 
	{
		cout << "GlobaleZeit:" << dGlobaleZeit << endl;
		weg1->vSimulieren();
		weg1->vAusgeben();
		cout << endl;
		weg2->vSimulieren();
		weg2->vAusgeben();
		cout << endl;
		vSleep(100);
	}

}

void vAufgabe_6a()
{
	using namespace vertagt;
	VListe<int> vliste;
	typedef VListe<int>::iterator vlistit;
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);
	for (int i = 0;i < 10;i++)
	{
		vliste.push_back(dist(device));
	}
	vliste.vAktualisieren();
    //ausgeben
	for (vlistit it = vliste.begin();it != vliste.end();it++)
	{
		cout << (*it) << '\t';
	}
	cout << endl;

	//delete enelemt>5
	for (vlistit it = vliste.begin();it != vliste.end();it++)
	{
		if (*it > 5)
			vliste.erase(it);
	}
	//wieder ausgeben
	for (vlistit it = vliste.begin();it != vliste.end();it++)
	{
		cout << (*it) << '\t';
	}
	cout << endl;
	vliste.vAktualisieren();
	//wieder*2 ausgeben...@_@
	for (vlistit it = vliste.begin();it != vliste.end();it++)
	{
		cout << (*it) << '\t';
	}
	cout << endl;
	vliste.push_front(dist(device));
	vliste.push_back(dist(device));
	vliste.vAktualisieren();
	for (vlistit it = vliste.begin();it != vliste.end();it++)
	{
		cout << (*it) << '\t';
	}
}


