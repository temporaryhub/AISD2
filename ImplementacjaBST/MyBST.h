// MyBST.h
/*
	---- W�asna implementacja drzewa BST na szablonach ver. 1.01 ----
	------------------------ Pawe� Stysz 2013 -----------------------
	----------- Zaj�cia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
	--------------------------- UWAGA ------------------------------- 
	  Przy korzystaniu z w�asnych typ�w wymagane jest przeci��enie
	      ...operator�w por�wnania w swojej klasie/strukturze!
	-----------------------------------------------------------------
*/

#ifndef _MYBST_H_
#define _MYBST_H_
#define NULL 0 // �eby korzysta� z "NULL"

#include <queue> // Kolejka do implementacji przechodzenia drzewa poziomami
#include <stack> // Stos do implementacji przechodzenia drzewa iteracyjnie
#include <string>
 
template <typename T>
class MyBST
{

// ------------------------PRYWATNE ---------------------------- 
private:
	// Struktura przechowuje warto�� danego w�z�a, oraz wska�niki na lewe i prawe poddrzewo
	struct Node
	{
		T value;					// Warto�� przechowywana przez w�ze�
		Node *left;					// Wska�nik na lew� ga���
		Node *right;				// Wska�nik na praw� ga���
		Node *parent;				// Wska�nik na rodzica danego w�z�a
		Node():value(0), left(NULL), right(NULL), parent(NULL){};	 // Konstruktor pustego w�z�a
		Node(T x):value(x), left(NULL), right(NULL), parent(NULL){}; // Konstruktor w�z�a z warto�ci� x
	};

	Node *root;						// Wska�nik na korze� drzewa (pierwszy element)
	int nrOfElements;				// Ilo�� element�w w drzewie
	void MyBSTinorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania inorder rekurencyjnie
	void MyBSTpreorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania preorder rekurencyjnie
	void MyBSTpostorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania postorder rekurencyjnie
	int MyBSTnrOfLeaves (Node* n);  // Pomocnicza funkcja rekurencyjnie zliczaj�ca ilo�� li�ci w drzewie
	int MyBSTNrOfRank2nodes (Node* n); // Pomocnicza funkcja rekurencyjnie zliczaj�ca ilos� w�z��w o poziomie 2
	int MyBSTNrOfRank1nodes (Node* n); // Pomocnicza funkcja rekurencyjnie zliczaj�ca ilos� w�z��w o poziomie 1
	int MyBSTheight (Node* n);		// Pomocnicza funkcja rekurencyjnie badaj�ca wysoko�� drzewa
	T MyBSTmax (Node* n);			// Zwraca warto�� maksymaln� w drzewie, dla kt�rego korzeniem jest w�ze� n
	Node* MyBSTmaxNode (Node* n);	// Zwraca adres w�z�a z najwi�kszym elementem w drzewie, dla kt�ego korzeniem jest n
	Node* MyBSTminNode (Node* n);	// Zwraca adres w�z�a z najmniejszym elementem w drzewie, dla kt�ego korzeniem jest n
	T MyBSTmin (Node* n);			// Zwraca warto�� minimaln� w drzewie, dla kt�rego korzeniem jest w�ze� n
	Node* MyBSTsuccessor (Node* n);	// Zwraca wska�nik na nast�pnik danego w�z�a w drzewie, null je�eli n jest li�ciem
	Node* MyBSTpredecessor (Node* n); // Zwraca wska�nik na poprzednik danego w�z�a w drzewie, null je�eli element jest ju� najmniejszy
	Node* MyBSTsearchNode (T x);	// Zwraca adres w�z�a z podan� warto�ci� x
	void MyBSTdraw (std::string sp, std::string sn, Node* n);	// Wykorzystuje odwrotny porz�dek inorder do "narysowania" drzewa w oknie konsoli; wykorzystano...
									// ...algorytm ze strony: http://edu.i-lo.tarnow.pl/inf/alg/001_search/0112.php; autor: mgr Jerzy Wa�aszek 

// ----------------------- PUBLICZNE ---------------------------
public:
	MyBST(void);					// Konstruktor domy�lny, tworzy puste drzewo
	bool isEmpty();					// Zwraca true je�eli drzewo jest puste, w przeciwnym razie - false
	bool insert(T x);				// Wstawia obiekt x w odpowiednie dla niego miejsce; false jezeli obiekt juz istnial i nie dodano
	bool remove(T x);				// Usuwa obiekt x z drzewa; true je�eli uda�o si� usun��, false je�eli nie (nie by�o takiego w�z�a)
	bool contain(T x);				// Zwraca true je�eli drzewo zawiera obiekt x
	int getHeight();				// Zwraca wysoko�� drzewa, dla pustego drzewa zwraca -1
	int getNrOfLeaves();			// Zwraca ilo�� li�ci drzewa
	int getNrOfElements();			// Zwraca ilo�� element�w w drzewie
	int getNrOfRank1nodes();		// Zwraca ilo�� w�z��w o stopniu 1
	int getNrOfRank2nodes();		// Zwraca ilo�� w�z��w o stopniu 2
	T getMax();						// Zwraca najwi�kszy element w drzewie
	T getMin();						// Zwraca najmniejszy element w drzewie
	T getSuccessor(T x);			// Zwraca warto�� nast�pnika elementu x
	T getPredecessor (T x);			// Zwraca warto�� poprzednika elementu x
	void preorderRecu();			// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci preorder (rekurencyjnie)
	void inorderRecu();				// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci inorder (rekurencyjnie)
	void postorderRecu();			// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci postorder (rekurencyjnie)
	void levelOrderIter();			// Wypisuje na stdout warto�ci kolejnych w�z��w przechodz�c poziomami (iteracyjnie)
	void preorderIter();			// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci preorder (iteracyjnie)
	void postorderIter();			// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci postorder (iteracyjnie)
	void inorderIter();				// Wypisuje na stdout warto�ci kolejnych w�z��w w kolejno�ci inorder (iteracyjnie)
	void draw();					// Wykorzystuje odwrotny porz�dek inorder do "narysowania" drzewa w oknie konsoli

