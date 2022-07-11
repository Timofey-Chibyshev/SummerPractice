#include "pch.h"
#include "FibonachiHeap.h"

TEST(TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Init, InitHeapTEST) 
{
	Heap_t* h = InitHeap();
	EXPECT_TRUE(!DisplayRootList(h));
}

TEST(NullInit, InitHeapTEST)
{
	Heap_t* h = NULL;
	EXPECT_TRUE(DisplayRootList(h) == -1);
}

TEST(OneNode, AddElemTEST)
{
	Heap_t* h = InitHeap();
	AddElem(h, 1);
	EXPECT_TRUE(DisplayRootList(h));
}

TEST(InsertEightNodes, AddElemTEST)
{
	Heap_t* h = InitHeap();
	for (int i = 1; i <= 8; i++) 
	{
		AddElem(h, i);
	}
	EXPECT_TRUE(DisplayRootList(h) == 8);
	EXPECT_TRUE(h->min->key);
}

TEST(NineNodesExtract, ExtractMinTEST)
{
	Heap_t* h = InitHeap();
	Node_t* tmp = NULL;
	for (int i = 1; i <= 9; i++) 
	{
		AddElem(h, i);
	}
	EXPECT_TRUE(DisplayRootList(h) == 9);
	EXPECT_TRUE(h->min->key);

	for (int i = 1; i <= 9; i++) 
	{
		tmp = ExtractMin(h);
		EXPECT_TRUE(tmp->key == i);
		EXPECT_TRUE(DisplayRootList(h) == 9 - i);
	}
}

TEST(EmptyHeaps, UnionTEST)
{
	Heap_t* H1 = InitHeap();
	Heap_t* H2 = InitHeap();
	Heap_t* H = Union(H1, H2);
	EXPECT_TRUE(!DisplayRootList(H));
	ASSERT_EQ(H->min, nullptr);
}

TEST(OneElemHeaps, UnionTEST)
{
	Heap_t* H1 = InitHeap();
	AddElem(H1, 1);
	Heap_t* H2 = InitHeap();
	AddElem(H2, 0);
	Heap_t* H = Union(H1, H2);
	EXPECT_TRUE(DisplayRootList(H), 2);
	EXPECT_TRUE(H->min->key == 0);
	EXPECT_TRUE(H->min->right->key, 1);
	EXPECT_TRUE(H->min->left->key, 1);
}

TEST(ManyElemsHeaps, UnionTEST)
{
	Heap_t* H1 = InitHeap();
	for (int i = 0; i <= 9; i += 2)
	{
		AddElem(H1, i);
	}
	DisplayRootList(H1);
	Heap_t* H2 = InitHeap();
	for (int i = 1; i <= 9; i+=2)
	{
		AddElem(H2, i);
	}
	DisplayRootList(H2);
	Heap_t* H = Union(H1, H2);

	EXPECT_TRUE(DisplayRootList(H), 10);
	EXPECT_TRUE(H->min->key == 0);
	EXPECT_TRUE(H->min->right->key, 2);
	EXPECT_TRUE(H->min->left->key, 9);
}