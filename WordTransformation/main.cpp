#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
    int testCases;
    cin >> testCases;
    
    for (int t = 0; t < testCases; t++)
    {
        string dict[200];
        int count = 0;
        
        string word;
        cin >> word;
        
        while (word != "*")
        {
            dict[count++] = word;
            cin >> word;      
        }
        
        int adj[count][count];
        
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                adj[i][j] = -1;
            }
        }
        
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if ((i != j) && (adj[i][j] == -1) && (dict[i].length() == dict[j].length()))
                {
                    bool diff = false;
                    for (int k = 0; k < dict[i].length(); k++)
                    {
                        if(dict[i][k] != dict[j][k])
                        {
                            if (diff)
                            {
                                diff = false;
                                break;
                            }
                            else
                            {
                                diff = true;
                            }
                        }
                    }
                    if (diff)
                    {
                        adj[i][j] = 1;
                        adj[j][i] = 1;
                    }
                    else
                    {
                        adj[i][j] = 0;
                        adj[j][i] = 0;
                    }
                }
            }
        }
        
        string query;
        getline(cin, query);
        getline(cin, query);
        
        while (!query.empty())
        {
            int src, dst;
            string srcText, dstText;
            int pos = query.find(" ");
            srcText = query.substr(0, pos);
            dstText = query.substr(pos+1);
            
            for (int i = 0; i < count; i++)
            {
                if (dict[i] == srcText)
                {
                    src = i;
                }
                if (dict[i] == dstText)
                {
                    dst = i;
                }
            }
            
            int k[count], p[count], d[count];
            queue<int> Q;

            for (int i = 0; i < count; i++)
            {
                k[i] = 0;
                p[i] = -1;
                d[i] = -1;
            }

            k[src] = 1;
            d[src] = 0;
            Q.push(src);

            while (!Q.empty())
            {
                int u = Q.front();
                Q.pop();
                for (int i = 1; i < count; i++)
                {
                    if (adj[u][i] > 0)
                    {
                        if (k[i] == 0)
                        {
                            k[i] = 1;
                            p[i] = u;
                            d[i] = d[u]+1;
                            Q.push(i);
                        }
                    }
                }
                k[u] = 2;
            }
            
            if (d[dst] > -1)
            {
                cout << srcText << " " << dstText << " " << d[dst] << endl;
            }
            
            getline(cin, query);
        }
        
        cout << endl;
    }

    return 0;
}

