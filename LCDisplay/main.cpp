#include <iostream>
#include <stdio.h>

using namespace std;

void draw1(short width, short height, short line)
{
    for (int i = 1; i < width; i++)
    {
        cout << " ";
    }
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
    }
    else
    {
        cout << "|";
    }
}

void draw2(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else if (line > 1 && line < height/2+1)
    {
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
    }
}

void draw3(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else
    {
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
}

void draw4(short width, short height, short line)
{
    if (line == 1 || line == height)
    {
        for (int i = 0; i < width; i++)
        {
            cout << " ";
        }
    }
    else if (line > 1 && line < height/2+1)
    {
        cout << "|";
        for (int i = 0; i < width-2; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
    else if (line == height/2+1)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else
    {
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
}

void draw5(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else if (line < height && line > height/2+1)
    {
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
    }
}

void draw6(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else if (line < height && line > height/2+1)
    {
        cout << "|";
        for (int i = 0; i < width-2; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
    }
}

void draw7(short width, short height, short line)
{
    if (line == 1)
    {
        cout << " ";
        for (int i = 1; i < width-1; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else
    {
        for (int i = 1; i < width; i++)
        {
            cout << " ";
        }
        if (line == height/2+1 || line == height)
        {
            cout << " ";
        }
        else
        {
            cout << "|";
        }
    }
}

void draw8(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-2; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
}

void draw9(short width, short height, short line)
{
    if (line == 1 || line == height/2+1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else if (line < height && line > height/2+1)
    {
        for (int i = 0; i < width-1; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-2; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
}

void draw0(short width, short height, short line)
{
    if (line == 1 || line == height)
    {
        cout << " ";
        for (int i = 0; i < width-2; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else if (line == height/2+1)
    {
        for (int i = 0; i < width; i++)
        {
            cout << " ";
        }
    }
    else
    {
        cout << "|";
        for (int i = 0; i < width-2; i++)
        {
            cout << " ";
        }
        cout << "|";
    }
}

void draw(char num, short size, short line);

int main()
{    
    while(true)
    {
        short s;
        char n[9];
        
        scanf("%d %s", &s, &n);
        
        if (s == 0 && n[0] == '0')
        {
            break;
        }
        
        for (int i = 1; i <= (2*s+3); i++)
        {
            for (int j = 0; j < (sizeof(n) / sizeof(n[0])); j++)
            {
                draw(n[j], s, i);
                cout << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}

void draw(char num, short size, short line)
{
    switch(num)
    {
        case '1':
            draw1(size+2, (2*size)+3, line);
            break;
        case '2':
            draw2(size+2, (2*size)+3, line);
            break;
        case '3':
            draw3(size+2, (2*size)+3, line);
            break;
        case '4':
            draw4(size+2, (2*size)+3, line);
            break;
        case '5':
            draw5(size+2, (2*size)+3, line);
            break;
        case '6':
            draw6(size+2, (2*size)+3, line);
            break;
        case '7':
            draw7(size+2, (2*size)+3, line);
            break;
        case '8':
            draw8(size+2, (2*size)+3, line);
            break;
        case '9':
            draw9(size+2, (2*size)+3, line);
            break;
        case '0':
            draw0(size+2, (2*size)+3, line);
            break;
    }
}