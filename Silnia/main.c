#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    if ((n == 0) || (n == 1))
    {
        printf("1");
    }
    else if (n == 2)
    {
        printf("2");
    }
    else if (n == 3)
    {
        printf("6");
    }
    else if (n == 4)
    {
        printf("4");
    }
    else
    {
        printf("0");
    }

    return 0;
}

