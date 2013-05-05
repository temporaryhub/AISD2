﻿// Bicoloring.cpp
/*
	--------------- Rozwiaznie zadania "Bicoloring"------------------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=945
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <map>


// Implementacja reprezentacji grafu skierowanego jako listy sasiedztw
class AdjacencyList
{
private:
	int nrOfVertex;	// Ilosc wierzcholkow w grafie
	std::map<int, std::vector<int> > vertexList; // Lista wierzcholkow z ich sasiadami
	std::map<int, std::vector<int> >::iterator iter; // iterator do poruszania sie po liscie wierzcholkow
	bool dfs_reku(int startVertex, int *colorsTab, int color);	// rekurencyjna metoda przeszukiwania w glab z kolorowaniem wierzcholkow

public:
	AdjacencyList(int nrOfVertex);	// Tworzy graf z okreslona iloscia wierzcholkow izolowanych
	bool insertEdge(int startVertex, int endVertex); // Dodaje do grafu krawedz pomiedzy wierzcholkami start i end; false jesli nie udalo sie dodac
	void showVertexNeighbors (int vertex);	// Wypisuje na stdout sasiadow danego weirzcholka (wierzcholki, do ktorych prowadza krawdzie z vertex)
	bool isBicolorable(void);				// Określa czy graf jest dwudzielny czy nie
	~AdjacencyList(void);	// Destruktor
};

AdjacencyList::AdjacencyList(int nrOfVertex): nrOfVertex(nrOfVertex) {};

bool AdjacencyList::dfs_reku(int startVertex, int *colorsTab, int color)
{
	colorsTab[startVertex] = color; // Nadaje określony kolor wierzchołkowi i jednoczesnie oznacza, że już go odwiedzaliśmy

	// Dla kazdego wierzcholka z listy sasiedztw badanego wierzcholka startVertex...
	for(std::vector<int>::iterator it = vertexList[startVertex].begin(); it != vertexList[startVertex].end(); ++it)
	{
		if (!colorsTab[*it]) // Jezeli jeszcze nie odwiedzalem tego wierzcholka...
			dfs_reku(*it, colorsTab, -color); // wywoluje dla niego przeszukiwanie DFS i nadaje kolor przeciwny do wierzch. startVertex
		else if (colorsTab[*it] == colorsTab[startVertex]) // Już go odwiedzałem, sprawdzam czy ma kolor przeciwny do startVertex, jeżeli nie...
			return false;									// ...to już wiadomo, że graf nei jest dwudzielny i nie trzeba dalej sprawdzać
	}

	return true; // sprawdziłem wszystkie wierzchołki, kolory się zgadzały, wiec mamy graf dwudzielny - zwracam true
}

bool AdjacencyList::insertEdge(int startVertex, int endVertex)
{
	// Wierzcholki musza miec wartosc nieujemna i mniejsza od ilosci wierzcholkow bo numerujemy od zera
	if (startVertex >= 0 && startVertex < nrOfVertex && endVertex >= 0 && endVertex < nrOfVertex)
	{
		// Dodaje na koniec listy sasiedztwa wierzcholka startVertex, wierzcholek endVertex
		vertexList[startVertex].push_back(endVertex);
		// UWAGA - graf jest nieskierowany więc na koniec listy sąsiedztwa endVertex trzeba też dodać startVertex bo krawędzie są jakby dwukierunkowe
		vertexList[endVertex].push_back(startVertex);
		return true;
	}
	// Zwraca false jezeli nei udalo sie dodac krawedzi
	return false;
}

// Tylko do testow, nie potrzebne w zadaniu
void AdjacencyList::showVertexNeighbors (int vertex)
{
	if (vertex >= 0 && vertex < nrOfVertex)
	{
		// Jezeli wierzcholek nie jest izolowany
		if (vertexList[vertex].size())
		{
			// Wypisuje na stdout kazdy element obiektu klasy vector
			for(std::vector<int>::iterator it = vertexList[vertex].begin(); it != vertexList[vertex].end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
		}
		// Zwraca -1 jezeli wierzcholek jest izolowany
		else
			std::cout << -1 << std::endl;
	}
	// Zwraca -2 jezeli wierzcholek nie istnieje
	else
		std::cout << -2 << std::endl;
}

bool AdjacencyList::isBicolorable(void)
{
	// Przechowuje kolory dla wierzcholkow; indeks tablicy to nr wierzcholka
	int *colorsTab = new int[nrOfVertex];
	bool ans; // Tu bedzie zapisana odpowiedz, nei moge zrobic po prostu return, bo na koniec musze usunac jeszcze tablice colorsTab
	// zeruje tablice kolorow co oznacza, ze wierzcholki nie zostaly odwiedzone
	std::fill(colorsTab, colorsTab + nrOfVertex, 0);
	// Ustawiam kolory rekurencyjnie dla wszystkich wierzcholkow
	ans = dfs_reku(0, colorsTab, 1);
	delete [] colorsTab;
	return ans;
}

AdjacencyList::~AdjacencyList(void)
{
	vertexList.clear();
}

int main ()
{
	int nrOfVertex; // Ilosc wierzcholkow w badanym grafie
	int vertexA; // pierwszy wierzcholek do utworzenia krawedzi
	int vertexB; // drugi wierzcholek do utworzenia krawedzi
	int nrOfEdges; // ilosc krawedzi do pobrania

	while (true)
	{
		// Pobiera ilosc wierzcholkow w grafie
		std::cin >> nrOfVertex;

		// Sprawdza czy nei doszlismy do konca danych (na wejsciu jest zero dla konca danych)
		if (!nrOfVertex)
			break;

		// Tworze graf z pobrana iloscia wierzcholkow (na razie bez zadnych krawedzi)
		AdjacencyList Graph(nrOfVertex);

		// Pobieram ilosc krawedzi do utworzenia
		std::cin >> nrOfEdges;

		// Łączę odpowiednie wierzchołki podanymi krawędziami
		for (int i = 0; i < nrOfEdges; i++)
		{
			std::cin >> vertexA;
			std::cin >> vertexB;

			Graph.insertEdge(vertexA, vertexB);
		}

		 //Badam utworzony graf funkcją isBicolorable i zwracam na stdout wynik
		if (Graph.isBicolorable())
			std::cout << "BICOLORABLE." << std::endl;
		else
			std::cout << "NOT BICOLORABLE." << std::endl;
	}
	
	return 0;
}