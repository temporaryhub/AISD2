// MyBST.h
/*
	---- W³asna implementacja drzewa BST na szablonach ver. 1.01 ----
	------------------------ Pawe³ Stysz 2013 -----------------------
	----------- Zajêcia: Algorytmy i Struktury Danych cz. 2 ---------
	-----------------------------------------------------------------
	--------------------------- UWAGA ------------------------------- 
	  Przy korzystaniu z w³asnych typów wymagane jest przeci¹¿enie
	      ...operatorów porównania w swojej klasie/strukturze!
	-----------------------------------------------------------------
*/

#ifndef _MYBST_H_
#define _MYBST_H_
#define NULL 0 // ¿eby korzystaæ z "NULL"

#include <queue> // Kolejka do implementacji przechodzenia drzewa poziomami
#include <stack> // Stos do implementacji przechodzenia drzewa iteracyjnie
#include <string>
 
template <typename T>
class MyBST
{

// ------------------------PRYWATNE ---------------------------- 
private:
	// Struktura przechowuje wartoœæ danego wêz³a, oraz wskaŸniki na lewe i prawe poddrzewo
	struct Node
	{
		T value;					// Wartoœæ przechowywana przez wêze³
		Node *left;					// WskaŸnik na lew¹ ga³¹Ÿ
		Node *right;				// WskaŸnik na praw¹ ga³¹Ÿ
		Node *parent;				// WskaŸnik na rodzica danego wêz³a
		Node():value(0), left(NULL), right(NULL), parent(NULL){};	 // Konstruktor pustego wêz³a
		Node(T x):value(x), left(NULL), right(NULL), parent(NULL){}; // Konstruktor wêz³a z wartoœci¹ x
	};

	Node *root;						// WskaŸnik na korzeñ drzewa (pierwszy element)
	int nrOfElements;				// Iloœæ elementów w drzewie
	void MyBSTinorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania inorder rekurencyjnie
	void MyBSTpreorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania preorder rekurencyjnie
	void MyBSTpostorder (Node* n);	// Pomocnicza funkcja dla przeszukiwania postorder rekurencyjnie
	int MyBSTnrOfLeaves (Node* n);  // Pomocnicza funkcja rekurencyjnie zliczaj¹ca iloœæ liœci w drzewie
	int MyBSTNrOfRank2nodes (Node* n); // Pomocnicza funkcja rekurencyjnie zliczaj¹ca ilosæ wêz³ów o poziomie 2
	int MyBSTNrOfRank1nodes (Node* n); // Pomocnicza funkcja rekurencyjnie zliczaj¹ca ilosæ wêz³ów o poziomie 1
	int MyBSTheight (Node* n);		// Pomocnicza funkcja rekurencyjnie badaj¹ca wysokoœæ drzewa
	T MyBSTmax (Node* n);			// Zwraca wartoœæ maksymaln¹ w drzewie, dla którego korzeniem jest wêze³ n
	Node* MyBSTmaxNode (Node* n);	// Zwraca adres wêz³a z najwiêkszym elementem w drzewie, dla któego korzeniem jest n
	Node* MyBSTminNode (Node* n);	// Zwraca adres wêz³a z najmniejszym elementem w drzewie, dla któego korzeniem jest n
	T MyBSTmin (Node* n);			// Zwraca wartoœæ minimaln¹ w drzewie, dla którego korzeniem jest wêze³ n
	Node* MyBSTsuccessor (Node* n);	// Zwraca wskaŸnik na nastêpnik danego wêz³a w drzewie, null je¿eli n jest liœciem
	Node* MyBSTpredecessor (Node* n); // Zwraca wskaŸnik na poprzednik danego wêz³a w drzewie, null je¿eli element jest ju¿ najmniejszy
	Node* MyBSTsearchNode (T x);	// Zwraca adres wêz³a z podan¹ wartoœci¹ x
	void MyBSTdraw (std::string sp, std::string sn, Node* n);	// Wykorzystuje odwrotny porz¹dek inorder do "narysowania" drzewa w oknie konsoli; wykorzystano...
									// ...algorytm ze strony: http://edu.i-lo.tarnow.pl/inf/alg/001_search/0112.php; autor: mgr Jerzy Wa³aszek 

// ----------------------- PUBLICZNE ---------------------------
public:
	MyBST(void);					// Konstruktor domyœlny, tworzy puste drzewo
	bool isEmpty();					// Zwraca true je¿eli drzewo jest puste, w przeciwnym razie - false
	bool insert(T x);				// Wstawia obiekt x w odpowiednie dla niego miejsce; false jezeli obiekt juz istnial i nie dodano
	bool remove(T x);				// Usuwa obiekt x z drzewa; true je¿eli uda³o siê usun¹æ, false je¿eli nie (nie by³o takiego wêz³a)
	bool contain(T x);				// Zwraca true je¿eli drzewo zawiera obiekt x
	int getHeight();				// Zwraca wysokoœæ drzewa, dla pustego drzewa zwraca -1
	int getNrOfLeaves();			// Zwraca iloœæ liœci drzewa
	int getNrOfElements();			// Zwraca iloœæ elementów w drzewie
	int getNrOfRank1nodes();		// Zwraca iloœæ wêz³ów o stopniu 1
	int getNrOfRank2nodes();		// Zwraca iloœæ wêz³ów o stopniu 2
	T getMax();						// Zwraca najwiêkszy element w drzewie
	T getMin();						// Zwraca najmniejszy element w drzewie
	T getSuccessor(T x);			// Zwraca wartoœæ nastêpnika elementu x
	T getPredecessor (T x);			// Zwraca wartoœæ poprzednika elementu x
	void preorderRecu();			// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci preorder (rekurencyjnie)
	void inorderRecu();				// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci inorder (rekurencyjnie)
	void postorderRecu();			// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci postorder (rekurencyjnie)
	void levelOrderIter();			// Wypisuje na stdout wartoœci kolejnych wêz³ów przechodz¹c poziomami (iteracyjnie)
	void preorderIter();			// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci preorder (iteracyjnie)
	void postorderIter();			// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci postorder (iteracyjnie)
	void inorderIter();				// Wypisuje na stdout wartoœci kolejnych wêz³ów w kolejnoœci inorder (iteracyjnie)
	void draw();					// Wykorzystuje odwrotny porz¹dek inorder do "narysowania" drzewa w oknie konsoli

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
	else if (n->left && !n->right) // Jedno (ale tylko jedno!) poddrzewo danego wêz³a pe³ne, drugie puste
		return 1 + MyBSTNrOfRank1nodes(n->left);
	else if (!n->left && n->right) 
		return 1 + MyBSTNrOfRank1nodes(n->right);
	else // Dany wêze³ nie jest stopnia pierwszego, ale sprawdŸ poddrzewa
		return MyBSTNrOfRank1nodes(n->right) + MyBSTNrOfRank1nodes(n->left);

