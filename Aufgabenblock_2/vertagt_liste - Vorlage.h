#pragma once

//#include "vertagt_aktion.h"
#include"vertagt_aktion - Vorlage.h"
#include <list>
#include<memory>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; // Benötigt man einen Standardkonstruktor?
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			for (auto it = p_objekte.begin();it != p_objekte.end();it++)
			{
				erase(it);
			}
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			if (p_objekte.begin() == nullptr)
			{
				return true;
			}
			else
				return false;
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(make_unique<VPushBack<T>>(p_objekte, move(obj)));
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(make_unique<VPushFront<T>>(p_objekte, move(obj)));
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(make_unique<VErase<T>>(p_objekte, move(it)));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			while (!p_aktionen.empty())
			{
				// Aktionszeiger auf 1. Element bestimmen und in Liste entfernen
				std::unique_ptr <VAktion<T>> p_aktion = move(p_aktionen.front());
				

				// Aktion ausführen
				p_aktion->vAusfuehren();
				p_aktionen.pop_front();
			}
		}
	};
} // namespace vertagt
