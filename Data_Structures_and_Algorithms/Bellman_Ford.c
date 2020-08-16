//
//  main.c
//  DSA_Project
//
//  Created by �ڹ�ȣ on 2019/11/29.
//  Copyright ? 2019 �ڹ�ȣ. All rights reserved.
//

#include <stdio.h>

#define INF 9999999 // ���� ���� �� ���� �� -INF
#define MAX 99999   // ����̰� �� �� �ִ� �ִ� ��

/*
-1�� ����ϴ� ���� �� ������ �ִ�.

1. Positive loop �� ���� �� -1 �̴�.
����̰� �� loop�� ��� ���� ���� ���������� �� �� ������ �� ������ �ִ� ��ΰ� ����.

2. ���� ���� ���.
����̰� ����� ���� ���� ���� ���� ���� �ִ� �� ó�� ���� �� �ֱ� ������ MAX�� �����ߴ�.
����̴� ��� ������ ���� �� �־ �ִ� MAX��ŭ �� �� �ִٰ� ��������.
��Ʈ�� ���� ���� ���� -INF + MAX ���� �۴ٸ� �̴� ��Ʈ�ѱ��� ���� ���� ���ٴ� ���̴�.
�� �� ������ -1�� ����ؾ� �Ѵ�.

MAX�� ���� �� ���� �ִ� �� �� �ִ� ���� 1000�����̰� �ִ� ���� ���� 99�� �̴�. �� 99000�̻��� ���� ������ �ȴ�.
�̿� ���߾� INF�� ���� MAX���ٸ� ũ�� ������ �ȴ�.
*/

int LS[100][100];   // London Street
int D[100], P[100]; // Distence, Parent vertex
int n, m;

void setting(void);
void check(void);
int Bellman_Ford(void); // Node�� ���� 100�� ���Ϸ� n^3�ص� 100000ȸ�� �ð����� ����.

int main()
{

    scanf("%d %d", &n, &m);

    setting();

    // check();

    int solution = 0;
    solution = Bellman_Ford();

    //check();

    if (solution == -1 || D[n - 1] < -INF + MAX)
    {
        printf("-1\n");
    }
    else
    {
        //check();
        int current = n - 1, cnt = 0;
        int reverse[100];
        while (current > -1)
        {
            reverse[cnt] = current;
            current = P[current];
            cnt++;
        }
        int i;
        for (i = cnt - 1; i >= 0; i--)
        {
            printf("%d ", reverse[i] + 1);
        }
        printf("\n");
    }

    return 0;
}

void setting(void)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        P[i] = -1;
        D[i] = -INF;
        for (j = 0; j < n; j++)
        {
            LS[i][j] = -INF;
        }
    }

    for (i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (LS[u - 1][v - 1] < w)
            LS[u - 1][v - 1] = w;
    }
}

void check(void)
{
    int i, j;
    printf("\nLS ARRAY : \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", LS[i][j]);
        }
        printf("\n");
    }
    printf("\nDistence ARRAY : \n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", D[i]);
    }
    printf("\n\nParent ARRAY : \n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", P[i]);
    }
    printf("\n\n");
}

int Bellman_Ford(void)
{
    D[0] = 0;
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                if (D[k] < D[j] + LS[j][k])
                {
                    D[k] = D[j] + LS[j][k];
                    P[k] = j;
                }
            }
        }
    }

    for (j = 0; j < n; j++)
    {
        for (k = 0; k < n; k++)
        {
            if (D[k] < D[j] + LS[j][k])
                return -1;
        }
    }
    return 1;
}
