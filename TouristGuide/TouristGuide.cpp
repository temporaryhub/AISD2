﻿// TouristGuide.cpp
/*
	------------ Rozwiaznie zadania "Tourist Guide"-----------------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1040
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include <cstdio>

#define INFINITY -1 // definiuje minus jeden jako namniejsza pojemnosc busa na trasie (krawedzi), ktora nei istnieje

int main ()
{
	int nrOfCities, nrOfRoads;
	int capacityTab[101][101];	// Tablica bedzie przechowywac pojemnosci autobusow kursujacych pomiedzy miastami tak, ze capacityTab[i][j]...
								// ... bedzie przechowywac maksymalna ilosc pasazerow mozliwych do przewiezienia pomiedzy miastem i oraz j
	// UWAGA - moze byc max 100 miast, ale miasta sa ideksowane od 1, a nie od 0, dlatego tablica ma wymiary 101x101
	int city1, city2, passengersLimit;
	int departure, destination, passengersToCarry;
	int scenarioNo = 1; // Przechowuje numer scenariusza, ktory aktalnie jest analizowany

	while (true)
	{
		std::cin >> nrOfCities;	// Pobieram ilosc wierzcholkow grafu (miast)
		std::cin >> nrOfRoads;	// Pobieram ilosc krawdzi grafu (drog pomiedzy miastami)

		if (!nrOfCities && !nrOfRoads)
			break;		// zero miast i drog oznacza, ze jest koniec danych wejsciowych - przerywam program

		// Wypelniam tablice ujemnymi wartosciami, dzieki czemu nie wybierzemy połączeń, których nie ma
		for (int i = 0; i <= nrOfCities; i++)
			std::fill(capacityTab[i], capacityTab[i] + nrOfCities, INFINITY);

		// Zeruje wartosci na przekatnej bo to nei są autobusy miejskie tylko międzymiastowe :)
		for (int i = 1; i <= nrOfCities; i++)
			capacityTab[i][i] = 0;

		// Wypelniam tablice drog faktycznymi pojemnosciami autobusow, pobranymi z danych zadania
		for (int i = 0; i < nrOfRoads; i++)
		{
			// Dane sa podawane w formacie: "numer miasta poczatkowego" "numer miasta docelowego" "pojemnosc autobusu"
			std::cin >> city1;
			std::cin >> city2;
			std::cin >> passengersLimit;
			// UWAGA - odejmujemy 1 na końcu bo przewodnik też musi jechać i zajmuje jedno miejsce zawsze
			capacityTab[city1][city2] = capacityTab[city2][city2] = passengersLimit - 1;
			// Prawdopodobnie wystarczyla by tylko polowa tablicy bo koszt przejazdu z city1 do city2 == city2 do city1 ale nei jestem pewien - do sprawdzenia
		}

		// Pobieram numer miasta, z ktorego rozpoczynamy podroz, cel podrozy oraz ilosc pasazerow do przewiezienia
		std::cin >> departure;
		std::cin >> destination;
		std::cin >> passengersToCarry;

		if (departure == destination) // Obsluguje przypadek, gdy miasto poczatkowe jest takie samo jak docelowe
			printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", scenarioNo++, 1);
		else // Miasta sa rozne, nalezy znalezc najlepsza trase
		{
			// Wykorzystuje algorytm Floyda-Warshalla tylko wyszukuje droge o najwyzszych, a nie najmniejszych wagach
			for(int k = 1; k <= nrOfCities; k++)
				for(int i = 1; i <= nrOfCities; i++)
					for(int j = 1; j <= nrOfCities; j++)
					{
// TU JEST GDZIES BLAD ->
							if (capacityTab[i][k] < 0 && capacityTab[k][j] > 0) // < 0 oznacza, ze dane polaczenie nie istnieje
								capacityTab[i][j] = std::max(capacityTab[i][j], capacityTab[k][j]);
							else if (capacityTab[k][j] < 0 && capacityTab[i][k] > 0)
								capacityTab[i][j] = std::max(capacityTab[i][j], capacityTab[i][k]);
							else if (capacityTab[k][j] > 0 && capacityTab[i][k] > 0)
								capacityTab[i][j] = std::max(capacityTab[i][j], std::min(capacityTab[i][k], capacityTab[k][j]));
					}
			
			int result = (int)std::ceil((float)passengersToCarry / (float)(capacityTab[departure][destination]));
			if (result <= 0)
				result = 1;

			// W tabeli pod indeksem [departure][destination] znajduja sie maksymalna ilosc pasazerow mozliwych do przetransportowania za jednym razem
			// Teraz wystarczy podzielic ilosc pasazerow przez obliczona wartosc i wziac z tego sufit - tyle kursow bedzie trzeba wykonac zeby przewiezc wszystkich
			printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", scenarioNo++, result);
		}
/*// ------- TYLKO DO TESTÓW ------------
		printf("Ilosc pasazerow: %3d, start: %3d, koniec: %3d\n", passengersToCarry, departure, destination);

		std::cout << "   ";
		for (int i = 1; i <= nrOfCities; i++)
			printf("%3d", i);
		std::cout << std::endl;
		for (int i = 1; i <= nrOfCities; i++)
		{
			printf("%3d", i);
			for (int j = 1; j <= nrOfCities; j++)
				printf("%3d", capacityTab[i][j]);
			std::cout << std::endl;
		}
		std::cout << "--------------------------------------" << std::endl;
*/
	}

	return 0;
}