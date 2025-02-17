#include <iostream>
#include <thread>
using namespace std;

//double Divide(int a, int b)
//{
//	try
//	{
//		// 当b == 0时抛出异常
//		if (b == 0)
//		{
//			string s("Divide by zero condition!");
//			throw s;
//		}
//		else
//		{
//			return ((double)a / (double)b);
//		}
//	}
//	catch (int errid)
//	{
//		cout << errid << endl;
//	}
//	return 0;
//}
//
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	try
//	{
//		cout << Divide(len, time) << endl;
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	cout << __FUNCTION__ << ":" << __LINE__ << "?执?" << endl;
//}

class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{}
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
	{}
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
	{}
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
	{}
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
		throw SqlException("权限不?", 100, "select * from name = '张三'");
	}
	else
	{
		cout << "SQLMgr 调?成功" << endl;
	}
}

void CacheMgr()
{
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不?", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	else
	{
		cout << "CacheMgr 调?成功" << endl;
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
		throw HttpException("权限不?", 101, "post");
	}
	else
	{
		cout << "HttpServer调?成功" << endl;
	}
	CacheMgr();
}

void _SendMsg(const string& s)
{
	if (rand() % 2 == 0)
	{
		throw HttpException("⽹络不稳定，发送失败", 102, "put");
	}
	else if (rand() % 7 == 0)
	{
		throw HttpException("你已经不是对象的好友，发送失败", 103, "put");
	}
	else
	{
		cout << "发送成功" << endl;
	}
}

void SendMsg(const string& s)
{
	// 发送消息失败，则再重试3次
	for (size_t i = 0; i < 4; i++)
	{
		try
		{
			_SendMsg(s);
			break;
		}
		catch (const Exception& e)
		{
			// 捕获异常，if中是102号错误，⽹络不稳定，则重新发送
			// 捕获异常，else中不是102号错误，则将异常重新抛出
			if (e.getid() == 102)
			{
				// 重试三次以后否失败了，则说明⽹络太差了，重新抛出异常
				if (i == 3)
					throw;
				cout << "开始第" << i + 1 << "重试" << endl;
			}
			else
			{
				throw;
			}
		}
	}
}

int main()
{
	//srand(time(0));
	//while (1)
	//{
	//	this_thread::sleep_for(chrono::seconds(1));
	//	try
	//	{
	//		HttpServer();
	//	}
	//	catch (const Exception& e) // 这?捕获基类，基类对象和派?类对象都可以被
	//	{
	//		cout << e.what() << endl;
	//	}
	//	catch (...)
	//	{
	//		cout << "未知异常" << endl;
	//	}
	//}

	srand(time(0));
	string str;
	while (cin >> str)
	{
		try
		{
			SendMsg(str);
		}
		catch (const Exception& e)
		{
			cout << e.what() << endl << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}