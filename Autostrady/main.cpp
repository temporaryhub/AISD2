#include <stdlib.h>
#include <stdio.h>
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
    int n, m;
    scanf("%d %d", &n, &m);
    
    int graf[m][3];
    
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &graf[i][0], &graf[i][1], &graf[i][2]);
    }
    
    int wynik;
    
    qsort(graf, m, sizeof(*graf), comp);
    
    UF<int> *unionFind = new UF<int>(n+1);
    
    unionFind->Initialization();
    
    int count = 0;
    
    for (int i = 0; i < m; i++)
    {
        int a = unionFind->Find(graf[i][0]);
        int b = unionFind->Find(graf[i][1]);
        if (a != b)
        {
            unionFind->Union(a, b, a);
            wynik = graf[i][2];
        }
    }
    
    printf("%d", wynik);
    
    return 0;
}