#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    char n[40], l1, l2;
    scanf("%s", &n);
    //printf("%s", n);
    //int l = atoi(n[39]);
    if (strlen(n) < 2)
    {
        l1 = n[strlen(n) - 1];
        l2 = '0';        
    }
    else
    {
        l1 = n[strlen(n) - 1];
        l2 = n[strlen(n) - 2];
    }
    int l = ((l2 - '0') * 10) + (l1 - '0');
    if (l == 0)
    {
        if (strlen(n) == 1)
        {
            printf("1");
        }
        else
        {
            printf("6");
        }
    }
    else if ((l % 4) == 0)
    {
        printf("6");
    }
    else if ((l % 4) == 1)
    {
        printf("2");
    }
    else if ((l % 4) == 2)
    {
        printf("4");
    }
    else if ((l % 4) == 3)
    {
        printf("8");
    }
    return 0;
}

