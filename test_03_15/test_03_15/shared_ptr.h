#pragma once
#include <functional>

namespace wyl
{
	template<class T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pcount(new int(1))
		{}

		template<class D>
		shared_ptr(T* ptr, D del)
			: _ptr(ptr)
			, _pcount(new int(1))
			, _del(del)
		{}

		
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _del(sp._del)
		{
			++(*_pcount);
		}

		void release()
		{
			if (--*(_pcount) == 0)
			{
				//delete _ptr;
				_del(_ptr);
				delete _pcount;

				_ptr = nullptr;
				_pcount = nullptr;
			}
		}

		shared_ptr& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				release();
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				++(*_pcount);
			}
			return *this;
		}

		int use_count() const
		{
			return *_pcount;
		}

		~shared_ptr()
		{
			release();
		}

		operator bool()
		{
			return _ptr != nullptr;
		}

	private:
		T* _ptr;
		
		int* _pcount;

		std::function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};
}