	~MyBST(void);				// Destruktor
};

// --------------------------- KONSTRUKTOR --------------------------------

template <typename T>
MyBST<T>::MyBST( void )
{
	root = NULL;
	nrOfElements = 0;
}

// ------------------------- METODY PRYWATNE ------------------------------

template <typename T>
int MyBST<T>::MyBSTNrOfRank1nodes( Node* n )
{
	if (!n)
		return 0;
	else if (n->left && !n->right) // Jedno (ale tylko jedno!) poddrzewo danego w�z�a pe�ne, drugie puste
		return 1 + MyBSTNrOfRank1nodes(n->left);
	else if (!n->left && n->right) 
		return 1 + MyBSTNrOfRank1nodes(n->right);
	else // Dany w�ze� nie jest stopnia pierwszego, ale sprawd� poddrzewa
		return MyBSTNrOfRank1nodes(n->right) + MyBSTNrOfRank1nodes(n->left);

	// Mo�na chyba te� zastosowa� xora, wtedy jest tylko jeden "else if" return 1 + MyBSTNrOfRank1nodes(n->right) + MyBSTNrOfRank1nodes(n->left)
}

template <typename T>
int MyBST<T>::MyBSTNrOfRank2nodes( Node* n )
{
	if (!n)
		return 0;
	else if (n->left && n->right) // Oba poddrzewa pe�ne == mamy w�ze� o poziomie 2
		return 1 + MyBSTNrOfRank2nodes(n->left) + MyBSTNrOfRank2nodes(n->right);
	else	// Dany w�ze� nie jest pe�ny, ale sprawd� poddrzewa
		return MyBSTNrOfRank2nodes(n->left) + MyBSTNrOfRank2nodes(n->right);
}

template <typename T>
T MyBST<T>::MyBSTmin( Node *n )
{
	if (isEmpty())
		return 0;

	Node* current = n;

	while (current->left)
		current = current->left;

	return current->value;
}

