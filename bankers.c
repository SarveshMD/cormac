#include <stdio.h>

int main()
{
    int m, n;
    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("\nEnter the number of resources: ");
    scanf("%d", &n);

    int alloc[m][n], need[m][n], max[m][n];
    int avail[n], safeSeq[m], finish[m];

    printf("Enter allocation matrx: \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Available Matrix: \n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &avail[i]);
    }

    printf("Enter Maximum Matrix: \n");

    for (int i = 0; i < m; i++)
    {
        finish[i] = 0;
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;

    while (count < m)
    {
        int found = 0;

        for (int i = 0; i < m; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < n; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        break;
                    }
                }
                if (j == n)
                {
                    for (int k = 0; k < n; k++)
                    {
                        avail[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0)
        {
            break;
        }
    }

    if (count == m)
    {
        printf("SYSTEM IN SAFE STATE.");
        for (int i = 0; i < m; i++)
        {
            printf("P%d->", safeSeq[i]);
        }
    }
    else
    {
        printf("The System is in unsafe state.");
    }
}