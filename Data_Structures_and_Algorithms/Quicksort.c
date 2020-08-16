#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

void Swap(int arr[], int x, int y) // arr[x]�� arr[y]�� �����մϴ�.
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

int Partition(int arr[], int left, int right)
{
    // arr : �Է¹��� ���� ����
    // �Ǻ��� ��ġ�� ���� ���ʿ��� �����ϰ�, quicksort�� ������ �̿��ϼ���.
    int x = arr[left];
    int i = left;
    int j = right;

    while (1)
    {

        while (i < j && arr[j] >= x)
            j--;
        while (i < j && arr[i] <= x)
            i++;

        if (i < j)
        {
            Swap(arr, i, j);
        }
        else
        {
            Swap(arr, left, j);
            return j;
        }
    }
}

void QuickSort(int arr[], int left, int right)
{
    // �ѷ� ����� ���ʰ� �������� �����մϴ�.  Partition �Լ��� �̿��ϼ���.
    int center;
    if (left < right)
    {
        center = Partition(arr, left, right);
        QuickSort(arr, left, center);
        QuickSort(arr, center + 1, right);
    }
}

//�����Լ�
int main()
{
    int n, i;
    int a[100];

    // Customize
    //srand((unsigned)time(NULL));

    //while(n!=999){

    printf("��� ���ڷ� �����Ͻðڽ��ϱ�?\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        a[i] = rand() % 1000;
    //n���� ���� �Է¹���

    printf("������ �迭 :");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    QuickSort(a, 0, n - 1); //����

    printf("������ �迭 :");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    //}
    return 0;
}
