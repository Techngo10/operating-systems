#include "mergesort.h"
#include <random>
#include <limits>
#include <span>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using usize = std::size_t;

inline int *A;
inline int *B;
inline int cutoff = 0;
int main()
{
	static constexpr auto array_sizes = []
	{
		std::array<usize, 14> sizes{};
		for (usize i = 0; i < sizes.size(); ++i)
			sizes[i] = usize{1} << (10 + i);
		return sizes;
	}();
	static constexpr std::size_t max_cutoff{7};//my zen4 has only 16core / 32threads
	static constexpr std::size_t repeat{8};
	std::chrono::steady_clock::duration result[max_cutoff+1][array_sizes.size()]{};

	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	std::vector<int> buffer(array_sizes.back() * 2);
	A = buffer.data();
	B = buffer.data() + array_sizes.back();
	for(usize iSize{}; iSize!=array_sizes.size(); ++iSize)
	{
		const std::size_t size{array_sizes[iSize]};
		const std::span<int> a{ A, size };
		const std::span<int> b{ B, size };
		for(auto i{repeat};i--;)
			for(cutoff = max_cutoff + 1; cutoff--;)
			{
				for(int& x: a)x = distrib(gen);
				auto* args{buildArgs(0, size-1, 0)};
				const auto start{ std::chrono::steady_clock::now() };
				parallel_mergesort(args);
				const auto end{ std::chrono::steady_clock::now() };
				result[cutoff][iSize] += (end-start);
				free(args);
			}
	}

	// total nanoseconds accumulated over `repeat` runs
	const auto total_ns{[&](usize cutoff, usize iSize)
	{
		return std::chrono::duration<double, std::nano>(result[cutoff][iSize]).count();
	}};
 
	const auto print_table = [&](std::string_view title, auto cell)
	{
		std::cout << "\n### " << title << "\n\n| " << title << " |";
		for (usize cutoff{}; cutoff <= max_cutoff; ++cutoff) std::cout << " cutoff=" << cutoff << " |";
		std::cout << "\n|---:|";
		for (usize cutoff{}; cutoff <= max_cutoff; ++cutoff) std::cout << "---:|";
		std::cout << '\n' << std::fixed << std::setprecision(3);
		for (usize iSize{}; iSize != array_sizes.size(); ++iSize)
		{
			std::cout << "| ints=" << array_sizes[iSize] << " |";
			for (usize cutoff{}; cutoff <= max_cutoff; ++cutoff) std::cout << ' ' << cell(cutoff, iSize) << " |";
			std::cout << '\n';
		}
	};
 
	print_table("Speed (ints/ms)", [&](usize cutoff, usize iSize)
	{
		return static_cast<double>(array_sizes[iSize] * repeat) / total_ns(cutoff, iSize) * 1000.;
	});
 
	print_table("Speedup", [&](usize cutoff, usize iSize)
	{
		return total_ns(0, iSize) / total_ns(cutoff, iSize);
	});
}
