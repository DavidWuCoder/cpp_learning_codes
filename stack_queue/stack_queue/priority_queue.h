#pragma once


#include <vector>

namespace wyl
{
	template<class T>
	struct less {
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	template<class T>
	struct greater {
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};

	template<class T, class Container = std::vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		// 强制生成默认构造
		priority_queue() = default;

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first, last)
		{
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0;  i--)
			{
				Adjustdown(i);
			}
		}

		void Adjustup(int child)
		{
			Compare com;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (_con[parent] < _con[child])
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (parent - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			Adjustup(_con.size() - 1);
		}

		void Adjustdown(int parent)
		{
			Compare com;
			int child = parent * 2 + 1;
			while (child < _con.size())
			{
				/*if (child + 1 < _con.size() && _con[child + 1] > _con[child])*/
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					child++;
				}

				/*if ( _con[parent] < _con[child])*/
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			Adjustdown(0);
		}

		bool empty()
		{
			return _con.empty();
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

	private:
		Container _con;
	};


}