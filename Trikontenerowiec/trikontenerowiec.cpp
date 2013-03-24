// trikontenerowiec.cpp
/*
	------------ Rozwiaznie zadania "Trikontenerowiec"---------------
	link do tresci: http://main.edu.pl/pl/user.phtml?op=showtask&task=e&con=PA2002
	------------------------ Paweł Stysz 2013 -----------------------
	----------- Zajęcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
*/

#include <iostream>

using namespace std;

struct Plyta
{
	int w;	// Przechowuje wartosc plyty
	int h;	// Przechowuje wysokosc plyty
};

int comp(const void *p1, const void *p2)
{
    const struct Plyta *plyta1 = (Plyta*)p1;    
	const struct Plyta *plyta2 = (Plyta*)p2;
	// W pierwszej kolejnoci porównuję według wartości płyty
	int roznica = plyta1->h - plyta2->h;
	// Jeżeli są różne to zwracam <0 jeżeli elem1 przed elem2, oraz >0 jeżeli elem2 przed elem1
	if (roznica) return roznica;
	// Jeżeli wartosc plyt jest rowna, porownuje wielkosci i wybieram mniejszą
	return plyta1->w - plyta2->w;
}

int main()
{
	int M, N;
	int optymalnaWartosc = 0; // Przechowuje optymalna wartosc ladunku
	int n = -1; // faktyczna ilosc elementow w tablicy (plyty za duze nie sa w ogole dodawane)
				// ...pierszy element w tablicy ma indeks 0 dlatego zaczynam od -1
	cin >> M;	// Zczytuje wielkosc ladowni
	cin >> N;	// Zczytuje ilosc plyt do zaladowania

	// Sprawdza czy dane wejsciowe sa w ogole poprawne
	if (N < 1 || M < 1)
	{
		std::cout << 0;
		return 0;
	}

	Plyta *tab = new Plyta[N];	// Tablica bedzie przechowywala wszystkie plyty do zaladowania

	// Wypelniam tablice plytami do zaladowania do kontenerowca
	for (int i = 0; i < N; i++)
	{
		Plyta *p = new Plyta();
		cin >> p->w;	// Zczytuje wartosc danej plyty
		cin >> p->h;	// Zczytuje wysokosc danej plyty
		if (p->h <= M)	// Jezeli plyta w ogole ma szanse sie zmiescic do ladowni...
			tab[++n] = *p;// ...zapisuje plyte do tablicy i zwiekszam faktyczna ilosc plyt mozliwych do zaladowania
		else			// W przeciwnym wypadku usuwam obiekt plyty
			delete p;
	}

	// Sortuje plyty rosnaco wedlug wielkosci, a jezeli sa takie same - rosnaco wedlug wartosci
	qsort(tab, n + 1, sizeof(Plyta), comp);

	// Wykonuj dopóki są jeszcze miejsca w ładowni oraz zostały jeszcze płyty do sprawdzenia
	while (M > 0 && n >= 0)
	{
		while (n >= 0 && tab[n].h > M ) // Najpierw sprawdzam czy n>=0 jezeli warunek prawdziwy to sprawdzam tab[n].h...
			--n;						// ...dzieki temu nie odwoluje sie do elementow o ujemnych indeksach

		// Jezeli n<0 to plyty sie skonczyly, mozna wyjsc z petli
		if (n < 0)
			break;

		optymalnaWartosc += tab[n].w; // Dodajemy wartosc zaladowanej plyty

		--M;	// Zmniesjzamy M bo wykorzystalismy juz jedno miejsce na plyte
	}

	cout << optymalnaWartosc;

	return 0;
}