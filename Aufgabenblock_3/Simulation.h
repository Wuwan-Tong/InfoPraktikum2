#pragma once
#include<iostream>
#include<map>

using namespace std;

class Kreuzung;
class Simulation
{
private:
	map<string, shared_ptr<Kreuzung>> mMapKreuzung;
public:
	Simulation();
	~Simulation();
	istream& vEinlesen(istream&, bool bMitGrfik=false);
	void vSimulieren();
	void vSimulieren(double dDauer, double dZeitschritt);
};

