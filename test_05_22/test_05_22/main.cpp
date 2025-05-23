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

//// atomic::compare_exchange_weak example:
//#include <iostream> // std::cout
//#include <atomic> // std::atomic
//#include <thread> // std::thread
//#include <vector> // std::vector
//// a simple global linked list:
//struct Node { int value; Node* next; };
//std::atomic<Node*> list_head(nullptr);
//void append(int val, int n)
//{
//	//std::this_thread::sleep_for(std::chrono::seconds(1));
//	for (int i = 0; i < n; i++)
//	{
//		// append an element to the list
//		Node* oldHead = list_head;
//		Node* newNode = new Node{ val + i,oldHead };
//		d - safe way :
//		while (!list_head.compare_exchange_weak(oldHead, newNode))
//			newNode->next = oldHead;
//	}
//}
//int main()
//{
//	// spawn 10 threads to fill the linked list:
//	std::vector<std::thread> threads;
//	threads.emplace_back(append, 0, 10);
//	threads.emplace_back(append, 20, 10);
//	threads.emplace_back(append, 30, 10);
//	threads.emplace_back(append, 40, 10);
//	for (auto& th : threads)
//		th.join();
//	// print contents:
//	for (Node* it = list_head; it != nullptr; it = it->next)
//		std::cout << ' ' << it->value;
//	std::cout << '\n';
//	// cleanup:
//	Node* it;
//	while (it = list_head)
//	{
//		list_head = it->next;
//		delete it;
//	}
//	return 0;
//}
//
//#include <iostream> // std::cout
//#include <atomic> // std::atomic
//#include <thread> // std::thread
//#include <mutex> // std::thread
//#include <vector> // std::vector
//template<typename T>
//struct node
//{
//	T data;
//	node* next;
//	node(const T& data) : data(data), next(nullptr) {}
//};
//namespace lock_free
//{
//	template<typename T>
//	class stack
//	{
//	public:
//		std::atomic<node<T>*> head = nullptr;
//	public:
//		void push(const T& data)
//		{
//			node<T>* new_node = new node<T>(data);
//			// 将 head 的当前值放到 new_node->next 中
//			new_node->next = head.load(std::memory_order_relaxed);
//			// 现在令 new_node 为新的 head ，但如果 head 不再是
//			// 存储于 new_node->next 的值（某些其他线程必须在刚才插⼊结点）
//			// 那么将新的 head 放到 new_node->next 中并再尝试
//			while (!head.compare_exchange_weak(new_node->next, new_node,
//				std::memory_order_release,
//				std::memory_order_relaxed))
//				; // 循环体为空
//		}
//	};
//}
//namespace lock
//{
//	template<typename T>
//	class stack
//	{
//	public:
//		node<T>* head = nullptr;
//		void push(const T& data)
//		{
//			node<T>* new_node = new node<T>(data);
//			new_node->next = head;
//			head = new_node;
//		}
//	};
//}
//int main()
//{
//	lock_free::stack<int> st1;
//	lock::stack<int> st2;
//	std::mutex mtx;
//	int n = 1000000;
//	auto lock_free_stack = [&st1, n] {
//		for (size_t i = 0; i < n; i++)
//		{
//			st1.push(i);
//		}
//		};
//	auto lock_stack = [&st2, &mtx, n] {
//		for (size_t i = 0; i < n; i++)
//		{
//			std::lock_guard<std::mutex> lock(mtx);
//			st2.push(i);
//		}
//		};
//	// 4个线程分别使⽤⽆锁⽅式和有锁⽅式插⼊n个数据到栈中对⽐性能
//	size_t begin1 = clock();
//	std::vector<std::thread> threads1;
//	for (size_t i = 0; i < 4; i++)
//	{
//		threads1.emplace_back(lock_free_stack);
//	}
//	for (auto& th : threads1)
//		th.join();
//	size_t end1 = clock();
//	std::cout << end1 - begin1 << std::endl;
//	size_t begin2 = clock();
//	std::vector<std::thread> threads2;
//	for (size_t i = 0; i < 4; i++)
//	{
//		threads2.emplace_back(lock_stack);
//	}
//	for (auto& th : threads2)
//		th.join();
//	size_t end2 = clock();
//
//	std::cout << end2 - begin2 << std::endl;
//	return 0;
//}

