// wdsi - Aski lab6.cpp : Defines the entry point for the console application.
//
// ConsoleApplication1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "time.h"
#include "windows.h"
#define NAPIS "lubie wdsi"
#define dlugosc_napisu 10
#define L 2048
#define liczba_iteracji 200
#define wspolczynnik_elitaryzmu 0.05
#define prawdopodobienstwo_mutacji 0.2
#define podzbior_krzyzowan (L/4)



using namespace std;

class osobnik {
public:
	string chromosom;
	unsigned int fitness;

	osobnik() {

		chromosom = losuj_string();
		fitness = 0;
		ocena_przystosowania();
	}
	//----------------------------------------------
	string losuj_string()
	{
		string los;

		for (int j = 0; j < dlugosc_napisu; j++)
			los += rand() % 95 + 32;

		return los;
	}
	//--------------------------------------------------
	void ocena_przystosowania() {

		for (int i = 0; i < 10; i++)
			fitness = fitness + abs(int(chromosom[i]) - NAPIS[i]);
	}
	//----------------------------------------------------
	void wyswietl_osobnika() {

		for (int i = 0; i < 10; i++)
			cout << chromosom[i];
		cout << " ";
	}
	//-----------------------------------------------------
	void wyswietl_ocene_przystosowania() {

		cout << fitness << endl;
	}
	//----------------------------------------------------
	friend bool porownaj(osobnik ob1, osobnik ob2);
	friend void ocena_przystosowania(vector <osobnik> &p);
};


bool porownaj(osobnik ob1, osobnik ob2) {

	if (ob1.fitness < ob2.fitness) return true;
	else return false;
}

int elitaryzm() {

	if (L % 2 == 0)
		return L*wspolczynnik_elitaryzmu;
}

void swapp(vector <osobnik> &p, vector <osobnik> &np, int wsp_elit) {

	for (int i = 0; i < wsp_elit; i++)
		np.push_back(p[i]);
}

float losuj()
{
	return (float)rand() / RAND_MAX;
}

void mutacja(osobnik &o)
{
	int znak, gen;

	znak = rand() % 95 + 32;
	gen = rand() % dlugosc_napisu;
	o.chromosom[gen] = znak;
}

void krzyzowanie(vector<osobnik>&p, vector<osobnik>&np, int wsp_elit) {

	int i1;
	int i2;
	int pkt_podzialu;
	osobnik nowy_osobnik1;
	osobnik nowy_osobnik2;

	for (int i = wsp_elit; i < L; i = i + 2) {

		i1 = rand() % podzbior_krzyzowan;
		i2 = rand() % podzbior_krzyzowan;
		pkt_podzialu = rand() % 9 + 1;
		nowy_osobnik1.chromosom = p[i1].chromosom.substr(0, pkt_podzialu) + p[i2].chromosom.substr(pkt_podzialu, dlugosc_napisu);
		nowy_osobnik2.chromosom = p[i2].chromosom.substr(0, pkt_podzialu) + p[i1].chromosom.substr(pkt_podzialu, dlugosc_napisu);
		if (losuj()<prawdopodobienstwo_mutacji)
			mutacja(nowy_osobnik1);
		nowy_osobnik1.fitness = 0;
		nowy_osobnik1.ocena_przystosowania();
		if (losuj()<prawdopodobienstwo_mutacji)
			mutacja(nowy_osobnik2);
		nowy_osobnik2.fitness = 0;
		nowy_osobnik2.ocena_przystosowania();
		np.push_back(nowy_osobnik1);
		np.push_back(nowy_osobnik2);
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	vector <osobnik> populacja;
	vector <osobnik> nowa_populacja;

	for (int i = 0; i < L; i++) { //tworzenie osobników
		osobnik ob;
		populacja.push_back(ob);
	}

	for (int i = 0; i < liczba_iteracji; i++) {

		sort(populacja.begin(), populacja.end(), porownaj);

		cout << i + 1 << ")" << " ";
		populacja[0].wyswietl_osobnika();
		populacja[0].wyswietl_ocene_przystosowania();

		if (populacja[0].fitness == 0) break;

		swapp(populacja, nowa_populacja, elitaryzm());
		krzyzowanie(populacja, nowa_populacja, elitaryzm());
		populacja = nowa_populacja;
		nowa_populacja.clear();
	}

	system("PAUSE");
}



