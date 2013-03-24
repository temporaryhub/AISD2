#include <iostream>

using namespace std;

int main()
{
    int r[255];
    int l, n;
    
    cin >> l;
    
    while (l > 0)
    {        
        cin >> n;
        
        int s[n], w[50][n];
        
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }
        
        for (int i = 0; i < n; i++)
        {
            w[i][i] = 0;
        }
        
        for (int j = 1; j < n; j++)
        {
            for (int i = 0; i < (n-j+1); i++)
            {
                int c = i + j - 1;
                w[i][j] = 1001;
                for (int k = i; k < c-1; k++)
                {
                    int q = w[i][k] + w[k+1][c];// a tutaj trzeba dorobić współczynnik
                    if (q < w[i][c])
                    {
                        w[i][c] = q;
                    }
                }
            }
        }
        
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << i << ',' << j << ' ' << w[i][j] << endl;
            }
        }
        
        cin >> l;
    }

    return 0;
}