	// Mo¿na chyba te¿ zastosowaæ xora, wtedy jest tylko jeden "else if" return 1 + MyBSTNrOfRank1nodes(n->right) + MyBSTNrOfRank1nodes(n->left)
}

template <typename T>
int MyBST<T>::MyBSTNrOfRank2nodes( Node* n )
{
	if (!n)
		return 0;
	else if (n->left && n->right) // Oba poddrzewa pe³ne == mamy wêze³ o poziomie 2
		return 1 + MyBSTNrOfRank2nodes(n->left) + MyBSTNrOfRank2nodes(n->right);
	else	// Dany wêze³ nie jest pe³ny, ale sprawd¿ poddrzewa
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
		return -1; // -1 poniewa¿ korzeñ jest zerowym wêz³em
	else
		return 1 + std::max(MyBSTheight(n->left), MyBSTheight(n->right));
}

template <typename T>
int MyBST<T>::MyBSTnrOfLeaves( Node* n )
{
	if (!n)
		return 0;
	else if (!n->left && !n->right) // Oba poddrzewa puste == mamy liœæ
		return 1;
	else
		return MyBSTnrOfLeaves(n->left) + MyBSTnrOfLeaves(n->right);

}

template <typename T>
void MyBST<T>::MyBSTpostorder( Node* n )
{
	if (n)	// Dopóki wêze³ nie jest pusty wywo³uj rekurencyjnie
	{
		MyBSTinorder(n->left);		
		MyBSTinorder(n->right);
		std::cout << n->value << " ";
	}
}

template <typename T>
void MyBST<T>::MyBSTpreorder( Node* n )
{
	if (n)	// Dopóki wêze³ nie jest pusty wywo³uj rekurencyjnie
	{
		std::cout << n->value << " ";
		MyBSTinorder(n->left);
		MyBSTinorder(n->right);

	}
}

