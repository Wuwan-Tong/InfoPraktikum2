#include "Simulation.h"
#include<string>
#include"Kreuzung.h"
#include"PKW.h"
#include"Fahrrad.h"
#include"Tempolimit.h"
#include<string>
#include"SimuClient.h"

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

istream& Simulation::vEinlesen(istream& i, bool bMitGrfik)
{
    bInitialisiereGrafik(1300, 1000);
    if (bMitGrfik == false)
    {
        int zeile = 1;
        while (!i.eof())
        {

            string schluesselwort;
            i >> schluesselwort;
            try
            {
                if (schluesselwort == "KREUZUNG")
                {
                    shared_ptr<Kreuzung> k1 = make_shared<Kreuzung>();
                    i >> *k1;

                    //kreuzung not already in the map
                    try {
                        if (mMapKreuzung.find(k1->getName()) == mMapKreuzung.end())//if not find, return end()
                        {
                            mMapKreuzung[k1->getName()] = k1;
                        }
                        else {
                            throw runtime_error("Kreuzung is already in the MapKreuzung!!   Line: " + to_string(zeile));
                        }
                    }
                    catch (runtime_error& error)
                    {
                        cout << error.what() << endl;
                    }

                }
                else if (schluesselwort == "PKW")
                {
                    unique_ptr<PKW> p1 = make_unique<PKW>();
                    string sStartKreuzung;
                    double dStartZeit;
                    i >> *p1 >> sStartKreuzung >> dStartZeit;
                }
                else if (schluesselwort == "FAHRRAD")
                {
                    unique_ptr<Fahrrad> f1 = make_unique<Fahrrad>();
                    string sStartKreuzung;
                    double dStartZeit;
                    i >> *f1 >> sStartKreuzung >> dStartZeit;
                }
                else if (schluesselwort == "STRASSE")
                {
                    string sQuellkreuzung;
                    string sZielkreuzung;
                    string sWegQuell2Ziel;
                    string sWegZiel2Quell;
                    double dLaenge;
                    int iTempolimit;
                    int ueberholverbot;
                    Tempolimit pTempolimit;
                    i >> sQuellkreuzung >> sZielkreuzung >> sWegQuell2Ziel >> sWegZiel2Quell >> dLaenge >> iTempolimit >> ueberholverbot;
                    try
                    {
                        switch (iTempolimit)
                        {
                        case 1:
                            pTempolimit = Tempolimit::Innerorts;
                            break;
                        case 2:
                            pTempolimit = Tempolimit::Landstrasse;
                            break;
                        case 3:
                            pTempolimit = Tempolimit::Autobahn;
                            break;
                        default:
                            pTempolimit = Tempolimit::Autobahn;
                            throw runtime_error("iTempolimit should be 1,2 or 3!!  Line: " + to_string(zeile));
                        }
                    }
                    catch (runtime_error& error)
                    {
                        cout << error.what() << endl;
                    }
                    try
                    {
                        switch (ueberholverbot)
                        {
                        case 0:
                            ueberholverbot = false;
                            break;
                        case 1:
                            ueberholverbot = true;
                            break;
                        default:
                            ueberholverbot = true;
                            throw runtime_error("iTempolimit should be 1,2 or 3!! line: " + to_string(zeile));
                        }
                    }
                    catch (runtime_error& error)
                    {
                        cout << error.what() << endl;
                    }
                }
                else
                {
                    throw runtime_error("schluesselwort shoule be one of (KREUZUNG, PKW, FAHRRAD, STRASSE)!!  Line: " + to_string(zeile));
                }
            }
            catch (runtime_error& error)
            {
                cout << error.what() << endl;
            }
            zeile++;
        }       
    }
    else
    {
    int zeile = 1;
    while (!i.eof())
    {

        string schluesselwort;
        i >> schluesselwort;
        try
        {
            if (schluesselwort == "KREUZUNG")
            {
                shared_ptr<Kreuzung> k1 = make_shared<Kreuzung>();
                int X;
                int Y;
                i >> *k1 >> X >> Y;

                //kreuzung not already in the map
                try {
                    if (mMapKreuzung.find(k1->getName()) == mMapKreuzung.end())//if not find, return end()
                    {
                        mMapKreuzung[k1->getName()] = k1;
                        bZeichneKreuzung(X, Y);
                    }
                    else {
                        throw runtime_error("Kreuzung is already in the MapKreuzung!!   Line: " + to_string(zeile));
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }

            }
            else if (schluesselwort == "PKW")
            {
                unique_ptr<PKW> p1 = make_unique<PKW>();
                string sStartKreuzung;
                double dStartZeit;
                i >> *p1 >> sStartKreuzung >> dStartZeit;
                try {
                    if (mMapKreuzung.find(sStartKreuzung) == mMapKreuzung.end())//not find
                    {
                        throw runtime_error("StartKreuzung cannot find!!   Line: " + to_string(zeile));
                    }
                    else {
                        //void vAnnahme(unique_ptr<Fahrzeug> fzg, double zeit);
                        mMapKreuzung.find(sStartKreuzung)->second->vAnnahme(move(p1), dStartZeit);
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }
                
            }
            else if (schluesselwort == "FAHRRAD")
            {
                unique_ptr<Fahrrad> f1 = make_unique<Fahrrad>();
                string sStartKreuzung;
                double dStartZeit;
                i >> *f1 >> sStartKreuzung >> dStartZeit;
                try {
                    if (mMapKreuzung.find(sStartKreuzung) == mMapKreuzung.end())//not find
                    {
                        throw runtime_error("StartKreuzung cannot find!!   Line: " + to_string(zeile));
                    }
                    else {
                        //void vAnnahme(unique_ptr<Fahrzeug> fzg, double zeit);
                        mMapKreuzung.find(sStartKreuzung)->second->vAnnahme(move(f1), dStartZeit);
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }
            }
            else if (schluesselwort == "STRASSE")
            {
                string sQuellkreuzung;
                string sZielkreuzung;
                string sWegQuell2Ziel;
                string sWegZiel2Quell;
                double dLaenge;
                int iTempolimit;
                int iUeberholverbot;
                bool ueberholverbot;
                Tempolimit pTempolimit;
                int iKoordinatenPaareAnzahl;

                i >> sQuellkreuzung >> sZielkreuzung >> sWegQuell2Ziel >> sWegZiel2Quell
                    >> dLaenge >> iTempolimit >> iUeberholverbot >> iKoordinatenPaareAnzahl;
                int temp = iKoordinatenPaareAnzahl * 2;
                int* Koordinaten = new int[temp];
                for (int ii = 0;ii < iKoordinatenPaareAnzahl * 2;ii++)
                {
                    i >> Koordinaten[ii];
                }
                bZeichneStrasse(sWegQuell2Ziel, sWegZiel2Quell, dLaenge, iKoordinatenPaareAnzahl, Koordinaten);               
                delete[] Koordinaten;
                try
                {
                    switch (iTempolimit)
                    {
                    case 1:
                        pTempolimit = Tempolimit::Innerorts;
                        break;
                    case 2:
                        pTempolimit = Tempolimit::Landstrasse;
                        break;
                    case 3:
                        pTempolimit = Tempolimit::Autobahn;
                        break;
                    default:
                        pTempolimit = Tempolimit::Autobahn;
                        throw runtime_error("iTempolimit should be 1,2 or 3!!  Line: " + to_string(zeile));
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }
                try
                {
                    switch (iUeberholverbot)
                    {
                    case 0:
                        ueberholverbot = false;
                        break;
                    case 1:
                        ueberholverbot = true;
                        break;
                    default:
                        ueberholverbot = true;
                        throw runtime_error("iTempolimit should be 1,2 or 3!! line: " + to_string(zeile));
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }
                /*void vVerbinde(string hinweg, string rueckweg, double weglaenge,
        weak_ptr<Kreuzung> startkreuzung, const weak_ptr<Kreuzung> zielkreuzung,
        Tempolimit tempolimit, bool uberholverbot);*/
                try {
                    if (mMapKreuzung.find(sQuellkreuzung) == mMapKreuzung.end())//not find
                    {
                        throw runtime_error("sQuellkreuzung cannot find!!   Line: " + to_string(zeile));
                    }
                    else {
                        //void vAnnahme(unique_ptr<Fahrzeug> fzg, double zeit);
                        mMapKreuzung.find(sQuellkreuzung)->second->vVerbinde(sWegQuell2Ziel, sWegZiel2Quell,
                            dLaenge, mMapKreuzung.find(sQuellkreuzung)->second,
                            mMapKreuzung.find(sZielkreuzung)->second, pTempolimit, ueberholverbot);
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }
            }
            else
            {
                throw runtime_error("schluesselwort shoule be one of (KREUZUNG, PKW, FAHRRAD, STRASSE)!!  Line: " + to_string(zeile));
            }
        }
        catch (runtime_error& error)
        {
            cout << error.what() << endl;
        }
        zeile++;
    }
 }
    
}

void Simulation::vSimulieren()
{
    for (auto& it :mMapKreuzung)
    {
        it.second->vSimulieren();
    }
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
    for (dGlobaleZeit = 0;dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
    {
        vSimulieren();
    }
}
