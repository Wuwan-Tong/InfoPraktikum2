#pragma once
#include<iostream>

using namespace std;

class Simulation
{
private:

public:
	Simulation();
	~Simulation();
	istream& vEinlesen(istream&);
	void vSimulieren();
};

