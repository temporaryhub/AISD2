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
    int graf[9][3] = { {1, 0, 1},
                       {3, 5, 1},
                       {5, 2, 1},
                       {3, 4, 4},
                       {5, 1, 5},
                       {0, 3, 1},
                       {0, 4, 5},
                       {4, 2, 2},
                       {2, 3, 3} };
    
//    graf[0][0] = 1; graf[0][1] = 0; graf[0][2] = 1;
//    graf[1][0] = 3; graf[1][1] = 5; graf[1][2] = 1;
//    graf[2][0] = 5; graf[2][1] = 2; graf[2][2] = 1;
//    graf[3][0] = 3; graf[3][1] = 4; graf[3][2] = 4;
//    graf[4][0] = 5; graf[4][1] = 1; graf[4][2] = 5;
//    graf[5][0] = 0; graf[5][1] = 3; graf[5][2] = 1;
//    graf[6][0] = 0; graf[6][1] = 4; graf[6][2] = 5;
//    graf[7][0] = 4; graf[7][1] = 2; graf[7][2] = 2;
//    graf[8][0] = 2; graf[8][1] = 3; graf[8][2] = 3;
    
    int wynik[9];
    
    qsort(graf, 9, sizeof(*graf), comp);
    
    UF<int> *unionFind = new UF<int>(6);
    
    unionFind->Initialization();
    
    int count = 0;
    
    for (int i = 0; i < 9; i++)
    {
        int a = unionFind->Find(graf[i][0]);
        int b = unionFind->Find(graf[i][1]);
        if (a != b)
        {
            unionFind->Union(a, b, a);
            wynik[count++] = i;
        }
    }
    
    // Prawidlowy wynik:
    //W grafie znajdzie sie krawedz nr 0 pomiedzy 1 a 0 o wadze 1
    //W grafie znajdzie sie krawedz nr 1 pomiedzy 3 a 5 o wadze 1
    //W grafie znajdzie sie krawedz nr 2 pomiedzy 5 a 2 o wadze 1
    //W grafie znajdzie sie krawedz nr 3 pomiedzy 0 a 3 o wadze 1
    //W grafie znajdzie sie krawedz nr 4 pomiedzy 4 a 2 o wadze 2

    
    for (int i = 0; i < count; i++)
    {
        cout << "W grafie znajdzie sie krawedz nr " << wynik[i] << " pomiedzy " << graf[wynik[i]][0] << " a " << graf[wynik[i]][1] << " o wadze " << graf[wynik[i]][2] << endl;
    }
    
    return 0;
}
