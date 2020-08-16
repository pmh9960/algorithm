#include <stdio.h>
#include <stdlib.h>

int HEAP_SIZE = 20;

struct Heap
{
    int *arr;      //heap array
    int count;     //����
    int capacity;  //���뷮
    int heap_type; // 0 �϶��� min heap , 1 �� ���� max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity, int heap_type);
void insert(Heap *h, int key);
void print(Heap *h); //�� ��ü�� ���
void heapify_bottom_top(Heap *h, int index);
void heapify_top_bottom(Heap *h, int parent_node);
int PopMin(Heap *h);

int main()
{
    int i;
    Heap *heap = CreateHeap(HEAP_SIZE, 0); //�ּ���
    if (heap == NULL)
    {
        printf("__Memory Issue____\n");
        return -1;
    }

    for (i = 9; i > 0; i--)
        insert(heap, i);

    print(heap);

    for (i = 9; i >= 0; i--)
    {
        printf(" Pop Minima : %d\n", PopMin(heap));
        print(heap);
    }
    return 0;
}

Heap *CreateHeap(int capacity, int heap_type)
{
    Heap *h = (Heap *)malloc(sizeof(Heap)); //one is number of heap

    //�޸� �Ҵ� ���� ���� Ȯ��
    if (h == NULL)
    {
        printf("Memory Error!");
        return h;
    }
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->arr = (int *)malloc(capacity * sizeof(int)); //����Ʈ ũ�� ����

    //�Ҵ翡 �����ߴ��� Ȯ��
    if (h->arr == NULL)
    {
        printf("Memory Error!");
        return h;
    }
    return h;
}

void insert(Heap *h, int key)
{
    //arr�� count�� ũ�⸦ �÷���, key���� ���� �߰�
    if (h->count >= h->capacity)
    {
        printf("Heap is full!");
        return;
    }

    h->count = h->count + 1;
    h->arr[h->count] = key;

    heapify_bottom_top(h, h->count);
}

void heapify_bottom_top(Heap *h, int index)
{
    // ������ �Ҷ����� ���ο� ���Ҹ� ������ ��忡 ����, sift-up �Ѵ�.��, �ڸ� ã���ֱ�
    if (index == 1)
    {
        return;
    }

    if (h->arr[index] < h->arr[index / 2])
    {
        int temp = h->arr[index];
        h->arr[index] = h->arr[index / 2];
        h->arr[index / 2] = temp;

        heapify_bottom_top(h, index / 2);
    }
    return;
}

void heapify_top_bottom(Heap *h, int parent_node)
{
    // ������ �� ������ ������ ��带 ��Ʈ ���� �ڸ��� �ű�� , ��üũ�⸦ 1��ŭ ���Դϴ�. �׸��� ��Ʈ��带 sift-down �մϴ�. (����Լ��� �̿��մϴ�)
    int parent_value, left_value, right_value;
    parent_value = h->arr[parent_node];

    // There is no child.
    if (parent_node * 2 > h->count)
    {
        return;
    }

    // There is one child.
    else if (parent_node * 2 == h->count)
    {
        left_value = h->arr[parent_node * 2];
        if (left_value < parent_value)
        {
            h->arr[parent_node] = left_value;
            h->arr[parent_node * 2] = parent_value;
            heapify_top_bottom(h, parent_node * 2);
            return;
        }
        return;
    }

    // There are two children.
    else
    {
        left_value = h->arr[parent_node * 2];
        right_value = h->arr[parent_node * 2 + 1];
        if (left_value < right_value)
        {
            if (left_value < parent_value)
            {
                h->arr[parent_node] = left_value;
                h->arr[parent_node * 2] = parent_value;
                heapify_top_bottom(h, parent_node * 2);
                return;
            }
            return;
        }
        else
        {
            if (right_value < parent_value)
            {
                h->arr[parent_node] = right_value;
                h->arr[parent_node * 2 + 1] = parent_value;
                heapify_top_bottom(h, parent_node * 2 + 1);
                return;
            }
            return;
        }
    }
}

int PopMin(Heap *h)
{
    //���� ����� ���� "__Heap is Empty__"�� ����Ѵ�.
    // ���� �ּҰ��� pop ���ְ�, ù ��° ���� ���������� ��ü�ϰ� ������ ��带 ����
    if (h->count == 0)
    {
        printf("__Heap is Empty__\n");
        return -1;
    }
    int pop = h->arr[1];
    h->arr[1] = h->arr[h->count];
    h->count = h->count - 1;

    heapify_top_bottom(h, 1);

    return pop;
}
void print(Heap *h)
{
    int i;
    printf("_________�� ���__________\n");
    for (i = 1; i <= h->count; i++)
    {
        printf("-> %d ", h->arr[i]);
    }
    printf("->__/\\__\n");
}
