// LinkNet.cpp
/*
	------------------ Rozwiaznie zadania "LinkNet"------------------
	link do tresci: http://main.edu.pl/pl/user.phtml?op=showtask&task=b&con=PA2002
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>

// Struktura przechowuje jedna transmisje z listy (moze byc nadawanie, lub odbieranie)
struct Transmission
{
	int connectionPort;		// Numer portu przylaczeniowego komputera
	int type;				// Rodzaj transmisji; -1 jezeli odbiera, +1 jezeli nadaje
	Transmission(): connectionPort(0), type(0){};
	Transmission(int _connectionPort, int _type): connectionPort(_connectionPort), type(_type){};
};

int comp(const void *p1, const void *p2)
{
    const struct Transmission *t1 = (Transmission*)p1;    
	const struct Transmission *t2 = (Transmission*)p2;
	// W pierwszej kolejnoci porownuje wedlug numeru portu (nizsze przed wiekszymi)
	int roznica = t1->connectionPort - t2->connectionPort;
	// Jeżeli są różne to zwracam <0 jeżeli elem1 przed elem2, oraz >0 jeżeli elem2 przed elem1
	if (roznica) return roznica;
	// Jeżeli porty sa takie same, ustawiam nadawanie przed odbieraniem
	return t2->type - t1->type;
}

int main() 
{
	int N;	// Ilosc polaczen (jedno polaczenie to dwa komputery)
	int doubleN; // przechowuje N * 2 liczone raz dla poprawy wydajnosci
	int minNrOfSteps = 0;	// minimalna ilosc taktow potrzebnych do przeslanai danych
	int nrOfActiveTrans = 0;// Ilosc aktywnych w danym momencie transmisji

	std::cin >> N;

	// N moze byc zerem, wtedy od razu zwracam zero i koniec programu
	if (!N)
	{
		std::cout << 0;
		return 0;
	}

	doubleN = 2 * N;

	// Tworze tablice dwa razy wieksza niz ilosc polaczen bo bede zapisywal osobno odbieranie...
	// ... a osobno wysylanie
	Transmission *tab = new Transmission[doubleN];

	// Zczytuje wszystkie transmisje z listy
	for (int i = 0; i < doubleN; i++)
	{
		int port;		// Tu bede przechowywal numer portu, do ktorego podpinam komp.
		int type = 1;	// typ transmisji (-1 odbior, +1 nadawanie)

		std::cin >> port;

		if (i % 2)		// Jezeli pobieram nieparzysty element tzn. ze mamy odbieranie bo sa na zmiane, od zera
			type = -1;

		Transmission *tr = new Transmission(port, type);
		tab[i] = *tr;
	}

	//Sortuje; zasada sortowania w opisie funkcji 'comp'
	qsort(tab, doubleN, sizeof(Transmission), comp);

	// Przegladam cala tablice transmisji
	for (int i = 0; i < doubleN; i++)
	{
		// Zadanie sprowadza sie do sprawdzenia, ile komp. chce nadawac rownoczesnie
		nrOfActiveTrans += tab[i].type;
		// Maksymalna ilosc komp. chcacych nadawac rownoczenie to nasza minimalna ilosc taktow
		if (nrOfActiveTrans > minNrOfSteps)
			minNrOfSteps = nrOfActiveTrans;
	}

	std::cout << minNrOfSteps;

	return 0;
}
