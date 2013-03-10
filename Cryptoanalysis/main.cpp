#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int comp (const void * a, const void * b)
{
    const unsigned int *av = reinterpret_cast<const unsigned int*>(a);
    const unsigned int *bv = reinterpret_cast<const unsigned int*>(b);
    if(av[1] > bv[1])
    {
        return -1;
    }
    else if(av[1] < bv[1])
    {
        return 1;
    }
    else
    {
        if (av[0] > bv[0])
        {
            return 1;
        }
        else if (av[0] < bv[0])
        {
            return -1;
        }
        return 0;
    }
}

int main()
{
    int n;
    cin >> n;
    int val[25][2];
    
    for (int i = 0; i < 25; i++)
    {
        val[i][0] = (char)(i+65);
        val[i][1] = 0;
    }
    
    for (int i = 0; i <= n; i++)
    {
        string s;
        getline(cin, s);
        for (int j = 0; j < s.length(); j++)
        {
            int c = (int)s[j];
            if (c >= 97 && c <= 122)
            {
                c = c - 32;
            }
            if (c >= 65 && c <= 90)
            {
                val[c-65][1]++;
            }
        }
    }
    
    qsort(val, 25, sizeof(*val), comp);
    
    for (int i = 0; i < 25; i++)
    {
        if (val[i][1] > 0)
        {
            cout << (char)val[i][0] << " " << val[i][1] << endl;
        }
    }

    return 0;
}
