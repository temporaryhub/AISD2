﻿// VertexRecu.cpp
/*
	------------ Rozwiaznie zadania "Vertex"-----------------
	link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=216
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
	void dfs_reku(int startVertex, bool *visitTab, int *totalNrOfVertex);	// rekurencyjna metoda przeszukiwania w glab
public:
	AdjacencyList(int nrOfVertex);	// Tworzy graf z okreslona iloscia wierzcholkow izolowanych
	bool insertEdge(int startVertex, int endVertex); // Dodaje do grafu krawedz skierowana z wierzcholka start do end; false jesli nie udalo sie dodac
	void showNotReachable (int vertex);		// Wypisuje na stdout wszystkie wierzcholki nieosiagalne z wierzcholka vertex(ich ilosc i kolejne numery)
	~AdjacencyList(void);	// Destruktor
};

AdjacencyList::AdjacencyList(int nrOfVertex): nrOfVertex(nrOfVertex) {};

void AdjacencyList::dfs_reku(int startVertex, bool *visitTab, int *totalNrOfVertex)
{
	// Dla kazdego wierzcholka z listy sasiedztw badanego wierzcholka startVertex...
	for(std::vector<int>::iterator it = vertexList[startVertex].begin(); it != vertexList[startVertex].end(); ++it)
	{
		if (!visitTab[*it]) // Jezeli jeszcze nie odwiedzalem tego wierzcholka...
		{
			visitTab[*it] = true;	//oznaczam go jako odwiedzony
			(*totalNrOfVertex)--;	//zmniejszam ilosc nieodwiedzonych wierzcholkow
			dfs_reku(*it, visitTab, totalNrOfVertex); // wywoluje dla niego przeszukiwanie DFS
		}
	}
}

bool AdjacencyList::insertEdge(int startVertex, int endVertex)
{
	// Wierzcholki musza miec wartosc dodatnia i mniejsza badz rowna najwiekszemu wierzcholkowi
	if (startVertex > 0 && startVertex <= nrOfVertex && endVertex > 0 && endVertex <= nrOfVertex)
	{
		// Dodaje na koniec listy sasiedztwa wierzcholka startVertex, wierzcholek endVertex
		vertexList[startVertex].push_back(endVertex);
		return true;
	}
	// Zwraca false jezeli nei udalo sie dodac krawedzi
	return false;
}

void AdjacencyList::showNotReachable (int vertex)
{
	if (vertex > 0 && vertex <= nrOfVertex)
	{
		int nrOfUnreachableVertex = nrOfVertex;	// Przechowuje ilosc nieodwiedzonych wierzcholkow
		bool *visitTable = new bool[nrOfVertex + 1];	// Przechowuje wartosc true jezeli wierzcholek o danym numerze(indeks w tablicy) byl odwiedzony 
												// ...indeksy tablicy sa numerami wierzcholkow
		// Wypelniam tablice wartosciami false bo jeszcze nei bylem w zadnym wierzcholku
		std::fill(visitTable, visitTable + nrOfVertex + 1, false);

		// Rekurencyjnie wywoluje przeszukiwanie DFS zaczynajac od wierzcholka vertex
		dfs_reku(vertex, visitTable, &nrOfUnreachableVertex);

		// Zwracam na stdout ilosc nieodwiedzonych wierzcholkow
		std::cout << nrOfUnreachableVertex;

		// Wypisuje na stdout te wierzcholki (ich numery), ktore nei byly odwiedzone (maja wart. false)
		for (int i = 1; i <= nrOfVertex; i++)
			if (!visitTable[i])
				std::cout << " " << i;
		
		delete []visitTable;
	}
}

AdjacencyList::~AdjacencyList(void)
{
	vertexList.clear();
}
//
// ---------------------- FUNKCJA MAIN -----------------------------------
//
int main ()
{
	int nrOfVertex; // Ilosc wierzcholkow w badanym grafie
	int vertexA = 0; // pierwszy wierzcholek do utworzenia krawedzi
	int vertexB; // drugi wierzcholek do utworzenia krawedzi
	int nrOfVertexToTest; // ilosc wierzcholkow do zbadania

	while (std::cin >> nrOfVertex)
	{
		// Sprawdza czy nei doszlismy do konca danych (na wejsciu jest zero dla konca danych)
		if (!nrOfVertex)
			break;

		// Tworze graf z pobrana iloscia wierzcholkow (na razie bez zadnych krawedzi)
		AdjacencyList Graph(nrOfVertex);

		// Pobieram jeden wierzcholek
		std::cin >> vertexB;

		while (true)
		{
			if (vertexA > 0)
				Graph.insertEdge(vertexA, vertexB);

			// Ten przypadek zachodzi, gdy nei ma w ogole krawedzi w grafie
			if (vertexA == 0 && vertexB == 0)
				break;

			vertexA = vertexB;
			std::cin >> vertexB;

			// Jezeli A i B sa == 0 to znaczy ze jest koniec podawania krawedzi i beda podawane wierzcholki do zbadania
			if (vertexA == 0 && vertexB == 0)
				break;
		}
		// Pobiera ilosc wierzcholkow do zbadania
		std::cin >> nrOfVertexToTest;
		// Tablica przechowuje wierzcholki do zbadania
		int *vertexToTest = new int[nrOfVertexToTest];

		// Pobieram wszystkie wierzcholki do zbadania i zapisuje je w tablicy
		for (int i = 0; i < nrOfVertexToTest; i++)
			std::cin >> vertexToTest[i];

		// UWAGA - Specjalnie nie dzialam bezposrednio na pobieranych danych w czasie rzeczywistym bo zdarza sie...
		// ...ze wtedy online judge wyrzuca jakies bledy!

		// Badam, ktore wierzcholki nie sa osiagalne przy przechodzeniu z zadanych wierzcholkow startowych
		for (int i = 0; i < nrOfVertexToTest; i++)
		{
			Graph.showNotReachable(vertexToTest[i]);
			std::cout << std::endl;
		}

		delete []vertexToTest;
	}
	
	return 0;
}