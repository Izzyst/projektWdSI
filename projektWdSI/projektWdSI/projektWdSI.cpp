// projektWdSI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// lab6WdSI.cpp : Defines the entry point for the console application.
//
/*
#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#define stala "Lubie WdSI" // szukany tekst
#define wielkosc_populacji 2048
#define dlugosc 10
#define iteracja_maks 200
#define wsp_elitaryzmu 0.05
#define mutacja_prawd 0.2
#define podzb_krzyz wielkosc_populacji/4
#define PI 3.14159
using namespace std;
//klasa reprezentuj¹ca danego osobnika
class osobnik {
public:
long double chromosom;
long double fitness;
osobnik(long double nazwa, long double przystosowanie);
};

osobnik::osobnik(long double nazwa, long double przystosowanie)
{
chromosom = nazwa;
fitness = przystosowanie;
}
// losowanie dowolnych znaków
string losuj_string()
{
string los;

for (int j = 0; j < dlugosc; j++)
los += rand() % 95 + 32;
cout << los << endl;

return los;
}
// inicjalizacja populacji
// inicjalizacja iksów
void init_populacja(vector <osobnik> &populacja)
{
string os;
srand(time(NULL));
for (int i = 0; i < wielkosc_populacji; i++)
{
osobnik nowy(i, 0);
populacja.push_back(nowy);
}
}
// funkcja oceny przystosowania
void fitness(vector <osobnik> &p)
{
for (int i = 0; i < wielkosc_populacji; i++)
{//for (int j = 0; j < dlugosc; j++)
p[i].fitness = 1.0 + p[i].chromosom*sin(10 * PI * p[i].chromosom);
}
}
// porownanie wartoœci fitness
bool porownaj(osobnik o1, osobnik o2)
{
if (o1.fitness < o2.fitness)
return true;
else
return false;
}
// funkcja zamieniaj¹ca etykiety wektorów
void swap(vector <osobnik> &ps, vector <osobnik> &pn, int esize)
{
for (int i = 0; i<esize; i++)
pn.push_back(ps[i]);
}

int wspolczynnik_elitaryzmu()
{
if (wielkosc_populacji % 2 == 0)
return wielkosc_populacji*wsp_elitaryzmu;
}

float losuj()
{
return (float)rand() / RAND_MAX;
}

void mutacja(osobnik &o)
{
int znak, gen;

znak = rand() % 95 + 32;
gen = rand() % dlugosc;
o.chromosom[gen] = znak;
}

void krzyzowanie(vector <osobnik> &ps, vector <osobnik> &pn, int esize)
{
int i1, i2, podzial;
for (int i = esize; i<wielkosc_populacji; i += 2)
{
i1 = rand() % podzb_krzyz;
i2 = rand() % podzb_krzyz;
podzial = rand() % dlugosc;
osobnik nowy_os1(ps[i1].chromosom.substr(0, podzial) + ps[i2].chromosom.substr(podzial, dlugosc), 0);
osobnik nowy_os2(ps[i2].chromosom.substr(0, podzial) + ps[i1].chromosom.substr(podzial, dlugosc), 0);
if (losuj()<mutacja_prawd)
mutacja(nowy_os1);
if (losuj()<mutacja_prawd)
mutacja(nowy_os2);
pn.push_back(nowy_os1);
pn.push_back(nowy_os2);
}
}

//void sort((*bool)(sortuj))


int _tmain(int argc, _TCHAR* argv[])
{
vector <osobnik> populacja;
vector <osobnik> nowap;
int esize;
init_populacja(populacja);
cout << "Lp\tNajlepszy osobnik\n";
for (int i = 0; i<iteracja_maks; i++)
{
fitness(populacja);
sort(populacja.begin(), populacja.end(), porownaj);
cout << i << "\t" << populacja[0].chromosom;
cout << endl;
if (populacja[0].fitness == 0)
break;
esize = wspolczynnik_elitaryzmu();
swap(populacja, nowap, esize);
//krzyzowanie(populacja, nowap, esize);
populacja = nowap;
nowap.clear();
}
system("PAUSE");
return 0;
}

*/

