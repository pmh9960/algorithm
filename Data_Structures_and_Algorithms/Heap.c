#include <stdio.h>
#include <stdlib.h>

int HEAP_SIZE = 20;

struct Heap
{
    int *arr;      //heap array
    int count;     //갯수
    int capacity;  //사용용량
    int heap_type; // 0 일때는 min heap , 1 일 때는 max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity, int heap_type);
void insert(Heap *h, int key);
void print(Heap *h); //힙 전체를 출력
void heapify_bottom_top(Heap *h, int index);
void heapify_top_bottom(Heap *h, int parent_node);
int PopMin(Heap *h);

int main()
{
    int i;
    Heap *heap = CreateHeap(HEAP_SIZE, 0); //최소힙
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

    //메모리 할당 실패 여부 확인
    if (h == NULL)
    {
        printf("Memory Error!");
        return h;
    }
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->arr = (int *)malloc(capacity * sizeof(int)); //바이트 크기 설정

    //할당에 성공했는지 확인
    if (h->arr == NULL)
    {
        printf("Memory Error!");
        return h;
    }
    return h;
}

void insert(Heap *h, int key)
{
    //arr와 count의 크기를 늘려줌, key값을 힙에 추가
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
    // 삽입을 할때에는 새로운 원소를 마지막 노드에 놓고, sift-up 한다.즉, 자리 찾아주기
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
    // 삭제를 할 때에는 마지막 노드를 루트 노드로 자리를 옮기고 , 전체크기를 1만큼 줄입니다. 그리고 루트노드를 sift-down 합니다. (재귀함수를 이용합니다)
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
    //힙이 비었을 때는 "__Heap is Empty__"를 출력한다.
    // 힙의 최소값을 pop 해주고, 첫 번째 노드는 마지막으로 교체하고 마지막 노드를 삭제
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
    printf("_________힙 출력__________\n");
    for (i = 1; i <= h->count; i++)
    {
        printf("-> %d ", h->arr[i]);
    }
    printf("->__/\\__\n");
}
