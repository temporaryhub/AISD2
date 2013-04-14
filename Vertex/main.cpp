#include <stdio.h>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
    while (true)
    {
        int n;
        scanf("%d", &n);

        if (n == 0)
        {
            break;
        }

        int adj[n+1][n+1];
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                adj[i][j] = 0;
            }
        }

        while (true)
        {
            int e, a;
            scanf("%d", &e);

            if (e == 0)
            {
                break;
            }

            scanf("%d", &a);
            int p = 0;

            while (a != 0)
            {
                adj[e][p++] = a;
                scanf("%d", &a);
            }
        }

        int a;
        scanf("%d", &a);

        for (int i = 0; i < a; i++)
        {
            int m;
            scanf("%d", &m);
            
            int k[n+1], count = n;
            queue<int> v;
            for (int b = 0; b <= n; b++)
            {
                k[b] = 0;
            }            
            v.push(m);
            while(!v.empty())
            {
                int u = v.front();
                v.pop();
                for (int c = 0; c <= n; c++)
                {
                    if (adj[u][c] == 0)
                    {
                        break;
                    }
                    else
                    {
                        if (k[adj[u][c]] == 0)
                        {
                            k[adj[u][c]] = 1;
                            v.push(adj[u][c]);
                            count--;
                        }
                    }
                }
            }
            
            printf("%d", count);
            for (int t = 1; t <= n; t++)
            {
                if (k[t] == 0)
                {
                    printf(" %d", t);
                }
            }
            printf("\n");
        }
    }

    return 0;
}

