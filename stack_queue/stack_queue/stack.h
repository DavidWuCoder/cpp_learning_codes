#pragma once

#include <deque>
//template<class T>
//class stack
//{
//private:
//	T* _a;
//	size_t _top;
//	size_t _capacity;
//};
namespace wyl
{
	template<class T, class Container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		const T& top() const
		{
			return _con.back();
		}

		const T& size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}