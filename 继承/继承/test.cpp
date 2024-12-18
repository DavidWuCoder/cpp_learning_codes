////#define _CRT_SECURE_NO_WARNINGS
////
////#include <iostream>
////using namespace std;
////
////// 实例演⽰三种继承关系下基类成员的各类型成员访问关系的变化
////class Person
////{
////public:
////	void Print()
////	{
////		cout << _name << endl;
////	}
////protected:
////	string _name = "zhangsan"; // 姓名
////private:
////	int _age; // 年龄
////};
////
////class student : public Person
////{
////	
////};
////
////int main()
////{
////	return 0;
////}
//
//#include <vector>
//#include <iostream>
//#include <list>
//
//template<class T>
//class stack : public std::vector<T>
//{
//public:
//	void push(const T& x)
//	{
//		std::vector<T>::push_back(x);
//
//	}
//	void pop()
//	{
//		std::vector<T>::pop_back();
//	}
//
//	const T& top()
//	{
//		return std::vector<T>::back();
//	}
//
//	bool empty()
//	{
//		return std::vector<T>::empty();
//	}
//};
//
//template<class Container>
//void print(const Container& c)
//{
//	typename Container::const_iterator it = c.begin();
//	while (it != c.end())
//	{
//		std::cout << *it << std::endl;
//		++it;
//	}
//	std::cout << std::endl;
//}
//
//int main()
//{
//	/*stack<int> st;
//	st.push(1);
//	st.push(2);
//	st.push(3);
//
//	while (!st.empty())
//	{
//		auto t = st.top();
//		st.pop();
//		std::cout << t << ' ';
//	}
//	std::cout << std::endl;*/
//
//
//	std::vector<int> v = { 1, 2, 3, 4, 5 };
//	std::list<int> l = { 1, 12, 13, 123 };
//
//	print<std::vector<int>>(v);
//	return 0;
//}
#include <iostream>
using namespace std;


class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{

			cout << "Person()" << endl;
	}
	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}
	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}
	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	string _name; // 姓名
};
//class Student : public Person
//{
//public:
//	Student(const char* name, int num)
//		:_num(num)
//		,Person(name)
//	{
//		cout << "Student()" << endl;
//	}
//
//	Student(const Student& s)
//		:Person(s)
//		,_num(s._num)
//	{
//		cout << "Student(const Student& s)" << endl;
//	}
//
//	Student& operator=(const Student& s)
//	{
//		cout << "Student& operator= (const Student& s)" << endl;
//		if (this != &s)
//		{
//			_num = s._num;
//			Person::operator=(s);
//		}
//		return *this;
//	}
//
//	~Student()
//	{
//		// 不需要显式地写
//		//Person::~Person();
//		std::cout << "~Student()" << std::endl;
//	}
//protected:
//	int _num; //学号
//};
//int main()
//{
//	Student s1("jack", 18);
//	Student s2(s1);
//	Student s3("rose", 17);
//	s1 = s3;
//	
//
//	
//	return 0;
//}
#include <iostream>
using namespace std;

//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//
//class Student : public Person
//{
//protected:
//	int _stuNum; // 学号
//};
//
//
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//int main()
//{
//	Person p;
//	Student s;
//	// 编译报错：error C2248: “Student::_stuNum”: ⽆法访问 protected 成员
//	// 解决⽅案：Display也变成Student 的友元即可
//	Display(p, s);
//	return 0;
//}

