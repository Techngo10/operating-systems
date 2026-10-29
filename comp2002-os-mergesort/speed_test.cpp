#include "mergesort.h"
#include <random>
#include <limits>
#include <span>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>

using usize = std::size_t;

inline int *A;
inline int *B;
inline int cutoff = 0;
int main()
{
    static constexpr std::array array_sizes{ []<usize...I>(std::index_sequence<I...>)static
    {
        return std::array<usize, sizeof...(I)>{ (usize{1}<<(10+I))... };
    }(std::make_index_sequence<14>{}) };
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
    for(usize iSize{}; iSize!=array_sizes.size(); ++iSize)
	{
        const std::size_t size{array_sizes[iSize]};
        const auto speed_serial{ result[0][iSize]/double(repeat*size) };
        for(usize cutoff{}; cutoff <= max_cutoff; ++cutoff)
        {
            const auto speed{ result[cutoff][iSize]/double(repeat*size) };
            std::cout << "size = " << size << ", cutoff = " << cutoff << ", speed (time/int) = " << speed << ", speedup = " << speed_serial/speed << '\n';
        }
    }
}