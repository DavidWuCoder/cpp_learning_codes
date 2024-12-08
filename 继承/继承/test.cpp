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
//#include <iostream>
//using namespace std;
//
//
//class Person
//{
//public:
//	Person(const char* name = "peter")
//		: _name(name)
//	{
//
//			cout << "Person()" << endl;
//	}
//	Person(const Person& p)
//		: _name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//	Person& operator=(const Person& p)
//	{
//		cout << "Person operator=(const Person& p)" << endl;
//		if (this != &p)
//			_name = p._name;
//		return *this;
//	}
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
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

class Person
{
public:
	Person(const char* name)
		:_name(name)
	{}
	string _name; // 姓名
};
class Student : virtual public Person
{
public:
	Student(const char* name, int num)
		:Person(name)
		, _num(num)
	{}
protected:
	int _num; //学号
};
class Teacher : virtual public Person
{
public:
	Teacher(const char* name, int id)
		:Person(name)
		, _id(id)
	{}
protected:
	int _id; // 职⼯编号
};
// 不要去玩菱形继承
class Assistant : public Student, public Teacher
{
public:
	Assistant(const char* name1, const char* name2, const char* name3)
		:Person(name3)
		, Student(name1, 1)
		, Teacher(name2, 2)
	{}
protected:
	string _majorCourse; // 主修课程
};
int main()
{
	// 思考⼀下这⾥a对象中_name是"张三", "李四", "王五"中的哪⼀个？
	Assistant a("张三", "李四", "王五");
	return 0;
}