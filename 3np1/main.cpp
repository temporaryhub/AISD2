#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int collatz(int n)
{
    int sum;
    if (n == 1)
    {
        return 1;
    }
    if (n % 2 == 0)
    {
        sum = collatz(n/2);
    }
    else
    {
        sum = collatz((3*n)+1);
    }
    return sum + 1;
}

int main()
{
    int data[1000000];
    string results[1000000];
    
    data[0] = 1;
    for (int i = 1; i < 1000000; i++)
    {
        data[i] = -1;
    }
    
    int w, s, x = 0;
    
    int res = scanf("%d %d", &w, &s);
    while (res == 2)
    {
        int max = -1;
        
        for (int i = w+1; i < s; i++)
        {
            int val;
            
            if (data[i+1] != -1)
            {
                val = data[i+1];
            }
            else
            {
                val = collatz(i);
                data[i+1] = val;
            }
            
            if (val > max)
            {
                max = val;
            }
        }
        
        // Trzeba zbuforowac i wypisac poza petla
        printf("%d %d %d\n", w, s, max);
        
        res = scanf("%d %d", &w, &s);
    }

    return 0;
}

