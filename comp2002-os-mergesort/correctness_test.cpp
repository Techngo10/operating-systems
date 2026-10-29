#include "mergesort.h"
#include <random>
#include <limits>
#include <span>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
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
	static constexpr std::size_t max_array_size{10000};
	static constexpr std::size_t max_cutoff{5};

	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	std::vector<int> buffer(max_array_size * 3);
	A = buffer.data();
	B = buffer.data() + max_array_size;
	int* pExpected{ buffer.data() + max_array_size * 2 };
	for(std::size_t i{max_array_size + 1};i--;)
	{
		const std::span<int> a{ A, i };
		const std::span<int> b{ B, i };
		const std::span<int> e{ pExpected, i };
		for(cutoff = max_cutoff + 1; cutoff--;)
		{
			int* pE{ pExpected };
			for(int& x: a)
			{
				x = distrib(gen);
				*pE++ = x;
			}
			auto* args{buildArgs(0, static_cast<int>(i)-1, 0)};
			parallel_mergesort(args);
			free(args);
			std::sort(e.begin(), e.end());
			if(!std::ranges::equal(a, e))[[unlikely]]
			{
				std::cout << "fail\n";
				std::cout << a << '\n';
				std::cout << e << '\n';
				return EXIT_FAILURE;
			}
		}
	}
	std::cout << "success\n";
}
