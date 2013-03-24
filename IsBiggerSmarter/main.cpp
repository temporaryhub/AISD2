#include <stdlib.h>
#include <stdio.h>

using namespace std;

int comp (const void * a, const void * b)
{
    const unsigned int *av = reinterpret_cast<const unsigned int*>(a);
    const unsigned int *bv = reinterpret_cast<const unsigned int*>(b);
    if(av[0] > bv[0])
    {
        return 1;
    }
    else if(av[0] < bv[0])
    {
        return -1;
    }
    else
    {
        if (av[1] > bv[1])
        {
            return -1;
        }
        else if (av[1] < bv[1])
        {
            return 1;
        }
        return 0;
    }
}

int main()
{
    int data[1000][3];
    int count = 0, w, s;
    
    int res = scanf("%d %d", &w, &s);
    while (res == 2)
    {
        data[count][0] = w;
        data[count][1] = s;
        data[count][2] = count+1;
        count++;
        res = scanf("%d %d", &w, &s);
    }
    
    qsort(data, count, sizeof(*data), comp);
    
    int n = 0, x = 1, i = 0;
    int r[1000];
    
    // Tutaj musi być jakaś pętla, która coś robi, ale nie wymyśliłem żadnej, która działa
    
    printf("%d\n", n);
    
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", r[i]);
    }
    
    return 0;
}

