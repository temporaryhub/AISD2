/*  main2.cpp

	------------------------ Waga Binarna ---------------------------
	link do treści zadania: http://main.edu.pl/pl/archive/pa/2001/wag
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	----------------------------------------------------------------- */

#include <iostream>
#include <cstdlib>
#define N 11

using namespace std;

struct WynikPomiaru
{
	long l;
	long m;
	long cmp; // Wartoć licznika l ułamka l/m przy mianowniku m powiększonym do 2^10
};

int comp(const void *p1, const void *p2)
{
    const struct WynikPomiaru *elem1 = (WynikPomiaru*)p1;    
	const struct WynikPomiaru *elem2 = (WynikPomiaru*)p2;
	// W pierwszej kolejnoci porównuję według wartoci licznika ułamków l/m sprowadzonych do wspólnego mianownika równego 2^10
	long roznica = elem1->cmp - elem2->cmp;
	// Jeżeli są różne to zwracam <0 jeżeli elem1 przed elem2, oraz >0 jeżeli elem2 przed elem1
	if (roznica) return (int)roznica;
	// Jeżeli liczniki są równe porównuję mianowniki
	return (int)(elem1->m - elem2->m);
}

int main (void)
{
	int n;
	cin >> n;

	long tablicaPoteg2[N];		// Tu przechowuje wartosci 2^(1...10)
	WynikPomiaru *tablicaWag;	// Tablica  wartosci w ukladzie {l, m, wartosc licznika l przy mianowniku = 2^10}
	tablicaWag = new WynikPomiaru[n]; // Tablica będzie miała n elementów składajšcych się ze struktur "Wynik pomiaru"

	tablicaPoteg2[0] = 1; // wartoć potęgi 2^0
	// Tworze tablice kolejnych poteg dwojki, zeby potem tylko mnozyc przez konkretna liczbe, bez potegowania
	// Indeksy tablicy odpowiadaja wykladnikowi potegi dwojki, wartosci to wynik potegowania
	for (int i = 1; i < N; i++)
		tablicaPoteg2[i] = tablicaPoteg2[i-1] * 2;

	// Przygotowuje dane do sortowania
	for (int i = 0; i < n; i++)
	{
		cin >> tablicaWag[i].l >> tablicaWag[i].m; // Zczytuję z pliku wejciowego l i m
		tablicaWag[i].cmp = tablicaPoteg2[10 - (int)tablicaWag[i].m] * tablicaWag[i].l; // Sprowadzam wszystkie ulamki do wspolnego mianownika i zapisuje wart. licznika na 3 poz. tablicy
	}

	qsort(tablicaWag, n, sizeof(WynikPomiaru), comp); // Sortuje tablice struktur wedlug wartosci licznikow ulamkow sprowadzonych do wspolnego mianownika
	
	// Wypisuje na stdout
	for (int i = 0; i < n; i++)
		cout << tablicaWag[i].l << " " << tablicaWag[i].m << endl;

	delete [] tablicaWag;
	return 0;
}




