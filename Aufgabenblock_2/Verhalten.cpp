#include "Verhalten.h"
#include"Weg.h"
#include"Fahrzeug.h"

Verhalten::Verhalten()
{
}

Verhalten::Verhalten(Weg& weg)
    :p_pWeg(&weg)
{
}
/*
double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
    double dStreckeSchnitt= aFzg.dGeschwindigkeit() * dZeitIntervall;
    if (dStreckeSchnitt > p_pWeg->getLaenge() - aFzg.dGetAbschnittStrecke())
        dStreckeSchnitt = p_pWeg->getLaenge() - aFzg.dGetAbschnittStrecke();
    return dStreckeSchnitt;

    
}
*/
Weg* Verhalten::get_weg()
{
    return p_pWeg;
}