//class Person
//{
//public:
//	string _name;
//	static int _count;
//};
//
//int Person::_count = 0;
//class Student : public Person
//{
//protected:
//	int _stuNum;
//};
//
//int main()
//{
//	Person p;
//	Student s;
//	// 这⾥的运⾏结果可以看到⾮静态成员_name的地址是不⼀样的
//	// 说明派⽣类继承下来了，⽗派⽣类对象各有⼀份
//	cout << &p._name << endl;
//	cout << &s._name << endl;
//	// 这⾥的运⾏结果可以看到静态成员_count的地址是⼀样的
//	// 说明派⽣类和基类共⽤同⼀份静态成员
//	cout << &p._count << endl;
//	cout << &s._count << endl;
//	// 公有的情况下，⽗派⽣类指定类域都可以访问静态成员
//	cout << Person::_count << endl;
//	cout << Student::_count << endl;
//
//
//
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name)
//		:_name(name)
//	{}
//	string _name; // 姓名
//};
//
//
//class Student : virtual public Person
//{
//public:
//	Student(const char* name, int num)
//		:Person(name)
//		, _num(num)
//	{}
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//public:
//	Teacher(const char* name, int id)
//		:Person(name)
//		, _id(id)
//	{}
//protected:
//	int _id; // 职⼯编号
//};
//// 不要去玩菱形继承
//class Assistant : public Student, public Teacher
//{
//public:
//	Assistant(const char* name1, const char* name2, const char* name3)
//		:Person(name3)
//		, Student(name1, 1)
//		, Teacher(name2, 2)
//	{}
//protected:
//	string _majorCourse; // 主修课程
//};
//int main()
//{
//	// 思考⼀下这⾥a对象中_name是"张三", "李四", "王五"中的哪⼀个？
//	Assistant a("张三", "李四", "王五");
//	return 0;
//}


//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//
//
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//};
//
//void Func(Person* ptr)
//{
//	// 这⾥可以看到虽然都是Person指针Ptr在调⽤BuyTicket
//	// 但是跟ptr没关系，⽽是由ptr指向的对象决定的。
//	ptr->BuyTicket();
//}
//int main()
//{
//	Person ps;
//	Student st;
//
//	ps.BuyTicket();
//	st.BuyTicket();
//
//	Func(&ps);
//	Func(&st);
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//class B : public A
//{
//public:
//	virtual void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	return 0;
//}


#include <iostream>
using namespace std;

//class Base {
//public:
//    virtual void show() { cout << "Base::show" << endl; }
//};
//
//class Derived : public Base {
//public:
//    void show() override { cout << "Derived::show" << endl; }
//};
//
//int main() {
//    Base base;
//    Derived derived;
//
//    // 通过对象直接调用
//    base.show(); // 调用 Base::show
//    derived.show(); // 调用 Derived::show
//
//    // 通过基类指针调用
//    Base* pBase = &base;
//    pBase->show(); // 调用 Base::show
//
//    pBase = &derived;
//    pBase->show(); // 调用 Derived::show，多态性
//
//    // 通过基类引用调用
//    Base& refBase = base;
//    refBase.show(); // 调用 Base::show
//
//    Base& refDerived = derived;
//    refDerived.show(); // 调用 Derived::show，多态性
//
//    return 0;
//}

//class A
//{
//public:
//	virtual ~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//class B : public A {
//public:
//	~B()
//	{
//		cout << "~B()->delete:" << _p << endl;
//		delete _p;
//	}
//protected:
//	int* _p = new int[10];
//};
//// 只有派⽣类Student的析构函数重写了Person的析构函数，下⾯的delete对象调⽤析构函数，才能
//// 构成多态，才能保证p1和p2指向的对象正确的调⽤析构函数。
//int main()
//{
//	A* p1 = new A;
//	A* p2 = new B;
//	delete p1;
//	delete p2;
//	return 0;
//}


//class animal
//{
//public:
//	virtual void func()
//	{
//	}
//};
//
//class dog : public animal
//{
//public:
//	virtual void func()
//	{
//		std::cout << "汪汪" << std::endl;
//	}
//};
//
//class cat : public animal
//{
//public:
//	virtual void func()
//	{
//		std::cout << "喵喵" << std::endl;
//	}
//};
//
//void f(animal& p)
//{
//	p.func();
//
//}
//
//int main()
//{
//	cat a;
//	dog b;
//
//	f(a);
//	f(b);
//	return 0;
//}


class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
};
class Derive : public Base
{
public:
	// 重写基类的func1
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func1" << endl; }
	void func4() { cout << "Derive::func4" << endl; }
protected:
	int b = 2;
};
//int main()
//{
//	Base b;
//	Derive d;
//	return 0;
//}

int main()
{
	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);
	Base b;
	Derive d;
	Base* p3 = &b;
	Derive* p4 = &d;
	printf("Person虚表地址:%p\n", *(int*)p3);
	printf("Student虚表地址:%p\n", *(int*)p4);
	printf("虚函数地址:%p\n", &Base::func1);
	printf("普通函数地址:%p\n", &Base::func5);
	return 0;
}