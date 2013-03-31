#include <iostream>
// Dolaczyc swoj UnionFind
#include "UnionFind.cpp"

using namespace std;

// Testowanie UnionFind na podstawie zadadnia nr 2 z zestawu 4.

int main()
{
    int pairs[12][2] = { {4,9}, {6,11}, {7, 9}, {2,7}, {1,8}, {9,10}, {4,11}, {2,10}, {4,6}, {7,10}, {1,5}, {9,4} };
    
    // Konstruktor dla UnionFind
    UF<int> *unionFind = new UF<int>(11);
    
    unionFind->Initialization();
    
    for (int i = 0; i < 12; i++)
    {
        int a = unionFind->Find(pairs[i][0]-1);
        int b = unionFind->Find(pairs[i][1]-1);
        if (a != b)
        {
            unionFind->Union(a, b, a);
        }
    }
    
    // Powinno wypisac:
    //Klasa abstrakcji nr 1: 1, 5, 8, 
    //Klasa abstrakcji nr 2: 2, 4, 6, 7, 9, 10, 11, 
    //Klasa abstrakcji nr 3: 3, 
    //Klasa abstrakcji nr 4: 
    //Klasa abstrakcji nr 5: 
    //Klasa abstrakcji nr 6: 
    //Klasa abstrakcji nr 7: 
    //Klasa abstrakcji nr 8: 
    //Klasa abstrakcji nr 9: 
    //Klasa abstrakcji nr 10: 
    //Klasa abstrakcji nr 11: 
    
    for (int i = 0; i < 11; i++)
    {
        cout << "Klasa abstrakcji nr " << i+1 << ": ";
        for (int j = 0; j < 11; j++)
        {
            if (unionFind->Find(j) == i) cout << j+1 << ", ";
        }
        cout << endl;
    }
    
    return 0;
}