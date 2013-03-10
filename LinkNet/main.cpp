#include <stdio.h>
#include <stdlib.h>

using namespace std;

int comp (const void * a, const void * b)
{
    const unsigned int *av = reinterpret_cast<const unsigned int*>(a);
    const unsigned int *bv = reinterpret_cast<const unsigned int*>(b);
    
//    int a_diff = (av[1] - av[0]);
//    int b_diff = (bv[1] - bv[0]);
//    
//    if(a_diff > b_diff)
//    {
//        return 1;
//    }
//    else if(a_diff < b_diff)
//    {
//        return -1;
//    }
    if (av[0] > bv[0])
    {
        return 1;
    }
    else if (av[0] < bv[0])
    {
        return -1;
    }
//    else if (av[1] > bv[1])
//    {
//        return -1;
//    }
//    else if (av[1] < bv[1])
//    {
//        return 1;
//    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int v[n][2];
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &v[i][0], &v[i][1]);
    }
    
    qsort(v, n, sizeof(*v), comp);
    
    int counter = 0;
    
    for (int i = 0; i < n; i++)
    {
        //printf("%d: %d %d\n", i, v[i][0], v[i][1]);
    }
    
    for (int i = 0; i < n; i++)
    {
        if (v[i][0] == -1)
        {
            //printf("Value no. %d is omitted (outer)\n", i);
            continue;
        }
        int k = 1, s[n];
        s[0] = i;
        for (int j = 0; j < n; j++)
        {
            if ((v[j][0] == -1) || (i == j))
            {
                if (v[j][0] == -1)
                {
                    //printf("Value no. %d is omitted (inner)\n", j);
                }
                continue;
            }
            bool t = true;
            for (int l = 0; l < k; l++)
            {
                //printf("Matching %d and %d\n", j, s[l]);
                if ((v[j][0] == v[s[l]][0] || v[j][1] == v[s[l]][1]) ||
                    (v[j][0] == v[s[l]][1] || v[j][1] == v[s[l]][0]) ||
                    (v[j][0] <= v[s[l]][0] && v[j][1] >= v[s[l]][1]) ||
                    (v[j][1] < v[s[l]][1] && v[j][1] > v[s[l]][0]) ||
                    (v[j][0] > v[s[l]][0] && v[j][0] < v[s[l]][1]))
                {
                    //printf("Value no. %d intersects with %d\n", j, s[l]);
                    t = false;
                    break;
                }
            }
            if (t)
            {
                //printf("No intersections found for %d.\n", j);
                s[k] = j;
                k++;
            }
        }
        for (int l = 0; l < k; l++)
        {
            //printf("Reseting %d.\n", s[l]);
            v[s[l]][0] = -1;
        }
        counter++;
        //printf("Counter raised to %d\n", counter);
    }
    
    printf("%d", counter);
    
    return 0;
}

