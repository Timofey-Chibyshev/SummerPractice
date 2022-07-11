#include "FibonachiHeap.h"

Heap_t* InitHeap()
{
    Heap_t* heap = (Heap_t*)malloc(sizeof(Heap_t));
    if (heap != NULL)
    {
        heap->min = NULL;
        heap->size = 0;
    }
    return heap;
}

Node_t* _newNode(int key)
{
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if (node != NULL)
    {
        node->left = NULL;
        node->right = NULL;
        node->child = NULL;
        node->parent = NULL;
        node->key = key;
        node->degree = 0;
        node->mark = 0;
    }
    return node;
}

void _insertNode(Node_t* a, Node_t* b, Node_t* c)
{
    b->left = a;
    a->right = b;

    b->right = c;
    c->left = b;
}

void _removeNode(Node_t* a, Node_t* b, Node_t* c)
{
    a->right = c;
    c->left = a;
}

Heap_t* AddElem(Heap_t* heap, int key)
{
    Node_t* node = _newNode(key);
    if (heap == NULL)
    {
        heap = InitHeap();
    }
    if (heap->min == NULL && heap->size == 0)
    {
        heap->min = node;
        node->left = node;
        node->right = node;
    }
    else
    {
        _insertNode(heap->min, node, heap->min->right);
        if (key < heap->min->key)
        {
            heap->min = node;
        }
    }
    heap->size++;
    return heap;
}

void _heapLink(Heap_t* heap, Node_t* a, Node_t* b)
{
    _removeNode(a->left, a, a->right);
    
    if (b->child)
    {
        _insertNode(b->child, a, b->child->right);
    }
    else
    {
        _insertNode(a, a, a);
    }

    a->parent = b;
    b->child = a;
    b->degree++;
    a->mark = 0;
}

int _log2(int num)
{
    int res = 1;
    while (num >>= 1) res++;
    {
        return res;
    }
}

void _consolidate(Heap_t* heap)
{
    int max_degree = _log2(heap->size);
    Node_t** degrees = (Node_t**)calloc(max_degree, sizeof(Node_t*));
    Node_t* start = heap->min, * curr = heap->min;
    do
    {
        int degree = curr->degree;
        Node_t* next = curr->right;
        while (degrees[degree] != NULL)
        {
            Node_t* node = degrees[degree];
            if (curr->key > node->key)
            {
                Node_t* tmp = curr;
                curr = node;
                node = tmp;
            }
            if (node == start)
            {
                start = next->left;
            }
            if (node == next)
            {
                next = next->right;
            }
            _heapLink(heap, node, curr);
            degrees[degree++] = NULL;
        }
        degrees[degree] = curr;
        curr = next;
    } while (curr != start);
    heap->min = NULL;

    for (int i = 0; i < max_degree; i++)
    {
        if (degrees[i] != NULL && (heap->min == NULL || degrees[i]->key < heap->min->key))
        {
            heap->min = degrees[i];
        }
    }
}

Node_t* ExtractMin(Heap_t* heap)
{
    if (heap == NULL || heap->min == NULL)
    {
        return NULL;
    }

    Node_t* min = heap->min, * child = min->child, ** next_child, * start = child;
    if (child != NULL)
    {
        do
        {
            next_child = child->right;
            _insertNode(min, child, min->right);
            child->parent = NULL;
            child = next_child;
        } while (child != start);
    }

    _removeNode(min->left, min, min->right);

    if (min == min->right)
    {
        heap->min = NULL;
    }
    else
    {
        heap->min = heap->min->right;
        _consolidate(heap);
    }
    heap->size--;
    return min;
}

void _deleteNode(Node_t* node)
{
    if (node == NULL)
    {
        return;
    }

    Node_t* curr = node->child;
    if (curr != NULL)
    {
        Node_t* start = curr;
        do
        {
            _deleteNode(curr->child);
            curr = curr->right;
        } while (curr != start);
    }
    free(curr);
}

void DeleteHeap(Heap_t* heap)
{
    if (heap == NULL)
    {
        return;
    }

    Node_t* curr = heap->min;
    if (curr != NULL)
    {
        Node_t* start = curr;
        do
        {
            _deleteNode(curr);
            curr = curr->right;
        } while (curr != start);
    }

    curr = heap->min;
    Node_t* start = curr;
    Node_t* tmp = NULL;
    do
    {
        tmp = curr;
        curr = curr->right;
        free(tmp);
    } while (curr != start);
    free(heap);
}

Heap_t* Union(Heap_t* H1, Heap_t* H2) 
{
    Heap_t* H = InitHeap();

    if (!H1->size && !H2->size)
    {
        H->size = 0;
        H->min = NULL;
        free(H1);
        free(H2);
        return H;
    }
    if (!H1->size && H2->size)
    {
        H->size = H2->size;
        H->min = H2->min;
        free(H1);
        free(H2);
        return H;
    }
    if (!H2->size && H1->size)
    {
        H->size = H1->size;
        H->min = H1->min;
        free(H1);
        free(H2);
        return H;
    } 

    if (H1->min->key > H2->min->key)
        return Union(H2, H1);
    
    H->min = H1->min;

    //Concatenate
    Node_t* H1head = H->min;
    Node_t* H1tail = H1head->left;

    Node_t* H2head = H2->min;
    Node_t* H2tail = H2head->left;
    
    H1tail->right = H2head;
    H2head->left = H1tail;
    H2tail->right = H1head;
    H1head->left = H2tail;

    H->size = H1->size + H2->size;

    free(H1);
    free(H2);
    return H;   
}

//for tests
int FibHeapExtractMinKey(Heap_t* h)
{
    Node_t* min = ExtractMin(h);
    if (min != NULL)
    {
        int res = min->key;
        printf("\n\n");
        printf("Extracted min key = %d", res);
        printf("\n\n");
        return res;
    }
    else
    {
        printf("\n\n");
        printf("Min = NULL");
        printf("\n\n");
        return -1;
    }
}

int DisplayRootList(Heap_t* h)
{
    printf("\n\n");
    if (!h)
    {
        printf("No heap");
        printf("\n\n");
        return -1;
    }

    Node_t* tmp = h->min;
    if (!tmp)
    {
        printf("Empty heap");
    }
    else
    {
        do
        {
            printf("%d ", tmp->key);
            tmp = tmp->right;
        } while (tmp != h->min);
    }
    printf("\n\n");

    return h->size;
}