//#include <atomic>
//#include <thread>
//#include <iostream>
//#include <vector>
//// ⾃旋锁（SpinLock）是⼀种忙等待的锁机制，适⽤于锁持有时间⾮常短的场景。
//// 在多线程编程中，当⼀个线程尝试获取已被其他线程持有的锁时，⾃旋锁会让该
//// 线程在循环中不断检查锁是否可⽤，⽽不是进⼊睡眠状态。这种⽅式可以减少上
//// 下⽂切换的开销，但在锁竞争激烈或锁持有时间较⻓的情况下，会导致CPU资源的浪费。
//// 以下是使⽤C++11实现的⼀个简单⾃旋锁⽰例：
//class SpinLock
//{
//private:
//	// ATOMIC_FLAG_INIT默认初始化为false
//	std::atomic_flag flag = ATOMIC_FLAG_INIT;
//public:
//	void lock()
//	{
//		// test_and_set将内部值设置为true，并且返回之前的值
//		// 第⼀个进来的线程将值原⼦的设置为true，返回false
//		// 后⾯进来的线程将原⼦的值设置为true，返回true，所以卡在这⾥空转，
//		// 直到第⼀个进去的线程unlock，clear，将值设置为false
//		while (flag.test_and_set(std::memory_order_acquire));
//	}
//	void unlock()
//	{
//		// clear将值原⼦的设置为false
//		flag.clear(std::memory_order_release);
//	}
//};
//// 测试⾃旋锁
//void worker(SpinLock& lock, int& sharedValue) {
//	lock.lock();
//	// 模拟⼀些⼯作
//	for (int i = 0; i < 1000000; ++i) {
//		++sharedValue;
//	}
//	lock.unlock();
//}
//#include <atomic>
//#include <thread>
//#include <iostream>
//#include <vector>
//// ⾃旋锁（SpinLock）是⼀种忙等待的锁机制，适⽤于锁持有时间⾮常短的场景。
//// 在多线程编程中，当⼀个线程尝试获取已被其他线程持有的锁时，⾃旋锁会让该
//// 线程在循环中不断检查锁是否可⽤，⽽不是进⼊睡眠状态。这种⽅式可以减少上
//// 下⽂切换的开销，但在锁竞争激烈或锁持有时间较⻓的情况下，会导致CPU资源的浪费。
//// 以下是使⽤C++11实现的⼀个简单⾃旋锁⽰例：
//class SpinLock
//{
//private:
// // ATOMIC_FLAG_INIT默认初始化为false
// std::atomic_flag flag = ATOMIC_FLAG_INIT;
//public:
// void lock() 
// {
// // test_and_set将内部值设置为true，并且返回之前的值
// // 第⼀个进来的线程将值原⼦的设置为true，返回false
// // 后⾯进来的线程将原⼦的值设置为true，返回true，所以卡在这⾥空转，
// // 直到第⼀个进去的线程unlock，clear，将值设置为false
// while (flag.test_and_set(std::memory_order_acquire));
// }
// void unlock()
// {
// // clear将值原⼦的设置为false
// flag.clear(std::memory_order_release);
// }
//};
//// 测试⾃旋锁
//void worker(SpinLock& lock, int& sharedValue) {
//	 lock.lock();
//	 // 模拟⼀些⼯作
//	 for (int i = 0; i < 1000000; ++i) {
//	 ++sharedValue;
//	 }
//	 lock.unlock();
//}
//int main() {
//	SpinLock lock;
//	int sharedValue = 0;
//	std::vector<std::thread> threads;
//	// 创建多个线程
//	for (int i = 0; i < 4; ++i) {
//		threads.emplace_back(worker, std::ref(lock), std::ref(sharedValue));
//	}
//	// 等待所有线程完成
//	for (auto& thread : threads) {
//		thread.join();
//	}
//	std::cout << "Final shared value: " << sharedValue << std::endl;
//	return 0;
//}

//// condition_variable::notify_all
//#include <iostream> // std::cout
//#include <thread> // std::thread
//#include <mutex> // std::mutex, std::unique_lock
//#include <condition_variable> // std::condition_variable
//std::mutex mtx;
//std::condition_variable cv;
//bool ready = false;
//void print_id(int id) {
//	std::unique_lock<std::mutex> lck(mtx);
//	while (!ready)
//		cv.wait(lck);
//	// ...
//	std::cout << "thread " << id << '\n';
//}
//void go() {
//	std::unique_lock<std::mutex> lck(mtx);
//	ready = true;
//
//	// 通知所有阻塞在条件变量上的线程
//	cv.notify_all();
//}
//int main()
//{
//	std::thread threads[10];
//	// spawn 10 threads:
//	for (int i = 0; i < 10; ++i)
//		threads[i] = std::thread(print_id, i);
//	std::cout << "10 threads ready to race...\n";
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	go(); // go!
//	for (auto& th : threads)
//		th.join();
//	return 0;
//}

// 下⾯演⽰⼀个经典问题，两个线程交替打印奇数和偶数
#include <iostream> // std::cout
#include <thread> // std::thread
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
using namespace std;
int main()
{
	std::mutex mtx;
	condition_variable c;
	int n = 100;
	bool flag = true;
	// 第⼀个打印的是t1打印0
	thread t1([&]() {
		int i = 0;
		while (i < n)
		{
			unique_lock<mutex> lock(mtx);
			// flag == false t1⼀直阻塞
			// flag == true t1不会阻塞
			while (!flag)
			{
				c.wait(lock);
			}
			cout << i << endl;
			flag = false;
			i += 2; // 偶数
			c.notify_one();
		}
		});
	// this_thread::sleep_for(std::chrono::milliseconds(3000));
	thread t2([&]() {
		int j = 1;
		while (j < n)
		{
			unique_lock<mutex> lock(mtx);
			// 只要flag == true t2⼀直阻塞
			// 只要flag == false t2不会阻塞
			while (flag)
				c.wait(lock);
			cout << j << endl;
			j += 2; // 奇数
			flag = true;
			c.notify_one();
		}
		});
	t1.join();
	t2.join();
	return 0;
}