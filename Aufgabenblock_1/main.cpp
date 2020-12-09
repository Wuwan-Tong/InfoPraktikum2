#include "Fahrzeug.h"
#include"Fahrrad.h"
#include"PKW.h"
#include<iostream>
#include<memory>
#include<vector>
#include<limits>

using namespace std;
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
//void vAufgabeProbe();
double dEpsilon = 0.001;
void vAufgabe_AB1();
extern double dGlobaleZeit=0.0;
int main()
{
	vAufgabe_AB1();
	/*
	vector<int> vecT(3, 2);
	
	for (int i = 0;i < 3;i++)
	{
		vecT.push_back(i);
	}
	for (int i = 0;i < 3;i++)
	{
		cout << vecT[i] << endl;
	}
	vecT.pop_back();
	vecT[1] = 3;
	for (int i = 0;i < 3;i++)
	{
		cout << vecT[i] << endl;
	}*/
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();
	//vAufgabe_3();


	//probe testat:
	//vAufgabeProbe();
	
	/*
	PKW* aPKW=new PKW("n1", 11.1, 1.0, 200);
	Fahrrad* aFahrrad=new Fahrrad("n2", 22.2);
	cout << *aPKW << endl << *aFahrrad << endl;
	*/
	return 0;
	
	
}


void vAufgabe_AB1() {

	int l = 0; // Laufindex f¨¹r gezielte Ausgabe
	vector<int> ausgabe{ 0,1,4,5,6,7,10,11,12,16 };

	std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	vecFahrzeuge.push_back(make_unique <PKW>("Auto", 200, 10));
	vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 20));
	for (dGlobaleZeit = 0; dGlobaleZeit < 5; dGlobaleZeit += 0.3)
	{
		auto itL = find(ausgabe.begin(), ausgabe.end(), l);
		if (itL != ausgabe.end()) {
			std::cout << std::endl << l << " Globalezeit = " << dGlobaleZeit << std::endl;
			vecFahrzeuge[1]->vKopf();
			//vKopf();
		}

		for (int i = 0; i < vecFahrzeuge.size(); i++)
		{
			vecFahrzeuge[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dEpsilon)
			{
				vecFahrzeuge[i]->dTanken(0.0);
			}
			if (itL != ausgabe.end()) {
				std::cout << *vecFahrzeuge[i] << endl;
			}
		}
		l++;
	}
}

//Probe testat
/*
void vAufgabeProbe() {

	Fahrzeug* pF1 = new Fahrzeug("Audi", 150);
	Fahrzeug* pF2 = new Fahrzeug("BMW", 200);
	dGlobaleZeit = 0.0;
	pF2->vKopf();
	cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
	cout << *pF1 << endl << *pF2 << endl;
	dGlobaleZeit = 5.0;
	cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
	pF1->vSimulieren();
	pF2->vSimulieren();
	cout << *pF1 << endl << *pF2 << endl;
	cout << endl;
	if (*pF1 < *pF2)
		cout << "Vergleich o.k." << endl;
	if (!(*pF2 < *pF1))
		cout << "Vergleich o.k." << endl;

	delete pF1;
	delete pF2;
}
*/
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
		cout << "Geben der Name von " <<i<< ". Fahrzeug ein:" << endl;
		cin >> name[i-1];
		cout << "Geben die Maximalgeschwindigkeit von " << i << ". Fahrzeug ein:" << endl;
		cin >> maxgeschwindigkeit[i-1];
		fahrzeug_ptr.push_back(make_unique<Fahrzeug>(name[i - 1], maxgeschwindigkeit[i - 1]));
	}
	(*fahrzeug_ptr.begin())->vKopf();
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
		string name = "pkw" + to_string(i+1);
		double geschwindigkeit = 80;
		double verbrauch = 280;
		fahrzeuge_unique_ptr.push_back(make_unique<PKW>(name, geschwindigkeit,verbrauch));
	}
	for (int i = 0;i < iAnzahlFahrrad;i++)
	{
		string name = "fahrrad" + to_string(i+1);
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
	if(b==0)
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


