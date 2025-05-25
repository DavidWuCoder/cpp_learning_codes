#include<thread>
#include <iostream>
#include <string>
using namespace std;

// ⼀般⼤型项⽬程序才会使⽤异常，下⾯我们模拟设计⼀个服务的⼏个模块
// 每个模块的继承都是Exception的派⽣类，每个模块可以添加⾃⼰的数据
// 最后捕获时，我们捕获基类就可以
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{
	}
	virtual string what() const
	{
		return _errmsg;
	}
	int getid() const
	{
		return _id;
	}
protected:
	string _errmsg;
	int _id;
};
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{
	}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};

class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{
	}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};
class HttpException : public Exception
{
public:
	HttpException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{
	}
	virtual string what() const
	{
		string str = "HttpException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};
void SQLMgr()
{
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不⾜", 100, "select * from name = '张三'");
	}
	else
	{
		cout << "SQLMgr 调⽤成功" << endl;
	}
}

void CacheMgr()
{
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不⾜", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	else
	{
		cout << "CacheMgr 调⽤成功" << endl;
	}
	SQLMgr();
}
void HttpServer()
{
	if (rand() % 3 == 0)
	{
		throw HttpException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpException("权限不⾜", 101, "post");
	}
	else
	{
		cout << "HttpServer调⽤成功" << endl;
	}
	CacheMgr();
}
int main()
{
	srand(time(0));
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(1));
		try
		{
 HttpServer();

		}
catch (const Exception& e) // 这⾥捕获基类，基类对象和派⽣类对象都可以被
			捕获
 {
 cout << e.what() << endl;
 }
 catch (...)
 {
 cout << "Unkown Exception" << endl;
 }
	}
 return 0;

}