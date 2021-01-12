#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include<memory>
#include"Tempolimit.h"
class Weg;
class Fahrzeug;
class Kreuzung :
    public Simulationsobjekt
{
private:
    double p_dTankstelle;
    list<shared_ptr<Weg>> p_pWege;

public:
    Kreuzung();
    Kreuzung(string name, double dTankstelle=0);
    ~Kreuzung();
    void vVerbinde(string hinweg, string rueckweg, double weglaenge,
        weak_ptr<Kreuzung> startkreuzung, const weak_ptr<Kreuzung> zielkreuzung,
        Tempolimit tempolimit, bool uberholverbot);
    void vTanken(Fahrzeug&);
    void vAnnahme(unique_ptr<Fahrzeug> fzg, double zeit);
    void vSimulieren();
    Weg& pZufalligerWeg(Weg&);
    double getTankstelle();
};

