#pragma once 

#ifndef __FIBONACHIHEAP_H_
#define __FIBONACHIHEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning (disable: 4996)

#include <stdio.h>
#include <malloc.h>

#define BUF_SIZE 16

typedef struct Node
{
    struct Node* left, * right, * child, * parent;
    int key, degree, mark;
} Node_t;

typedef struct Heap
{
    int size;
    Node_t* min;
} Heap_t;

//main functions
Heap_t* InitHeap();

Heap_t* AddElem(Heap_t* heap, int key);

Node_t* ExtractMin(Heap_t* heap);

Heap_t* Union(Heap_t* H1, Heap_t* H2);

void DeleteHeap(Heap_t* heap);

//additional functions
void _deleteNode(Node_t* node);

void _consolidate(Heap_t* heap);

int _log2(int num);

void _heapLink(Heap_t* heap, Node_t* a, Node_t* b);

void _removeNode(Node_t* a, Node_t* b, Node_t* c);

void _insertNode(Node_t* a, Node_t* b, Node_t* c);

Node_t* _newNode(int key);

//for tests
int FibHeapExtractMinKey(Heap_t* h);

int DisplayRootList(Heap_t* h);

#ifdef __cplusplus
}
#endif
#endif