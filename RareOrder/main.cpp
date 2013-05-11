#include <iostream>
#include <stack>

using namespace std;

void DFS(int u, bool adj[26][26], int k[26], stack<int>& s)
{
    k[u] = 1;
    for (int i = 0; i < 26; i++)
    {
        if (adj[u][i])
        {
            if (k[i] == 0)
            {
                DFS(i, adj, k, s);
            }
        }
    }
    k[u] = 2;
    s.push(u);
}

stack<int> DFS_Directed(bool adj[26][26])
{
    stack<int> s;
    int k[26];
    for (int i = 0; i < 26; i++)
    {
        k[i] = 0;
    }
    for (int i = 0; i < 26; i++)
    {
        if (k[i] == 0)
        {
            DFS(i, adj, k, s);
        }
    }
    return s;
}

int main(int argc, char** argv)
{
    string index[4096];
    string word;
    int count = 0;
    int max_len = 0;
    
    bool adj[26][26];
    bool exists[26];
    for (int i = 0; i < 26; i++)
    {
        exists[i] = false;
        for (int j = 0; j < 26; j++)
        {
            adj[i][j] = false;
        }
    }
    
    cin >> word;
    char first = word[0];
    
    while (word != "#")
    {
        if (word[0] != first)
        {
            int a, b;
            a = (int)first;
            b = (int)word[0];
            adj[a-65][b-65] = true;
            exists[a-65] = true;
            exists[b-65] = true;
            first = word[0];
        }
        index[count] = word;
        count++;
        if (word.length() > max_len)
        {
            max_len = word.length();
        }
        cin >> word;
    }
    
    for (int i = 2; i <= max_len; i++)
    {
        string start = "";
        for (int j = 0; j < count; j++)
        {
            if (index[j].length() < i)
            {
                continue;
            }            
            
            if (start == "")
            {
                start = index[j].substr(0, i);
                continue;
            }
            
            if (index[j].substr(0, i-1) == start.substr(0, i-1))
            {
                if (index[j].substr(i-1, 1) == start.substr(i-1, 1))
                {
                    continue;
                }
                else
                {
                    char x, y;
                    x = start[i-1];
                    y = index[j][i-1];
                    int a, b;
                    a = (int)(x);
                    b = (int)(y);
                    adj[a-65][b-65] = true;
                    exists[a-65] = true;
                    exists[b-65] = true;
                    start = index[j].substr(0, i);
                }
            }
            else
            {
                start = index[j].substr(0, i);
            }
        }
    }
    
    stack<int> s = DFS_Directed(adj);

    while (!s.empty())
    {
        if (exists[s.top()])
        {
            cout << (char)(s.top()+65);
        }
        s.pop();
    }
    
    cout << endl;
    
    return 0;
}

