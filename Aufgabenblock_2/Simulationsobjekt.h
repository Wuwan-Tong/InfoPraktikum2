#pragma once
#include<string>
using namespace std;
extern double dGlobaleZeit;
class Simulationsobjekt
{
protected:
	string p_sName;
	const int p_iID;
	static int p_iMaxID;
	double p_dZeit = 0;
public:
	Simulationsobjekt();
	Simulationsobjekt(const string pname);
	virtual ~Simulationsobjekt();
	virtual void vSimulieren()=0;
	virtual void vAusgeben();
	virtual void vAusgeben(ostream&);
	virtual bool operator==(Simulationsobjekt&);
};
ostream& operator<<(ostream&, Simulationsobjekt&);//operand kein element der klasse
