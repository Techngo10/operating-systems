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

inline int *A;
inline int *B;
inline int cutoff = 0;
int main()
{
	cutoff = 3;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	for(std::size_t i{10000};i--;)
	{
        A = (int*)malloc(sizeof(int) * i);
        B = (int*)malloc(sizeof(int) * i);
        const std::span<int> a{ A, i };
        const std::span<int> b{ B, i };
		for(int& x: a)
			x = distrib(gen);
		std::vector<int> expected{a.begin(), a.end()};
		std::stable_sort(expected.begin(), expected.end());
		auto* args{buildArgs(0, i-1, 0)};
		parallel_mergesort(args);
		free(args);
		if(const std::span<int> e{expected.begin(), expected.end()}; !std::ranges::equal(a, expected))
		{
			std::cout << "fail\n";
			std::cout << a << '\n';
			std::cout << e << '\n';
		}
		free(A);
		free(B);
	}
	std::cout << "success\n";
}