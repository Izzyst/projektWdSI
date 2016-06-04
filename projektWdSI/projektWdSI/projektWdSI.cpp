// projektWdSI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
//#define stala "Lubie WdSI"
#define wielkosc_populacji 2048
#define dlugosc 21
#define iteracja_maks 200
#define wsp_elitaryzmu 0.05
#define mutacja_prawd 0.2
#define podzb_krzyz wielkosc_populacji/4

using namespace std;

class osobnik {
public:
	bool chromosom[21];
	double ocena;
	double przystosowanie(double x);
	osobnik() {
		for (int i = 0; i < 21; i++)
		{
			chromosom[i] = NULL;
		}
		ocena = 0;
	};
	osobnik(bool _chromosom[], double _ocena) { *chromosom  = _chromosom; ocena = _ocena; }
};
//=y
double osobnik::przystosowanie(double x)
{
	return  x + sin(3 * cos(5 * x));
}
//tu zamiast kodowania do 10 powinno byæ do Graya???
// konwertowanie z sys  binarnego do 10
int kodowanieBinarne(osobnik ob)
{
	int x = 0;
	for (int i = 0; i < 21; i++)
	{
		if (ob.chromosom[i])
			x += pow(2, i);
	}
	return x;
}


double losuj_z_przedzialu()
{
	double los;

	for (int j = 0; j < dlugosc; j++)
	{
		los += rand() % 20000;
		los /= 10000;
		cout << los << endl;
	}

	return los;
}

void init_populacja(vector <osobnik> &populacja)
{
	double  os;
	//*os=losuj_z_przedzialu();
	
	srand(time(NULL));
	for (int i = 0; i < wielkosc_populacji; i++)
	{
		os = losuj_z_przedzialu();
		osobnik nowy(os, 0.0);
		populacja.push_back(nowy);
	}
}

/*void fitness(vector <osobnik> &p)
{
	for (int i = 0; i < wielkosc_populacji; i++)
		for (int j = 0; j < dlugosc; j++)
			p[i].fitness += (abs(int(p[i].chromosom[j] - stala[j])));
}*/

bool porownaj(osobnik o1, osobnik o2)
{

	if (o1.przystosowanie(o1.chromosom) < o2.przystosowanie())
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
		//i2 = rand() % podzb_krzyz;
		podzial = rand() % dlugosc;
		osobnik nowy_os1(ps[i1].chromosom.substr(0, podzial) + ps[i2].chromosom.substr(podzial, dlugosc), 0);
		//osobnik nowy_os2(ps[i2].chromosom.substr(0, podzial) + ps[i1].chromosom.substr(podzial, dlugosc), 0);
		if (losuj()<mutacja_prawd)
			mutacja(nowy_os1);
		//if (losuj()<mutacja_prawd)
			//mutacja(nowy_os2);
		pn.push_back(nowy_os1);
		//pn.push_back(nowy_os2);
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

