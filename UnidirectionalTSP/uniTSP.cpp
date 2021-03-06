﻿// uniTSP.cpp
/*
	------ Rozwiaznie zadania "Jednokierunkowy komiwojazer"----------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=52
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>
#include <climits> // wykorzystuje do INT_MAX

// Przechowuje wartosc jednej komorki w tabeli, razem z jej indeksem
struct Cell
{
	int index;
	int value;

	// Przeciazam operatory zeby korzystac z std::min
	bool operator <  (Cell const &c) const { return value  < c.value; }
	bool operator >  (Cell const &c) const { return value  > c.value; }
	bool operator == (Cell const &c) const { return value == c.value; }
};

// Okresla ktorym wierszem sie zajmujemy, potrzebne do utrzymania porzadku leksykograficznego kiedy...
// ...przeskakujemy pomiedzy pierwszym i ostatnim wierszem
enum RowType
{
	firstRow,
	middleRow,
	lastRow
};

// Oblicza minimalna sciezke dla zadanej tablicy i zwraca na stdin
void calculateMinPath (int *tab, int rows, int col)
{
	const int SIZE = rows * col;
	// Tworze tablice w ktorej bede przechowywal minimalne koszty sciezek
	int *costs = new int[SIZE];

	// Ostatnia kolumna tablicy kosztow, jest rowna ostatniej kolumnie pobranej na wejsciu tablicy, bo...
	// ... sprawdzam od prawej do lewej, wiec ostatnia kolumna jest jakby poczatkiem i koszt jest zerowy
	for (int i = col - 1; i < SIZE; i += col)
		costs[i] = tab[i];
	
	// Sprawdzam od prawej do lewej zaczynajac od drugiej kolumny od konca (wytlumaczenie dlaczego - powyzej)
	for (int i = col - 2; i >=0; i--) // Przechodze kolumnami
	{
		for (int j = 0; j < rows; j++) // Przechodze wierszami (tu juz nie ma znaczenia w ktora strone sprawdzam)
		{
			// Poniewaz tabela, po ktorej porusza sie nasz komiwojazer jest jakby nawinieta na poziomym walcu (...
			// ...mozliwe jest przechodzenie z ostatniego, dolnego wiersza, do pierwszego i odwrotnie)...
			// ...obliczony numer wiersza musi to uwzgledniac dlatego "if-else" przy up i down
			int up, middle, down; // Wartosci po prawej od badanej komorki

			// wartosc prawej komorki po skosie "na gorze" w stosunku do aktualnie badanej
			if (j == 0) // Pierwszy wiersz sprawdzamy (zerowy) wiec interesuje nas wartosc z ostatniego tak na prawde
				up = costs[(rows - 1) * col + i + 1];
			else		// Dowolny inny, nie pierwszy wiersz
				up = costs[(j - 1) * col + i + 1];

			// wartosc prawej komorki w tym samym wierszu co aktualnie badana
			middle = costs[j * col + i + 1];

			// wartosc prawej komorki po skosie "na dole" w stosunku do aktualnei badanej
			if (j == rows - 1) // Ostatni wiersz sprawdzamy wiec interesuje nas tak na prawde wartosc z pierwszego (zerowego)
				down = costs[i + 1];
			else				// Sprawdzamy dowolny, nie ostatni wiersz
				down = costs[(j + 1) * col + i + 1];

			// Moj najlepszy koszt to najmnieszy z tych obliczonych kosztow (up, middle i down) powiekszony o wartosc...
			// ...danej komorki, w ktorej sie aktualnie znajduje w tym kroku
			costs[j * col + i] = std::min(up, std::min(middle, down)) + tab[j * col + i];
		} // koniec for (int j = 0; j < rows; j++) 
	} // koniec for (int i = col - 2; i >=0; i--)

	// Szukam pierwszego wiersza z najmniejsza wartoscia w pierwszej kolumnie (pierwszego bo ma byc porzadek leksykograficzny)
	int minCost = INT_MAX;	// Przechowuje najmniejszy koszt przejscia komiwojazera
	int bestIndex = -1;		// Przechowuje numer wiersza rozpoczynajacego najmniejsza sciezke
	for (int i = 0; i < SIZE; i += col)
		if (costs[i] < minCost)
		{
			minCost = costs[i];
			bestIndex = i;
		}

	Cell best; // Najlepsza w danej kolumnie komorka; zaczynamy od obliczonego powyzej miejsca
	best.index = bestIndex;
	best.value = minCost;
	std::cout << (int)(best.index / col) + 1; // Czesc calkowita z dzielenia + 1 bo tablica idzie od zera

	// Poszukuje najlepszej sciezki, tym razem idac od lewej do prawej, zaczynajac od znalezionego minimum
	for (int i = 0; i < col - 1; i++) // Przechodze kolumnami
	{
		// Wartosci na prawo od badanej komorki; szukam najmniejszej z nich -> 'best'
		Cell up, middle, down;
		RowType currentRow = middleRow;	// Jezeli jestesmy w zerowym wierszu i wartosc up i middle sa takie same, to middle...
										// ... powinna byc przed up. Jezeli jestesmy w ostatnim wierszu i middle i down sa takie same...
										// to down jako pierwszy. Ta zmienna tego pilnuje choc nie jest to najladniej zrobione musze przyznac

		// Pobieramy indeks i wartosc komorki z prawej "na gorze"
		up.index = best.index - col + 1;
		if (up.index < 0)		 // Jestesmy w zerowym wierszu
		{
			up.index += SIZE; // Pobieramy wartosc z ostatniego wiersza
			currentRow = firstRow;
		}
		up.value = costs[up.index];

		// wartosc prawej komorkiw tym samym wierszu co aktualnie badana
		middle.index = best.index + 1;
		middle.value = costs[middle.index];

		down.index = best.index + col + 1;
		if (down.index > SIZE)		 // Jestesmy w ostatnim wierszu
		{
			down.index -= SIZE; // Pobieramy wartosc z pierwszego wiersza
			currentRow = lastRow;
		}
		down.value = costs[down.index];

		// Znajduje najmmniejsza wartosc z trzech
		if (currentRow == middleRow)
			best = std::min(up, std::min(middle, down));
		else if (currentRow == firstRow)
			best = std::min(middle, std::min(down, up));
		else
			best = std::min(down, std::min(up, middle));
		std::cout << " " << (int)(best.index / col) + 1; // Taki dziwny zapis bo online judge nie lubi jak jest spacja na koncu wyniku
	} // koniec for (int i = 0; i < col; i++)

	// Na koniec jeszcze wypisuje dlugosc najlepszej sciezki
	std::cout << std::endl << minCost << std::endl;

	delete[] costs;
} // koniec calculateMinPath


int main ()
{
	int rows, columns;	// Przechowuja pobrana ilosc wierszy i kolumn
	int *matrix;		// Pobrana na wejsciu macierz liczbowa do badania trasy

	// Dziala dopoki sa dane wejsciowe na stdin
	while (std::cin >> rows >> columns)
	{
		// Ilosc elementow tablicy
		const int SIZE = rows * columns;
		// Tworzy dynamicznie tablice, ktora pomiesci y na x elementow; odwolanie do elementu matrix[y][x] to matrix[y*col + x]
		matrix = new int[SIZE];

		// Wypelniam utworzona tablice liczbami z stdin
		for (int i = 0; i < SIZE; i++)
				std::cin >> matrix[i]; 

		// Obliczam minimalna sciezke dla pobranej tablicy
		calculateMinPath(matrix, rows, columns);

		// Usuwam tablice na koniec obliczen bo juz jej nie potrzebuje, stworze nowa w nastepnej petli...
		// ...powinno byc troszke wydajniej niz jakby ustawic na sztywno rozmiar 10 x 100 (bo taki moze byc max)
		delete[] matrix;
	}// koniec glownego while
	return 0;
} // koniec main