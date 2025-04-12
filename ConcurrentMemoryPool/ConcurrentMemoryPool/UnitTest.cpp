#include "ObjectPool.h"
#include "ConcurrentAlloc.h"

void MultiThreadAlloc1()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 7; i++)
	{
		void* ptr = ConcurrentAlloc(7);
		v.push_back(ptr);
	}
	for (auto e : v)
	{
		ConcurrentFree(e, 7);
	}
}

void MultiThreadAlloc2()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 7; i++)
	{
		void* ptr = ConcurrentAlloc(16);
		v.push_back(ptr);
	}
	for (auto e : v)
	{
		ConcurrentFree(e, 16);
	}
}

void TestMultiThread()
{ 
	std::thread t1(MultiThreadAlloc1);
	std::thread t2(MultiThreadAlloc2);

	t1.join();
	t2.join();
}

//void TestConcurrentAlloc1()
//{
//	void* p1 = ConcurrentAlloc(6);
//	void* p2 = ConcurrentAlloc(8);
//	void* p3 = ConcurrentAlloc(7);
//	void* p4 = ConcurrentAlloc(1);
//	void* p5 = ConcurrentAlloc(6);
//	void* p6 = ConcurrentAlloc(7);
//	void* p7 = ConcurrentAlloc(7);
//
//	ConcurrentFree(p1, 6);
//	ConcurrentFree(p2, 8);
//	ConcurrentFree(p3, 7);
//	ConcurrentFree(p4, 1);
//	ConcurrentFree(p5, 6);
//	ConcurrentFree(p6, 7);
//	ConcurrentFree(p7, 7);
//}
//
//void TestConcurrentAlloc2()
//{
//	for (size_t i = 0; i < 1024; i++)
//	{
//		void* p1 = ConcurrentAlloc(6);
//		std::cout << p1 << std::endl;
//	}
//	void* p2 = ConcurrentAlloc(8);
//	std::cout << p2 << std::endl;
//}

int main()
{
	//TestObjectPool();
	//TLSTest();
	//TestConcurrentAlloc1();
	//TestConcurrentAlloc2();
	TestMultiThread();
	return 0;
}