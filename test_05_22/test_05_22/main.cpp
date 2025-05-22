//template <class Fn, class... Args>
//void call_once(once_flag& flag, Fn&& fn, Args&&... args);
//
//// call_once example
//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <mutex >
//void set_winner(int x) { winner = x; }
//std::once_flag winner_flag;
//void wait_1000ms(int id) {
//	// count to 1000, waiting 1ms between increments:
//	for (int i = 0; i < 1000; ++i)
//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
//	// claim to be the winner (only the first such call is executed):
//
//	std::call_once(winner_flag, set_winner, id);
//}
//int main()
//{
//	std::thread threads[10];
//	// spawn 10 threads:
//	for (int i = 0; i < 10; ++i)
//		threads[i] = std::thread(wait_1000ms, i + 1);
//	std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";
//	for (auto& th : threads)
//		th.join();
//	std::cout << "winner thread: " << winner << '\n';
//	return 0;
//}

//#include <atomic>
//#include <iostream>
//#include <thread>
//#include <vector>
//using namespace std;
//atomic<int> acnt;
////atomic_int acnt;
//int cnt;
//void Add1(atomic<int>& cnt)
//{
//	int old = cnt.load();
//	// 如果cnt的值跟old相等，则将cnt的值设置为old+1，并且返回true，这组操作是原⼦的。
//	// 那么如果在load和compare_exchange_weak操作之间cnt对象被其他线程改了
//	// 则old和cnt不相等，则将old的值改为cnt的值，并且返回false。
//	while (!atomic_compare_exchange_weak(&cnt, &old, old + 1));
//	//while (!cnt.compare_exchange_weak(old, old + 1));
//}
//void f()
//{
//	for (int n = 0; n < 100000; ++n)
//	{
//		++acnt;
//		// Add1的⽤CAS模拟atomic的operator++的原⼦操作
//		//Add1(acnt);
//		++cnt;
//	}
//}
//int main()
//{
//	std::vector<thread> pool;
//	for (int n = 0; n < 4; ++n)
//		pool.emplace_back(f);
//	for (auto& e : pool)
//		e.join();
//	cout << "原⼦计数器为 " << acnt << '\n'
//		<< "⾮原⼦计数器为 " << cnt << '\n';
//	return 0;
//}

struct Date
{
	int _year = 1;
	int _month = 1;
	int _day = 1;
};
template<class T>
void check()
{
	cout << typeid(T).name() << endl;
	cout << std::is_trivially_copyable<T>::value << endl;
	cout << std::is_copy_constructible<T>::value << endl;
	cout << std::is_move_constructible<T>::value << endl;
	cout << std::is_copy_assignable<T>::value << endl;
	cout << std::is_move_assignable<T>::value << endl;
	cout << std::is_same<T, typename std::remove_cv<T>::type>::value << endl
		<< endl;
}
//int main()
//{
// check<int>();
// check<double>();
// check<int*>();
// check<Date>();
// check<Date*>();
// check<string>();
// check<string*>();
//
// return 0;
//}

// atomic::compare_exchange_weak example:
#include <iostream> // std::cout
#include <atomic> // std::atomic
#include <thread> // std::thread
#include <vector> // std::vector
// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);
void append(int val, int n)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	for (int i = 0; i < n; i++)
	{
		// append an element to the list
		Node* oldHead = list_head;
		Node* newNode = new Node{ val + i,oldHead };
		d - safe way :
		while (!list_head.compare_exchange_weak(oldHead, newNode))
			newNode->next = oldHead;
	}
}
int main()
{
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	threads.emplace_back(append, 0, 10);
	threads.emplace_back(append, 20, 10);
	threads.emplace_back(append, 30, 10);
	threads.emplace_back(append, 40, 10);
	for (auto& th : threads)
		th.join();
	// print contents:
	for (Node* it = list_head; it != nullptr; it = it->next)
		std::cout << ' ' << it->value;
	std::cout << '\n';
	// cleanup:
	Node* it;
	while (it = list_head)
	{
		list_head = it->next;
		delete it;
	}
	return 0;
}

#include <iostream> // std::cout
#include <atomic> // std::atomic
#include <thread> // std::thread
#include <mutex> // std::thread
#include <vector> // std::vector
template<typename T>
struct node
{
	T data;
	node* next;
	node(const T& data) : data(data), next(nullptr) {}
};
namespace lock_free
{
	template<typename T>
	class stack
	{
	public:
		std::atomic<node<T>*> head = nullptr;
	public:
		void push(const T& data)
		{
			node<T>* new_node = new node<T>(data);
			// 将 head 的当前值放到 new_node->next 中
			new_node->next = head.load(std::memory_order_relaxed);
			// 现在令 new_node 为新的 head ，但如果 head 不再是
			// 存储于 new_node->next 的值（某些其他线程必须在刚才插⼊结点）
			// 那么将新的 head 放到 new_node->next 中并再尝试
			while (!head.compare_exchange_weak(new_node->next, new_node,
				std::memory_order_release,
				std::memory_order_relaxed))
				; // 循环体为空
		}
	};
}
namespace lock
{
	template<typename T>
	class stack
	{
	public:
		node<T>* head = nullptr;
		void push(const T& data)
		{
			node<T>* new_node = new node<T>(data);
			new_node->next = head;
			head = new_node;
		}
	};
}
int main()
{
	lock_free::stack<int> st1;
	lock::stack<int> st2;
	std::mutex mtx;
	int n = 1000000;
	auto lock_free_stack = [&st1, n] {
		for (size_t i = 0; i < n; i++)
		{
			st1.push(i);
		}
		};
	auto lock_stack = [&st2, &mtx, n] {
		for (size_t i = 0; i < n; i++)
		{
			std::lock_guard<std::mutex> lock(mtx);
			st2.push(i);
		}
		};
	// 4个线程分别使⽤⽆锁⽅式和有锁⽅式插⼊n个数据到栈中对⽐性能
	size_t begin1 = clock();
	std::vector<std::thread> threads1;
	for (size_t i = 0; i < 4; i++)
	{
		threads1.emplace_back(lock_free_stack);
	}
	for (auto& th : threads1)
		th.join();
	size_t end1 = clock();
	std::cout << end1 - begin1 << std::endl;
	size_t begin2 = clock();
	std::vector<std::thread> threads2;
	for (size_t i = 0; i < 4; i++)
	{
		threads2.emplace_back(lock_stack);
	}
	for (auto& th : threads2)
		th.join();
	size_t end2 = clock();

	std::cout << end2 - begin2 << std::endl;
	return 0;
}