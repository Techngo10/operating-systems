#include "mergesort.h"
#include <random>
#include <limits>
#include <span>
#include <algorithm>
#include <iostream>
auto& operator<<(auto& stream, std::span<int>const&arr)
{
	for(const int x: arr)
	{
		if(&x != arr.data())stream.put(',');
		stream << x;
	}
	return stream;
}

int *A;
int *B;
int cutoff = 0;
int main()
{
	cutoff = 3;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	for(std::size_t i{100};i--;)
	{
        A = (int*)malloc(sizeof(int) * i);
        B = (int*)malloc(sizeof(int) * i);
        const std::span<int> a{ A, i };
        const std::span<int> b{ B, i };
		for(int& x: a)
			x = distrib(gen);
		std::vector<int> cpy{a.begin(), a.end()};
		std::stable_sort(cpy.begin(), cpy.end());
		// parallel_mergesort_impl(arr.data(), buf.data(), i, cutoff);
		// if(arr != cpy)
		// {
		// 	std::cout << "fail\n";
		// 	std::cout << arr<< '\n';
		// 	std::cout << cpy<< '\n';
		// }
	}
	std::cout << "success\n";
}