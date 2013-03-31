#include <stdlib.h>
#include <iostream>
#include "UnionFind.cpp"

using namespace std;

int comp (const void * a, const void * b)
{
    const unsigned int *av = reinterpret_cast<const unsigned int*>(a);
    const unsigned int *bv = reinterpret_cast<const unsigned int*>(b);
    if(av[2] > bv[2])
    {
        return 1;
    }
    else if(av[2] < bv[2])
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int graf[19][3] = { {10,  7,   9},
                        { 7, 10, 100},
                        {10,  7,  77},
                        { 5,  4,   3},
                        { 3,  9,   4},
                        { 3,  5,   6},
                        { 1,  4,   1},
                        {10,  1,   7},
                        { 8,  9,   8},
                        { 2,  9,   3},
                        {10,  5,   5},
                        { 8, 10,   6},
                        { 3,  1,   9},
                        { 5,  2,   7},
                        { 2,  3,   2},
                        { 7,  4,   8},
                        {10,  4,   1},
                        { 5,  6,   1},
                        {10,  6,   2} };
    
    int wynik[19];
    
    qsort(graf, 19, sizeof(*graf), comp);
    
    UF<int> *unionFind = new UF<int>(11);
    
    unionFind->Initialization();
    
    int count = 0;
    
    for (int i = 0; i < 19; i++)
    {
        int a = unionFind->Find(graf[i][0]);
        int b = unionFind->Find(graf[i][1]);
        cout << "Krawedz " << i << " pomiedzy " << graf[i][0] << " a " << graf[i][1] << " w zbiorze " << a << " oraz " << b << endl;
        if (a != b)
        {
            cout << "Roznica" << endl;
            unionFind->Union(a, b, a);
            wynik[count++] = i;
        }
    }
    
    for (int i = 0; i < count; i++)
    {
        cout << "W grafie znajdzie sie krawedz nr " << wynik[i] << " pomiedzy " << graf[wynik[i]][0] << " a " << graf[wynik[i]][1] << " o wadze " << graf[wynik[i]][2] << endl;
    }
    
    return 0;
}