#pragma once
#include <vector>

namespace wyl
{
	template<size_t N>
	class bit_set
	{
	public:
		bit_set()
		{
			_bs.resize(N / 32 + 1);

		}

		// x映射的位标记为1
		void set(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] |= (1 << j);
		}

		// x映射的位标记成0
		void reset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] &= ~(1 << j);
		}

		// 检查x是否标记为1
		bool test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			//  1 0r 0
			return _bs[i] & (1 << j);
		}

	private:
		std::vector<size_t> _bs;
	};

	//template<size_t N>
	//class twobitset
	//{
	//public:
	//	void set(size_t x)
	//	{
	//		bool bit1 = _bs1.test(x);
	//		bool bit2 = _bs2.test(x);

	//		if (!bit1 && !bit2)
	//		{
	//			_bs2.set(x);
	//		}
	//		else if (!bit1 && bit2)
	//		{
	//			_bs1.set(x);
	//			_bs2.reset(x);
	//		}
	//		else if (bit1 && !bit2)
	//		{
	//			_bs2.set(x);
	//		}
	//	}

	//private:
	//	bitset<N> _bs1;
	//	bitset<N> _bs2;
	//};
}
