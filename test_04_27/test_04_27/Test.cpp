//#include <iostream>
#include "BitSet.h"
//using namespace std;
//
//int main()
//{
//	wyl::bit_set<100> bs;
//	bs.set(32);
//	bs.set(33);
//
//	bs.reset(33);
//	bs.set(34);
//
//	std::cout << bs.test(31) << std::endl;
//	std::cout << bs.test(32) << std::endl;
//	std::cout << bs.test(33) << std::endl;
//	std::cout << bs.test(34) << std::endl;
//
//	wyl::bit_set<-1> bs1;
//	wyl::bit_set<0xfffffff> bs2;
//	wyl::bit_set<UINT_MAX> bs3;
//	return 0;
//}

#include <iostream>
#include <bitset>
using namespace std;

//int main()
//{
//	std::cout << sizeof(std::vector<int>);
//	return 0;
// }

#include "BloomFilter.h"

int main()
{
	//std::vector<double> v{ 1, 2, 3 };
	//std::cout << v.size() << std::endl;         // ���3��Ԫ������)
	//std::cout << sizeof(v);        // ��Ϊ24�����������С��
	//wyl::TestBloom1();
	wyl::TestBloomFilter2();

	return 0;
}