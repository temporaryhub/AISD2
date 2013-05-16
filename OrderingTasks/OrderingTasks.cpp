﻿/* OrderingTasks.cpp

  --------------- Rozwiaznie zadania "Ordering Tasks"------------------
  link do tresci: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1246
  ------------------------ Paweł Stysz 2013 -----------------------
  ----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
  -----------------------------------------------------------------
*/
#include <stack>
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
	void dfs_reku(int startVertex, bool *visitTab, std::stack<int> *topologicalStack);	// rekurencyjna metoda przeszukiwania w glab
public:
	AdjacencyList(int nrOfVertex);	// Tworzy graf z okreslona iloscia wierzcholkow izolowanych
	bool insertEdge(int startVertex, int endVertex); // Dodaje do grafu krawedz skierowana z wierzcholka start do end; false jesli nie udalo sie dodac
	void showVertexNeighbors (int vertex);	// Wypisuje na stdout sasiadow danego weirzcholka (wierzcholki, do ktorych prowadza krawdzie z vertex)
											// ...zwraca 0 jezeli wierzcholek jest izolowany, -1 jezeli wierzcholek nie istnieje w grafie
	void topologicalSort (void);		// Wypisuje na stdout sortowanie topologiczne ustalonego grafu
	~AdjacencyList(void);	// Destruktor
};

AdjacencyList::AdjacencyList(int nrOfVertex): nrOfVertex(nrOfVertex) {};

void AdjacencyList::dfs_reku(int startVertex, bool *visitTab, std::stack<int> *topologicalStack)
{
	visitTab[startVertex] = true; // oznaczam wierzcholek, ktorego liste sasiedztw aktualnie badam, jako odwiedzony
	// Dla kazdego wierzcholka z listy sasiedztw badanego wierzcholka startVertex...
	for(std::vector<int>::iterator it = vertexList[startVertex].begin(); it != vertexList[startVertex].end(); ++it)
		if (!visitTab[*it]) // Jezeli jeszcze nie odwiedzalem tego wierzcholka...
			dfs_reku(*it, visitTab, topologicalStack); // wywoluje dla niego przeszukiwanie DFS

	topologicalStack->push(startVertex); // odkladam 'ostatni' (czyli z najwiekszym czasem zamkniecia) wierzcholek na stos
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

// Tylko do testow, nie potrzebne w zadaniu
void AdjacencyList::showVertexNeighbors (int vertex)
{
	if (vertex > 0 && vertex <= nrOfVertex)
	{
		// Jezeli wierzcholek nie jest izolowany
		if (vertexList[vertex].size())
		{
			// Wypisuje na stdout kazdy element obiektu klasy vector
			for(std::vector<int>::iterator it = vertexList[vertex].begin(); it != vertexList[vertex].end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
		}
		// Zwraca zero jezeli wierzcholek jest izolowany
		else
			std::cout << 0 << std::endl;
	}
	// Zwraca -1 jezeli wierzcholek nie istnieje
	else
		std::cout << -1 << std::endl;
}

void AdjacencyList::topologicalSort (void)
{
	if (nrOfVertex > 0)
	{
		std::stack<int> topologicalSortedStack;		// Przechowuje kolejne wierzcholki grafu posortowane topologicznie
		bool *visitTable = new bool[nrOfVertex + 1];	// Przechowuje wartosc true jezeli wierzcholek o danym numerze(indeks w tablicy) byl odwiedzony 
														// ...indeksy tablicy sa numerami wierzcholkow
		// Wypelniam tablice wartosciami false bo jeszcze nei bylem w zadnym wierzcholku
		std::fill(visitTable, visitTable + nrOfVertex + 1, false);

		// Rekurencyjnie wywoluje przeszukiwanie DFS zaczynajac od wierzcholka pierwszego, dla wszystkich wierzcholkow
		for (int i = 1; i <= nrOfVertex; i++)
			if (!visitTable[i]) // sprawdzam, czy juz nie odwiedzilem danego wierzcholka wczesniej
				dfs_reku(i, visitTable, &topologicalSortedStack);

		// Zwracam na stdout numery wszystkich wierzcholkow posortowanych topologicznie
		while (true) // dopoki w kolejce znajduja sie jeszcze wierzcholki, wykonuj...
		{
			std::cout << topologicalSortedStack.top(); // zwroc pierwszy element ze stosu
			topologicalSortedStack.pop();				// zdejmij pierwszy element se stosu

			if (topologicalSortedStack.empty()) // to by moglo byc w warunku while ale ta konstrukcja zapewnia brak nadmiarowych spacji dla UVa
				break;
			else
				std::cout << " ";
		}
		std::cout << std::endl;

		delete []visitTable;
	}

}

AdjacencyList::~AdjacencyList(void)
{
	vertexList.clear();
}

//---------------------------------------------------------------------------------
// ----------------------------------- MAIN ---------------------------------------
//---------------------------------------------------------------------------------

int main ()
{
	int n, m; // odpowiednio ilosc wszystkich zadan i ilosc znanych zaleznosci pomiedzy nimi
	int a, b; // zadania, pomiedzy ktorymi zachodzi jakas zaleznosc taka ze a musi byc przed b

	while (true)
	{
		std::cin >> n; // pobieram ilosc wszyskich zadan czyli ilosc wierzcholkow grafu
		std::cin >> m; // pobieram ilosc roznych zaleznosci pomiedzy zadaniami, czyli ilosc krawedzi skierowanych

		if (n == 0 && m == 0) // brak zadan i krawedzi == koniec danych
			break;
		else if (m == 0) // sa wierzcholki ale brak krawedzi, wypisuje tylko wierzcholki po kolei
		{
			for (int i = 1; i <= n; i++)
			{
				std::cout << i;

				if (i < n)
					std::cout << " ";
			}

			std::cout << std::endl;
		}
		else // mamy dodane wierzcholki i jakies krawedzie - odpalamy algorytm sortowanai topologicznego
		{
			AdjacencyList Graph(n); // Pusta lista sasiedztw dla n wierzcholkow

			// wypelniam tablice sasiedztw odpowiednimi krawedziami grafu
			for (int i = 0; i < m; i++)
			{
				std::cin >> a;
				std::cin >> b;
				Graph.insertEdge(a, b);
			}
// ------------------ TYLKO DO TESTOW -------------------
/*			
			for (int i = 1; i <= n; i++) 
			{
				std::cout << i << ": ";
				Graph.showVertexNeighbors(i);
			}
*/
// --------> W tym miejscu mamy juz gotowa liste sasiedztw czyli zapisane wszystkie zaleznosci jakie zachodza pomiedzy zadaniami

			// Wypisuje na stdout wierzcholki zapisanego grafu posortowane topologicznie
			Graph.topologicalSort();
		}
	}
	return 0;
}