//
//  main.c
//  DSA_Project
//
//  Created by 박민호 on 2019/11/29.
//  Copyright ? 2019 박민호. All rights reserved.
//

#include <stdio.h>

#define INF 9999999 // 길이 없을 때 갖는 값 -INF
#define MAX 99999   // 흥민이가 벌 수 있는 최대 돈

/*
-1을 출력하는 경우는 두 종류가 있다.

1. Positive loop 가 있을 때 -1 이다.
흥민이가 이 loop를 계속 돌면 돈을 무제한으로 벌 수 있으니 이 때에는 최단 경로가 없다.

2. 길이 없는 경우.
흥민이가 벌어온 돈이 길이 없는 곳을 길이 있는 곳 처럼 만들 수 있기 때문에 MAX를 정의했다.
흥민이는 어떻게 런던의 길이 나 있어도 최대 MAX만큼 벌 수 있다고 가정하자.
토트넘 까지 가는 값이 -INF + MAX 보다 작다면 이는 토트넘까지 가는 길이 없다는 뜻이다.
즉 이 때에도 -1을 출력해야 한다.

MAX의 값은 한 길의 최대 벌 수 있는 돈이 1000이하이고 최대 가는 길은 99개 이다. 즉 99000이상의 값을 가지면 된다.
이에 맞추어 INF의 값은 MAX보다만 크게 잡으면 된다.
*/

int LS[100][100];   // London Street
int D[100], P[100]; // Distence, Parent vertex
int n, m;

void setting(void);
void check(void);
int Bellman_Ford(void); // Node의 수가 100개 이하로 n^3해도 100000회로 시간문제 없음.

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