template <typename T>
void MyBST<T>::MyBSTinorder( Node* n )
{
	if (n)	// Dopóki wêze³ nie jest pusty wywo³uj rekurencyjnie
	{
		MyBSTinorder(n->left);
		std::cout << n->value << " ";
		MyBSTinorder(n->right);
	}
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTpredecessor( Node* n )
{
	if (n->left) // istnieje lewe poddrzewo wiêc poprzednikiem jest element najwiêkszy z tego poddrzewa
		return MyBSTmaxNode(n->left);
	else if (n->right) // nie istnieje lewe poddrzewo wiêc poprzednikiem jest pierwszy wêze³-rodzic, dla którego n le¿y w prawym poddrzewie
	{
		Node* current = n;

		while (current != current->parent->right)
			current = current->parent;

		return current->parent;
	}
	else	// podany element jest najmniejszy, nie ma poprzedników
		return NULL;
}

template <typename T>
typename MyBST<T>::Node* MyBST<T>::MyBSTsuccessor( Node* n )
{
	if (n->right) // istnieje prawe poddrzewo wiêc nastêpnikiem jest element najmniejszy z tego poddrzewa
		return MyBSTminNode(n->right);
	else if (n->left) // nie istnieje prawe poddrzewo wiêc nastêpnikiem jest pierwszy wêze³-rodzic, dla którego n le¿y wlewym poddrzewie
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
	if (isEmpty())			// Je¿eli drzewo jest puste to od razu zwróæ false
		return false;

	Node* current = root;	// Zaczynamy sprawdzanie od korzenia

	while (current)		// Dopóki current nie jest pustym wêz³em (wtedy doszliœmy do koñca i nie znaleŸliœmy elementu)
	{
		if (x > current->value) // Dla wiêkszej wartoœci idziemy w prawo
			current = current->right;
		else if (x < current->value)	// ...dla mneijszej w lewo
			current = current->left;
		else					// W przeciwnym wypadku jesteœmy w³aœnie "na" szukanym elementcie
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
	Node* current = MyBSTsearchNode(x); // Znajduje wêzel przechowuj¹cy dan¹ wartoœæ
	if (!current)
		return NULL;	// Je¿eli nie istneije taki wêze³ to wyjdŸ zg³aszaj¹c NULL
	return MyBSTpredecessor(current)->value; // W przeciwnym frazie zwróæ wartoœæ poprzednika tego wêz³a
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
	if (isEmpty())			// Je¿eli drzewo jest puste to od razu zwróæ false
		return false;

	Node* current = root;	// Zaczynamy sprawdzanie od korzenia
	Node** parentBranch;	// Tu bêdê przechowywa³ adres ga³êzi rodzica, w któej znajduje siê current

	while (current)		// Dopóki current nie jest pustym wêz³em (wtedy doszliœmy do koñca i nie znaleŸliœmy elementu)
	{
		if (x > current->value) // Dla wiêkszej wartoœci idziemy w prawo
			current = current->right;
		else if (x < current->value)	// ...dla mneijszej w lewo
			current = current->left;
		else					// W przeciwnym wypadku jesteœmy w³aœnie "na" szukanym elementcie
			break;				// przerywamy, w current zapisany jest adres wêz³a do usuniêcia
	}

	if (!current)		// Wyszliœmy z pêtli ale nie znaleŸliœmy wêz³a; wychodzimy z metody i zwracamy false
		return false;

	if (current->parent)
	{
		if (current->parent->left == current) // Sprawdzam w której ga³êzi rodzica znajduje siê aktualny wêze³
			parentBranch = &current->parent->left;
		else 
			parentBranch = &current->parent->right;
	}
	else
		parentBranch = NULL;	// jesteœmy w korzeniu

	if (current->left && !current->right) // wêze³ ma jedno dziecko po lewej
	{
		if (parentBranch)
			*parentBranch = current->left;	// W³aœciwa ga³¹Ÿ rodzica usuwanego wêz³a ma wskazywaæ na jego lewego potomka
		else
			root = current->left;			// Je¿eli nei istnieje rodzic usuwanego wêz³a, to usuwamy korzeñ, trzeba wiêc wybraæ nowy
		current->left->parent = current->parent;
		delete current;
	}
	else if (!current->left && current->right) // wêze³ ma jedno dziecko po prawej
	{
		if (parentBranch)
			*parentBranch = current->right;	// W³aœciwa ga³¹Ÿ rodzica usuwanego wêz³a ma wskazywaæ na jego prawego potomka
		else
			root = current->right;			// Je¿eli nei istnieje rodzic usuwanego wêz³a, to usuwamy korzeñ, trzeba wiêc wybraæ nowy
		current->right->parent = current->parent;
		delete current;		
	}
	else if (current->left && current->right) // wêze³ ma dwoje "dzieci"
	{
		Node* currentSuccessor = MyBSTsuccessor(current);   //znajdujemy nastêpnik wêz³a, który chcemy usun¹æ
		Node* successorRight = currentSuccessor->right;		// wêze³ z prawej ga³êzi nastêpnika, wiadomo, ¿e lewej nie ma bo to wynika z def. nastêpnika
		Node** successorParentBranch;						// przechowuje adres ga³êzi rodzica pod któr¹ by³ wczeœniej nastêpnik

		if (currentSuccessor == currentSuccessor->parent->right)	// Szukam ga³êzi pod któr¹ bêdê podpina³ prawe poddrzewo aktualnego nastêpnika
			successorParentBranch = &currentSuccessor->parent->right;
		else
			successorParentBranch = &currentSuccessor->parent->left;

		current->value = currentSuccessor->value;			// kopiujê wartoœæ 
		*successorParentBranch = currentSuccessor->right;	// przepinam prawe poddrzewo nastêpnika
		if (successorRight)									// je¿eli nastêpnik nei by³ liœciem to zmieniam jeszcze rodzica dla prawego wêz³a
			successorRight->parent = currentSuccessor->parent;

		delete currentSuccessor;
	}
	else	// wêze³ jest liœciem
	{
		if (parentBranch)
			*parentBranch = NULL;	// W³aœciwa ga³¹Ÿ rodzica usuwanego wêz³a ma wskazywaæ na NULL
		else
			root = NULL;			// je¿eli nie istnieje rodzic to usunêliœmy korzeñ, który by³ liœciem, wiêc ostatni wêze³ => root jest pusty
		delete current;				// usuwamy dany wêze³
	}

	nrOfElements--;
	return true;
}

template <typename T>
bool MyBST<T>::isEmpty()
{
	return (root == NULL);	// Je¿eli korzeñ wskazuje na NULL tzn. ¿e nie ma ¿adnych elementów
}

template <typename T>
bool MyBST<T>::insert( T x )
{
	Node* newNode = new Node(x);	// Tworzymy nowy wêze³

	if (isEmpty())					// Je¿eli drzewo jest puste to nowy wêze³ jest korzeniem drzewa
	{
		root = newNode;
		nrOfElements++;
		return true;
	}
	else
	{
		Node* current = root;		// Wêze³, który aktualnie sprawdzamy, zaczynamy od korzenia
		while (current)				// Szukamy miejsca dla nowego wêz³a dopóki nie dojdziemy do w³aœciwego, pustego liœcia
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

		// Po znalezieniu w³aœciwego rodzica dla nowego wêz³a...
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

	while(!s.empty())	// Je¿eli stos jest pusty to sprawdziliœmy ca³e drzewo i koniec
	{
		current = s.top();	// Zczytuje pierwszy el. ze stosu i...
		s.pop();			//... usuwam go
		std::cout << current->value << " ";
		if (current->right)
			s.push(current->right);	// Wsadzam na stos prawy element
		if (current->left)
			s.push(current->left);	// Wsadzam na stos lewy element
		// W tym miejscu na stosie mam lewy i prawy el. (je¿eli istniej¹) wiêc na pocz¹tku...
		// ... pêtli zaczynam od nich
	}
	std::cout << std::endl;

}

template <typename T>
void MyBST<T>::postorderIter()
{
	std::stack<Node*> s;
	Node* current = NULL;	//aktualnie badany wêze³
	Node* prev = NULL;		// poprzednio badany wêze³ 
	s.push(root);

	while (!s.empty())		// dopóki na stosie s¹ jeszcze elementy, wykonuj:
	{
		current = s.top();
		
		// Uwaga - poni¿szy warunek zadzia³a, nawet je¿eli prev == NULL bo wtedy nie jest ju¿...
		// ... sprawdzany drugi i trzeci warunek, wiêc nie bêdzie b³êdu odwo³ania do nieistniej¹cego obj.
		if (!prev || prev->left == current || prev->right == current)
		{
			if (current->left)	// Je¿eli istnieje lewy wêze³ dodaj go na stos
				s.push(current->left);
			else if (current->right)	// Je¿eli istnieje prawy wêze³, dodaj go na stos
				s.push(current->right);
		}
		else if (current->left == prev && current->right) // Je¿eli poprzednio badano lewe dziecko aktualnego wêz³a i wêze³ ma prawe dziecko...
		{
			s.push(current->right);	//... wrzuæ je na stos (to nie brzmi dobrze ;) )
		}
		else
		{
			std::cout << current->value << " ";
			s.pop();	// wykonano wszystkie mo¿liwe operacje na ostatnim wêŸle, mo¿na go usun¹æ
		}
		prev = current;	// wêze³ ktory teraz zabadaliœmy staje siê poprzednim i pêtla rusza od nowa
	}
	std::cout << std::endl;
}

template <typename T>
void MyBST<T>::inorderIter()
{
	std::stack<Node*> s;
	Node* current = root->left;	// Zaczynamy od lewego elementu bo musimy zejœæ na dó³ lewej ga³êzi
	s.push(root);

	while(current || !s.empty())	// petla jest kontynuowana jezeli aktualny wezel nei jest pusty, lub stos zawiera jeszcze wezly
	{
		if (current)				// Jezeli istnieje dany wezel (czyli nie doszlismy do konca lewej galezi) to:
		{
			s.push(current);		// wrzucamy go na stos
			current = current->left;// przechodzimy nizej na lewo
		}
		else						// Zeszlismy na dol lewej galezi wiêc:
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