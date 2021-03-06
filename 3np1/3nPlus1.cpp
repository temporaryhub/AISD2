﻿// 3nPlus1.cpp
/*
	------------ Rozwiaznie zadania "Problem 3n + 1"-----------------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=36
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/


#include <iostream>

#define N_SIZE 1000001

// Tablica przechowujaca oblczone wartosci n; 0 jezeli wartosc jeszcze nie obliczona.
//  Pobierane z stdin n <= 1000000 dlatego rozmiar o jeden wiekszy, zeby zgadzaly sie indeksy
int calculatedCycletab[N_SIZE];

// Funkcja zwraca dlugosc cyklu dla podanego n
int calculateCycle (int n)
{
	// UWAGA - obliczane aktualnie (nie pobierane) n moze byc wieksze niz 1000000 np. dla pierwszego kroku gdy j = 999999 dlatego nie zawsze...
	//...sie zmiesci w tablicy, trzeba jeszcze sprawdzic, czy w ogole moge pobrac te wartosc z tab. lub zrobic tablice o rozm. max 3*1000000+1

	// Sprawdzam czy n nie wykracza poza tablicy i czy obliczylem juz wczesniej wartosc dla n...
	if (n < N_SIZE && calculatedCycletab[n])
		//...jezeli tak, to nie licze ponownie, tylko ja zwracam
		return calculatedCycletab[n];

	// Liczenie dl. cyklu dla n nieparzystych
	if (n % 2)
	{
		// Jezeli mieszcze sie w tablicy to na niej dzialam
		if (n < N_SIZE) 
		{
			// W n-tym indeksie wpisuje dlugosc cyklu rekurencyjnie; dodaje 1 bo w "tym" wywolaniu juz obliczylem jedna wartosc
			calculatedCycletab[n] = 1 + calculateCycle(3*n + 1);
			return calculatedCycletab[n];
		}
		// Jezeli nie mieszcze sie w tablicy to tylko obliczam
		else
			return 1 + calculateCycle(3*n + 1);
	}
	// Liczenie dl. cyklu dla n parzystych
	else
	{
		// Jezeli mieszcze sie w tablicy to na niej dzialam
		if (n < N_SIZE) 
		{
			// W n-tym indeksie wpisuje dlugosc cyklu rekurencyjnie; dodaje 1 bo w "tym" wywolaniu juz obliczylem jedna wartosc
			calculatedCycletab[n] = 1 + calculateCycle(n / 2);
			return calculatedCycletab[n];
		}
		// Jezeli nie mieszcze sie w tablicy to tylko obliczam
		else
			return 1 + calculateCycle(n / 2);
	}
}

int main ()
{
	// Wypelniam tablice zerami
	std::fill(calculatedCycletab, calculatedCycletab + N_SIZE, 0);
	// UWAGA - BARDZO WAZNE! To nam zapewnia wyjscie z rekurencji bo zgodnie z trescia zadania - zawsze dojdziemy do 1 i wtedy jest koniec
	calculatedCycletab[1] = 1;
	// Przechowuje min i max zakresu, z jakiego badane sa liczby
	int i, j;

	// Wykonuj dopoki sa dane wejsciowe
	while (std::cin >> i >> j)
	{
		// Wartosc maksymalnego cyklu dla liczby z zakresu od i do j
		int maxCycle = 0;

		// Pierwsza z liczb jest wieksza od drugiej, idziemy od j do i po kolei (rosnaco)
		if (i >= j)
		{		
			for (int n = j; n <= i; n++)
			{
				// Obliczam dlugosc cyklu dla danego n
				int temp = calculateCycle(n);
				// Jezeli wartosc cyklu jest wieksza niz maksymalna - podstawiam obliczona, jako maksymalna
				if (temp > maxCycle)
					maxCycle = temp;
			}
		}
		// Druga z liczba jest wieksza, idziemy od i do j po kolei
		else
		{
			for (int n = i; n <=j; n++)
			{
				// Obliczam dlugosc cyklu dla danego n
				int temp = calculateCycle(n);
				// Jezeli wartosc cyklu jest wieksza niz maksymalna - podstawiam obliczona, jako maksymalna
				if (temp > maxCycle)
					maxCycle = temp;
			}
		}
		// Wypisuje na stdout obliczony wynik
		std::cout << i << " " << j << " " << maxCycle << std::endl;
	}


	return 0;
}