// lab5.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#define stala "Lubie WdSI"
#define wielkosc_populacji 2048
#define dlugosc 10
#define iteracja_maks 200
#define wsp_elitaryzmu 0.05
#define mutacja_prawd 0.2
#define podzb_krzyz wielkosc_populacji/4

using namespace std;

class osobnik {
public:
	string chromosom;
	unsigned int fitness;
	osobnik(string nazwa, unsigned int przystosowanie);
};

osobnik::osobnik(string nazwa, unsigned int przystosowanie)
{
	chromosom = nazwa;
	fitness = przystosowanie;
}

string losuj_string()
{
	string los;

	for (int j = 0; j < dlugosc; j++)
		los += rand() % 95 + 32;
	cout << los << endl;

	return los;
}

void init_populacja(vector <osobnik> &populacja)
{
	string os;
	srand(time(NULL));
	for (int i = 0; i < wielkosc_populacji; i++)
	{
		os = losuj_string();
		osobnik nowy(os, 0);
		populacja.push_back(nowy);
	}
}

void fitness(vector <osobnik> &p)
{
	for (int i = 0; i < wielkosc_populacji; i++)
		for (int j = 0; j < dlugosc; j++)
			p[i].fitness += (abs(int(p[i].chromosom[j] - stala[j])));
}

bool porownaj(osobnik o1, osobnik o2)
{
	if (o1.fitness < o2.fitness)
		return true;
	else
		return false;
}

void swap(vector <osobnik> &ps, vector <osobnik> &pn, int esize)
{
	for (int i = 0; i<esize; i++)
		pn.push_back(ps[i]);
}

int wspolczynnik_elitaryzmu()
{
	if (wielkosc_populacji % 2 == 0)
		return wielkosc_populacji*wsp_elitaryzmu;
}

float losuj()
{
	return (float)rand() / RAND_MAX;
}

void mutacja(osobnik &o)
{
	int znak, gen;

	znak = rand() % 95 + 32;
	gen = rand() % dlugosc;
	o.chromosom[gen] = znak;
}

void krzyzowanie(vector <osobnik> &ps, vector <osobnik> &pn, int esize)
{
	int i1, i2, podzial;
	for (int i = esize; i<wielkosc_populacji; i += 2)
	{
		i1 = rand() % podzb_krzyz;
		i2 = rand() % podzb_krzyz;
		podzial = rand() % dlugosc;
		osobnik nowy_os1(ps[i1].chromosom.substr(0, podzial) + ps[i2].chromosom.substr(podzial, dlugosc), 0);
		osobnik nowy_os2(ps[i2].chromosom.substr(0, podzial) + ps[i1].chromosom.substr(podzial, dlugosc), 0);
		if (losuj()<mutacja_prawd)
			mutacja(nowy_os1);
		if (losuj()<mutacja_prawd)
			mutacja(nowy_os2);
		pn.push_back(nowy_os1);
		pn.push_back(nowy_os2);
	}
}

//void sort((*bool)(sortuj))


int _tmain(int argc, _TCHAR* argv[])
{
	vector <osobnik> populacja;
	vector <osobnik> nowap;
	int esize;
	init_populacja(populacja);
	cout << "Lp\tNajlepszy osobnik\n";
	for (int i = 0; i<iteracja_maks; i++)
	{
		fitness(populacja);
		sort(populacja.begin(), populacja.end(), porownaj);
		cout << i << "\t" << populacja[0].chromosom;
		cout << endl;
		if (populacja[0].fitness == 0)
			break;
		esize = wspolczynnik_elitaryzmu();
		swap(populacja, nowap, esize);
		krzyzowanie(populacja, nowap, esize);
		populacja = nowap;
		nowap.clear();
	}
	system("PAUSE");
	return 0;
}