template <typename T>
T MyBST<T>::MyBSTmax( Node* n )
{
	if (isEmpty())
		return 0;

	Node* current = n;

	while (current->right)
		current = current->right;

	return current->value;
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTminNode( Node* n )
{
	if (isEmpty())
		return NULL;

	Node* current = n;

	while (current->left)
		current = current->left;

	return current;
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTmaxNode( Node* n )
{
	if (isEmpty())
		return 0;

	Node* current = n;

	while (current->right)
		current = current->right;

	return current;
}

template <typename T>
int MyBST<T>::MyBSTheight( Node* n )
{
	if (!n)
		return -1; // -1 poniewa� korze� jest zerowym w�z�em
	else
		return 1 + std::max(MyBSTheight(n->left), MyBSTheight(n->right));
}

template <typename T>
int MyBST<T>::MyBSTnrOfLeaves( Node* n )
{
	if (!n)
		return 0;
	else if (!n->left && !n->right) // Oba poddrzewa puste == mamy li��
		return 1;
	else
		return MyBSTnrOfLeaves(n->left) + MyBSTnrOfLeaves(n->right);

}

template <typename T>
void MyBST<T>::MyBSTpostorder( Node* n )
{
	if (n)	// Dop�ki w�ze� nie jest pusty wywo�uj rekurencyjnie
	{
		MyBSTinorder(n->left);		
		MyBSTinorder(n->right);
		std::cout << n->value << " ";
	}
}

template <typename T>
void MyBST<T>::MyBSTpreorder( Node* n )
{
	if (n)	// Dop�ki w�ze� nie jest pusty wywo�uj rekurencyjnie
	{
		std::cout << n->value << " ";
		MyBSTinorder(n->left);
		MyBSTinorder(n->right);

	}
}

template <typename T>
void MyBST<T>::MyBSTinorder( Node* n )
{
	if (n)	// Dop�ki w�ze� nie jest pusty wywo�uj rekurencyjnie
	{
		MyBSTinorder(n->left);
		std::cout << n->value << " ";
		MyBSTinorder(n->right);
	}
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTpredecessor( Node* n )
{
	if (n->left) // istnieje lewe poddrzewo wi�c poprzednikiem jest element najwi�kszy z tego poddrzewa
		return MyBSTmaxNode(n->left);
	else if (n->right) // nie istnieje lewe poddrzewo wi�c poprzednikiem jest pierwszy w�ze�-rodzic, dla kt�rego n le�y w prawym poddrzewie
	{
		Node* current = n;

		while (current != current->parent->right)
			current = current->parent;

		return current->parent;
	}
	else	// podany element jest najmniejszy, nie ma poprzednik�w
		return NULL;
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTsuccessor( Node* n )
{
	if (n->right) // istnieje prawe poddrzewo wi�c nast�pnikiem jest element najmniejszy z tego poddrzewa
		return MyBSTminNode(n->right);
	else if (n->left) // nie istnieje prawe poddrzewo wi�c nast�pnikiem jest pierwszy w�ze�-rodzic, dla kt�rego n le�y wlewym poddrzewie
	{
		Node* current = n;

		while (current != current->parent->left)
			current = current->parent;

		return current->parent;
	}
	else	// podany element jest najwiekszy, nie ma nastepnikow
		return NULL;
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTsearchNode( T x )
{
	if (isEmpty())			// Je�eli drzewo jest puste to od razu zwr�� false
		return false;

	Node* current = root;	// Zaczynamy sprawdzanie od korzenia

	while (current)		// Dop�ki current nie jest pustym w�z�em (wtedy doszli�my do ko�ca i nie znale�li�my elementu)
	{
		if (x > current->value) // Dla wi�kszej warto�ci idziemy w prawo
			current = current->right;
		else if (x < current->value)	// ...dla mneijszej w lewo
			current = current->left;
		else					// W przeciwnym wypadku jeste�my w�a�nie "na" szukanym elementcie
			return current;
	}

	return NULL;
}

template <typename T>
void MyBST<T>::MyBSTdraw(std::string sp, std::string sn, Node* n)
{
	std::string cr, cl, cp, s;
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;

	if(n)
	{
		s = sp;
		if(sn == cr)
			s[s.length() - 2] = ' ';
		MyBSTdraw(s + cp, cr, n->right);

		s = s.substr(0,sp.length()-2);
		cout << s << sn << n->value << endl;

		s = sp;
		if(sn == cl)
			s[s.length() - 2] = ' ';
		MyBSTdraw(s + cp, cl, n->left);
	}

}

// ------------------------- METODY PUBLICZNE -----------------------------

template <typename T>
void MyBST<T>::postorderRecu()
{
	MyBSTpostorder(root);
	std::cout << endl;
}

template <typename T>
void MyBST<T>::inorderRecu()
{
	MyBSTinorder(root);
	std::cout << endl;
}

template <typename T>
void MyBST<T>::preorderRecu()
{
	MyBSTpreorder(root);
	std::cout << endl;
}

template <typename T>
int MyBST<T>::getNrOfRank2nodes()
{
	if (isEmpty())
		return 0;
	else
		return MyBSTNrOfRank2nodes(root);
}

template <typename T>
int MyBST<T>::getNrOfRank1nodes()
{
	if (isEmpty())
		return 0;
	else
		return MyBSTNrOfRank1nodes(root);
}

template <typename T>
int MyBST<T>::getNrOfElements()
{
	return nrOfElements;
}

template <typename T>
int MyBST<T>::getNrOfLeaves()
{
	if (isEmpty())
		return 0;
	else
		return MyBSTnrOfLeaves(root);
}

template <typename T>
int MyBST<T>::getHeight()
{
	return MyBSTheight(root);
}

template <typename T>
T MyBST<T>::getMin()
{
	return MyBSTmin(root);
}

template <typename T>
T MyBST<T>::getMax()
{
	return MyBSTmax(root);
}

template <typename T>
T MyBST<T>::getPredecessor( T x )
{
	Node* current = MyBSTsearchNode(x); // Znajduje w�zel przechowuj�cy dan� warto��
	if (!current)
		return NULL;	// Je�eli nie istneije taki w�ze� to wyjd� zg�aszaj�c NULL
	return MyBSTpredecessor(current)->value; // W przeciwnym frazie zwr�� warto�� poprzednika tego w�z�a
}

template <typename T>
T MyBST<T>::getSuccessor( T x )
{
	Node* current = MyBSTsearchNode(x);
	if (!current)
		return NULL;
	return MyBSTsuccessor(current)->value;
}

template <typename T>
bool MyBST<T>::contain( T x )
{
	if (MyBSTsearchNode(x))
		return true;
	return false;
}

template <typename T>
bool MyBST<T>::remove( T x )
{
	if (isEmpty())			// Je�eli drzewo jest puste to od razu zwr�� false
		return false;

	Node* current = root;	// Zaczynamy sprawdzanie od korzenia
	Node** parentBranch;	// Tu b�d� przechowywa� adres ga��zi rodzica, w kt�ej znajduje si� current

	while (current)		// Dop�ki current nie jest pustym w�z�em (wtedy doszli�my do ko�ca i nie znale�li�my elementu)
	{
		if (x > current->value) // Dla wi�kszej warto�ci idziemy w prawo
			current = current->right;
		else if (x < current->value)	// ...dla mneijszej w lewo
			current = current->left;
		else					// W przeciwnym wypadku jeste�my w�a�nie "na" szukanym elementcie
			break;				// przerywamy, w current zapisany jest adres w�z�a do usuni�cia
	}

	if (!current)		// Wyszli�my z p�tli ale nie znale�li�my w�z�a; wychodzimy z metody i zwracamy false
		return false;

	if (current->parent)
	{
		if (current->parent->left == current) // Sprawdzam w kt�rej ga��zi rodzica znajduje si� aktualny w�ze�
			parentBranch = &current->parent->left;
		else 
			parentBranch = &current->parent->right;
	}
	else
		parentBranch = NULL;	// jeste�my w korzeniu

	if (current->left && !current->right) // w�ze� ma jedno dziecko po lewej
	{
		if (parentBranch)
			*parentBranch = current->left;	// W�a�ciwa ga��� rodzica usuwanego w�z�a ma wskazywa� na jego lewego potomka
		else
			root = current->left;			// Je�eli nei istnieje rodzic usuwanego w�z�a, to usuwamy korze�, trzeba wi�c wybra� nowy
		current->left->parent = current->parent;
		delete current;
	}
	else if (!current->left && current->right) // w�ze� ma jedno dziecko po prawej
	{
		if (parentBranch)
			*parentBranch = current->right;	// W�a�ciwa ga��� rodzica usuwanego w�z�a ma wskazywa� na jego prawego potomka
		else
			root = current->right;			// Je�eli nei istnieje rodzic usuwanego w�z�a, to usuwamy korze�, trzeba wi�c wybra� nowy
		current->right->parent = current->parent;
		delete current;		
	}
	else if (current->left && current->right) // w�ze� ma dwoje "dzieci"
	{
		Node* currentSuccessor = MyBSTsuccessor(current);   //znajdujemy nast�pnik w�z�a, kt�ry chcemy usun��
		Node* successorRight = currentSuccessor->right;		// w�ze� z prawej ga��zi nast�pnika, wiadomo, �e lewej nie ma bo to wynika z def. nast�pnika
		Node** successorParentBranch;						// przechowuje adres ga��zi rodzica pod kt�r� by� wcze�niej nast�pnik

		if (currentSuccessor == currentSuccessor->parent->right)	// Szukam ga��zi pod kt�r� b�d� podpina� prawe poddrzewo aktualnego nast�pnika
			successorParentBranch = &currentSuccessor->parent->right;
		else
			successorParentBranch = &currentSuccessor->parent->left;

		current->value = currentSuccessor->value;			// kopiuj� warto�� 
		*successorParentBranch = currentSuccessor->right;	// przepinam prawe poddrzewo nast�pnika
		if (successorRight)									// je�eli nast�pnik nei by� li�ciem to zmieniam jeszcze rodzica dla prawego w�z�a
			successorRight->parent = currentSuccessor->parent;

		delete currentSuccessor;
	}
	else	// w�ze� jest li�ciem
	{
		if (parentBranch)
			*parentBranch = NULL;	// W�a�ciwa ga��� rodzica usuwanego w�z�a ma wskazywa� na NULL
		else
			root = NULL;			// je�eli nie istnieje rodzic to usun�li�my korze�, kt�ry by� li�ciem, wi�c ostatni w�ze� => root jest pusty
		delete current;				// usuwamy dany w�ze�
	}

	nrOfElements--;
	return true;
}

template <typename T>
bool MyBST<T>::isEmpty()
{
	return (root == NULL);	// Je�eli korze� wskazuje na NULL tzn. �e nie ma �adnych element�w
}

template <typename T>
bool MyBST<T>::insert( T x )
{
	Node* newNode = new Node(x);	// Tworzymy nowy w�ze�

	if (isEmpty())					// Je�eli drzewo jest puste to nowy w�ze� jest korzeniem drzewa
	{
		root = newNode;
		nrOfElements++;
		return true;
	}
	else
	{
		Node* current = root;		// W�ze�, kt�ry aktualnie sprawdzamy, zaczynamy od korzenia
		while (current)				// Szukamy miejsca dla nowego w�z�a dop�ki nie dojdziemy do w�a�ciwego, pustego li�cia
		{
			newNode->parent = current;
			if (newNode->value > current->value)
				current = current->right;
			else if (newNode->value < current->value)
				current = current->left;
			else
			{
				delete newNode;
				return false;	// element juz istnieje
			}
		}

		// Po znalezieniu w�a�ciwego rodzica dla nowego w�z�a...
		if (newNode->value < newNode->parent->value)
			newNode->parent->left = newNode;	// ...wstawiamy po odpowiedniej stronie.
		else
			newNode->parent->right = newNode;

		nrOfElements++;
	}
	
}

template <typename T>
void MyBST<T>::levelOrderIter()
{
	if (!isEmpty())
	{
		std::queue<MyBST::Node*> q;
		Node* current = NULL;
		q.push(root);

		while(!q.empty())
		{
			current = q.front();

			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);

			std::cout << current->value << " ";
			q.pop();
		}
		std::cout << endl;
	}
}

template <typename T>
void MyBST<T>::preorderIter()
{
	std::stack<MyBST::Node*> s;
	Node* current = NULL;
	s.push(root); // Zaczynamy od korzenia

	while(!s.empty())	// Je�eli stos jest pusty to sprawdzili�my ca�e drzewo i koniec
	{
		current = s.top();	// Zczytuje pierwszy el. ze stosu i...
		s.pop();			//... usuwam go
		std::cout << current->value << " ";
		if (current->right)
			s.push(current->right);	// Wsadzam na stos prawy element
		if (current->left)
			s.push(current->left);	// Wsadzam na stos lewy element
		// W tym miejscu na stosie mam lewy i prawy el. (je�eli istniej�) wi�c na pocz�tku...
		// ... p�tli zaczynam od nich
	}
	std::cout << std::endl;

}

template <typename T>
void MyBST<T>::postorderIter()
{
	std::stack<Node*> s;
	Node* current = NULL;	//aktualnie badany w�ze�
	Node* prev = NULL;		// poprzednio badany w�ze� 
	s.push(root);

	while (!s.empty())		// dop�ki na stosie s� jeszcze elementy, wykonuj:
	{
		current = s.top();
		
		// Uwaga - poni�szy warunek zadzia�a, nawet je�eli prev == NULL bo wtedy nie jest ju�...
		// ... sprawdzany drugi i trzeci warunek, wi�c nie b�dzie b��du odwo�ania do nieistniej�cego obj.
		if (!prev || prev->left == current || prev->right == current)
		{
			if (current->left)	// Je�eli istnieje lewy w�ze� dodaj go na stos
				s.push(current->left);
			else if (current->right)	// Je�eli istnieje prawy w�ze�, dodaj go na stos
				s.push(current->right);
		}
		else if (current->left == prev && current->right) // Je�eli poprzednio badano lewe dziecko aktualnego w�z�a i w�ze� ma prawe dziecko...
		{
			s.push(current->right);	//... wrzu� je na stos (to nie brzmi dobrze ;) )
		}
		else
		{
			std::cout << current->value << " ";
			s.pop();	// wykonano wszystkie mo�liwe operacje na ostatnim w�le, mo�na go usun��
		}
		prev = current;	// w�ze� ktory teraz zabadali�my staje si� poprzednim i p�tla rusza od nowa
	}
	std::cout << std::endl;
}

template <typename T>
void MyBST<T>::inorderIter()
{
	std::stack<Node*> s;
	Node* current = root->left;	// Zaczynamy od lewego elementu bo musimy zej�� na d� lewej ga��zi
	s.push(root);

	while(current || !s.empty())	// petla jest kontynuowana jezeli aktualny wezel nei jest pusty, lub stos zawiera jeszcze wezly
	{
		if (current)				// Jezeli istnieje dany wezel (czyli nie doszlismy do konca lewej galezi) to:
		{
			s.push(current);		// wrzucamy go na stos
			current = current->left;// przechodzimy nizej na lewo
		}
		else						// Zeszlismy na dol lewej galezi wi�c:
		{
			current = s.top();		// zczytujemy ten element
			s.pop();				// usuwamy go ze stosu
			std::cout << current->value << " "; // Wypisujemy na ekran
			current = current->right; // bierzemy sie za jego prawe drzewo, a jezeli nie istnieje to bierzemy kolejny element ze stosu...
		}							//...ktory w tym wypadku bedzie jego rodzicem czyli wszystko sie zgadza: lewy, rodzic, prawy
	}
	std::cout << std::endl;
}

template <typename T>
void MyBST<T>::draw()
{
	MyBSTdraw("", "", root);
	std::cout << std::endl;
}

// --------------------------- DESTRUKTOR --------------------------------

template <typename T>
MyBST<T>::~MyBST( void )
{
	delete root; // Czy to wystarczy??
}

#endif