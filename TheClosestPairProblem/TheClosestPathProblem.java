package theclosestpathproblem;

import java.io.*;
import java.util.Scanner;

public class TheClosestPathProblem
{
    private static int[][] Merge(int[][] t1, int[][] t2, int l, int m, int r, int index)
    {
        int i = l, j = m+1, k = l;
        int[][] a = new int[r+1][2];
        while ((i <= m) && (j <= r))
        {
            if (t1[i][index] < t2[j][index])
            {
                a[k][0] = t1[i][0];
                a[k][1] = t1[i][1];
                i++;
            }
            else
            {
                a[k][0] = t2[j][0];
                a[k][1] = t2[j][1];
                j++;
            }
            k++;
        }
        while (i <= m)
        {
            a[k][0] = t1[i][0];
            a[k][1] = t1[i][1];
            i++;
            k++;
        }
        while (j <= r)
        {
            a[k][0] = t2[j][0];
            a[k][1] = t2[j][1];
            j++;
            k++;
        }
        return a;
    }
    
    private static int[][] MergeSort(int[][] t, int l, int r, int index)
    {
        if (l < r)
        {
            int m = (int)Math.floor((l+r)/2);
            int[][] t1 = MergeSort(t, l, m, index);
            int[][] t2 = MergeSort(t, m+1, r, index);
            t = Merge(t1, t2, l, m, r, index);
        }
        return t;
    }
    
    private static double recursiveCPP(int[][] p, int i, int j)
    {
        if ((j-i) < 3)
        {
            p = MergeSort(p, i, j, 1);
            double delta = distance(p[i], p[i+1]);
            if ((j-i) == 1)
            {
                return delta;
            }
            else if (distance(p[i+1],p[i+2]) < delta)
            {
                return distance(p[i+1],p[i+2]);
            }
            else if (distance(p[i],p[i+2]) < delta)
            {
                return distance(p[i],p[i+2]);
            }
            return delta;
        }
        else
        {
            int k = i + ((j-i)/2);
            int l = p[k][0];
            double deltaL = recursiveCPP(p, i, k);
            double deltaR = recursiveCPP(p, k+1, j);
            double delta = Math.min(deltaL, deltaR);
            Merge(p, p, i, k, j, 1);
            int t = -1;
            int[][] b = new int[j+1][2];
            for (int m = i; m < j; m++)
            {
                if ((p[m][0] > (l - delta)) && (p[m][0] < (l + delta)))
                {
                    t++;
                    b[t][0] = p[m][0];
                    b[t][1] = p[m][1];
                    for (int u = 1; u < (t-1); u++)
                    {
                        for (int v = k+1; v < Math.min(t,k+7); v++)
                        {
                            delta = Math.min(delta, distance(b[k], b[v]));
                        }
                    }
                }
            }
            return delta;
        }
    }
    
    private static double distance(int[] q1, int[] q2)
    {
        return Math.sqrt(Math.pow((q2[0] - q1[0]), 2) + Math.pow((q2[1] - q1[1]), 2));
    }
    
    public static void main(String[] args)
    {
        int n;
        
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        
        do
        {
            int[][] p = new int[n][2];
            
            for (int i = 0; i < n; i++)
            {
                p[i][0] = in.nextInt();
                p[i][1] = in.nextInt();
            }
            
            for (int i = 0; i < n; i++)
            {
                System.out.println(p[i][0]+" "+p[i][1]);
            }
            
            p = MergeSort(p, 0, n-1, 1);
            
            double delta = recursiveCPP(p, 0, n-1);
            delta = (double)Math.round(delta * 10000) / 10000;
            
            if (delta >= 10000)
            {
                System.out.println("INFINITY");
            }
            else
            {
                System.out.println(delta);
            }
            
            n = in.nextInt();
        } while (n > 0);
    }
}
