#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "treap.hpp"

std::vector<std::string> words;

double measure(std::function<void(void)> f)
{
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> t;

	t1 = std::chrono::high_resolution_clock::now();
	f();
	t2 = std::chrono::high_resolution_clock::now();

	t = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	return t.count() * 1000;
}

template <typename Container>
void benchmark(Container &container)
{
	const size_t LOOKUP_SIZE = 5000;
	double time;

	// Randomize insertion order.
	random_shuffle(words.begin(), words.end());

	// Measure insertion time.
	time = measure([&]() mutable { container.insert(words.begin(), words.end()); });
	std::cout << "  insertion time: " << time << " ms" << std::endl;

	// Randomize lookup order.
	random_shuffle(words.begin(), words.end());

	// Measure find time.
	time = measure([&]() mutable {
		for (size_t i = 0; i < LOOKUP_SIZE; i++)
		{
			container.find(words[i]);
		}
	});
	std::cout << "  find time: " << time << " ms" << std::endl;

	// Measure count time.
	time = measure([&]() mutable {
		for (size_t i = 0; i < LOOKUP_SIZE; i++)
		{
			container.count(words[i]);
		}
	});
	std::cout << "  count time: " << time << " ms" << std::endl;
}

/**
 * @note Nodes could be reused if using better allocator.
 * @note Key is identical to value.
 * @note Non-const iterators are protected to prevent key modification.
 * @note Priority of header node can be any value.
 * @note Issue DR 431 was unsolved until C++11.
 */
int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	// Read words.
	std::istream_iterator<std::string> begin(std::cin);
	std::istream_iterator<std::string> end;
	words.insert(words.begin(), begin, end);

	// Benchmark treap.
	polsl::treap<std::string> treap;
	std::cout << "Treap" << std::endl;
	benchmark(treap);

	// Benchmark set.
	std::set<std::string> set;
	std::cout << "Set" << std::endl;
	benchmark(set);

	// Benchmark unordered set.
	std::unordered_set<std::string> uset;
	std::cout << "Unordered set" << std::endl;
	benchmark(uset);

	return 0;
}
