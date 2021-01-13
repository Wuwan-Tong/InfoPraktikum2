#include "Simulation.h"
#include<string>
#include"Kreuzung.h"
#include"PKW.h"
#include"Fahrrad.h"
#include"Tempolimit.h"
#include<string>

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

istream& Simulation::vEinlesen(istream& i)
{
    int zeile = 1;
    string schluesselwort;
    i >> schluesselwort;
    while (!i.eof())
    {
        try
        {
            if (schluesselwort == "KREUZUNG")
            {
                shared_ptr<Kreuzung> k1 = make_shared<Kreuzung>();
                i >> *k1;
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
                bool ueberholverbot;
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
                        throw runtime_error("iTempolimit should be 1,2 or 3!!  Line: "+ to_string(zeile));
                    }
                }
                catch (runtime_error& error)
                {
                    cout << error.what() << endl;
                }

                try
                {
                    switch (iTempolimit)
                    {
                    case 0:
                        ueberholverbot = false;
                        break;
                    case 1:
                        ueberholverbot = true;
                        break;
                    default:
                        ueberholverbot = true;
                        throw runtime_error("iTempolimit should be 1,2 or 3!! line: "+ to_string(zeile));
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

    }
    
}
