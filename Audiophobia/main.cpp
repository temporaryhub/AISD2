#include <stdio.h>
#include <stdlib.h>
#include <queue>
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

int main(int argc, char** argv)
{
    int c, s, q, cnum = 1;
    scanf("%d %d %d", &c, &s, &q);
    
    while ((c != 0) || (s != 0) || (q != 0))
    {
        printf("Case #%d\n", cnum);
        cnum++;
        
        int graf[s][3];
        int adj[c+1][c+1];
        bool wynik[s];
        
        for (int i = 1; i <= c; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                adj[i][j] = -1;
            }
        }

    
        for (int i = 0; i < s; i++)
        {
            wynik[i] = false;
            scanf("%d %d %d", &graf[i][0], &graf[i][1], &graf[i][2]);
        }
    
        qsort(graf, s, sizeof(*graf), comp);
        
        UF<int> *unionFind = new UF<int>(c+1);
    
        unionFind->Initialization();

        // Kruskall
        for (int i = 0; i < s; i++)
        {
            int a = unionFind->Find(graf[i][0]);
            int b = unionFind->Find(graf[i][1]);
            if (a != b)
            {
                unionFind->Union(a, b, a);
                adj[a][b] = graf[i][2];
                adj[b][a] = graf[i][2];
            }
        }
        
        for (int i = 0; i < q; i++)
        {
            int src, dst;
            scanf("%d %d", &src, &dst);
            
            // BFS
            int k[c+1], p[c+1], d[c+1];
            queue<int> Q;
            
            for (int j = 1; j <= c; j++)
            {
                k[j] = 0;
                p[j] = -1;
                d[j] = -1;
            }
            
            k[src] = 1;
            d[src] = 0;
            Q.push(src);
            
            while (!Q.empty())
            {
                int u = Q.front();
                Q.pop();
                for (int j = 1; j <= c; j++)
                {
                    if (adj[u][j] > -1)
                    {
                        if (k[j] == 0)
                        {
                            k[j] = 1;
                            p[j] = u;
                            d[j] = d[u]+1;
                            Q.push(j);
                        }
                    }
                }
                k[u] = 2;
            }
            
            if (d[dst] == -1)
            {
                printf("no path\n");
            }
            else
            {
                int child = dst;
                int max = 0;
                for (int j = 1; j <= c; j++)
                {
                    int parent = p[child];
                    if (adj[parent][child] > max)
                    {
                        max = adj[parent][child];
                    }
                    if (parent == src)
                    {
                        break;
                    }
                    else
                    {
                        child = parent;
                    }
                }
                printf("%d\n",max);
            }
        }
        
        printf("\n");
        scanf("%d %d %d", &c, &s, &q);
    }
    
    
    return 0;
}