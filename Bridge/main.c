#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int i, t[n][1000], min[n];
    for(i = 0; i < n; i++)
    {
        scanf("%c", NULL);
        int c;
        scanf("%d", &c);
        int j = 0;
        min[i] = 101;
        while (j < c)
        {
            scanf("%d", &t[i][j]);
            if (t[i][j] < min[i])
            {
                min[i] = t[i][j];
            }
            j++;
        }
        t[i][j] = 1001;
    }
    scanf("%c", NULL);
    
    for (i = 0; i < n; i++)
    {
        char found = 'f';
        char str[4096] = "";
        int time = 0;
        int k = 0;
        for (;;)
        {
            if (t[i][k] == min[i] && found == 'f')
            {
                k++;
                found = 't';
                continue;
            }
            if (t[i][k] == 1001)
            {
                break;
            }
            char tmp[10];
            sprintf(tmp, "%d %d\n", t[i][k], min[i]);
            strcat(str, tmp);
            time = time + t[i][k];
            if (t[i][k+1] != 1001)
            {
                char tmp2[10];
                sprintf(tmp2, "%d\n", min[i]);
                strcat(str, tmp2);
                time = time + min[i];
            }
            k++;
        }

        char tm[10];
        sprintf(tm, "%d", time);
        printf("%s\n%s\n", tm, str);
    }

    return 0;
}