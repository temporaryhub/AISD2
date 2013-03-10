#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp ( const void *pa, const void *pb ) {
    const int (*a)[2] = pa;
    const int (*b)[2] = pb;
    if ( (*a)[2] < (*b)[2] ) return -1;
    if ( (*a)[2] > (*b)[2] ) return +1;
    if ( (*a)[2] == (*b)[2] )
    {
        if ( (*a)[0] < (*b)[0] ) return -1;
        if ( (*a)[0] > (*b)[0] ) return +1;
    }
    return 0;
}

int main()
{
    int n, i;
    
    scanf("%d", &n);
    
    //char l[n][255];
    int wagi[n][3];
    int w[n];
    
    for (i = 0; i < n; i++)
    {
        int l, m;
        scanf("%d %d", &l, &m);
        wagi[i][0] = l;
        wagi[i][1] = m;
        switch (m)
        {
            case 1:
                wagi[i][2] = l * 512;
                w[i] = l * 512;
                break;
            case 2:
                wagi[i][2] = l * 256;
                w[i] = l * 256;
                break;
            case 3:
                wagi[i][2] = l * 128;
                w[i] = l * 128;
                break;
            case 4:
                wagi[i][2] = l * 64;
                w[i] = l * 64;
                break;
            case 5:
                wagi[i][2] = l * 32;
                w[i] = l * 32;
                break;
            case 6:
                wagi[i][2] = l * 16;
                w[i] = l * 16;
                break;
            case 7:
                wagi[i][2] = l * 8;
                w[i] = l * 8;
                break;
            case 8:
                wagi[i][2] = l * 4;
                w[i] = l * 4;
                break;
            case 9:
                wagi[i][2] = l * 2;
                w[i] = l * 2;
                break;
            case 10:
                wagi[i][2] = l;
                w[i] = l;
                break;
        }
    }
    
    qsort(wagi, n, sizeof(*wagi), comp);
    
    for (i = 0; i < n; i++)
    {
        printf("%d %d\n", wagi[i][0], wagi[i][1]);
    }
    
    return 0;
}

