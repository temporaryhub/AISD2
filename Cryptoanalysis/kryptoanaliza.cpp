// kryptoanaliza.cpp
/*
	--------- Rozwiaznie zadania "Co to jest kryptoanaliza?"---------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=949
	------------------------ Pawe³ Stysz 2013 -----------------------
	----------- Zajêcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <cstdlib>

#define NR_OF_LETTERS 25

typedef std::pair<char, int> KeyValuePair;

int comp(const void *p1, const void *p2)
{
    KeyValuePair *pair1 = (KeyValuePair*)p1;    
	KeyValuePair *pair2 = (KeyValuePair*)p2; 
	// Porownuje pary klucz - wartosc wedlug ilosci wystapien
	int result = pair2->second - pair1->second;
	if (result) return result;
	// Jezeli ilosc wystapien jest taka sama to litery wedlug kolejnosci w alfabecie
	return (int)pair1->first - (int)pair2->first;
}


int main ()
{
	std::map<char, int> letters;		// Tablica asocjacyjna liter
	int nrOfLines;	// Tu przechowuje ilosc linii tekstu do pobrania
	KeyValuePair *pairsTab = new KeyValuePair[NR_OF_LETTERS]; // Tablica par klucz - wartosc do posortowania
	
	// Wypelniam cala tablice kluczami i wartosciami zero...
	// ...dzieki temu nie bede musial sprawdzac czy klucz istnieje tylko bede zwiekszal wartosc
	for (char i = 'A'; i <= 'Z'; i++)
		letters[i] = 0;

	// Pobieram ilosc linii tekstu do analizy
	std::cin >> nrOfLines;

	for (int i = 0; i <= nrOfLines; i++)
	{
		std::string line; // Tu bede przechowywal jedna linie tekstu z wejscia

		// Pobieram jedna linie tekstu
		std::getline(std::cin, line);

		// Przechodze przez kazda litere z pobranej linijki
		for (int j = 0; j < (int)line.length(); j++)
		{
			// Jezeli dany znak jest litera to zmieniam ja na wielka litere i zwiekszam ilosc wystapien
			if (isalpha(line[j]))
				letters[toupper(line[j])] += 1;
		}

	}

	int j = 0; // Wypelniam tablice par klucz-wartosc danymi z tablicy asocjacyjnej
	for (char i = 'A'; i <= 'Z'; i++)
		pairsTab[j++] = KeyValuePair(i, letters[i]);

	// Sortuje malejaco wedlug ilosci wystapien
	std::qsort(pairsTab, NR_OF_LETTERS, sizeof(KeyValuePair), comp);

	// Wypisuje litery i ilosci wystapien, jezeli dojde do zerowych wystapien - przerywam
	for (int i = 0; i < NR_OF_LETTERS; i++)
	{
		if (pairsTab[i].second > 0)
			std::cout << pairsTab[i].first << " " << pairsTab[i].second << std::endl;
		else
			break;
	}

	return 0;
}