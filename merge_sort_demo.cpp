#include <iostream>

#include "merge_sort.h"

int main()
{
	std::cout << "Algo" << std::endl;

	MergeSort ms;
	std::vector<int> a{2, 1, 3, 7, 1, 3, 3, 7};
	ms.sort(a);
	//ms.sort(a.begin(), a.end(), [](int a, int b) { return a > b; });
	//ms.sort(a.begin(), a.end());

	for (const auto& el : a)
		std::cout << el << ", ";
	
	std::cout << std::endl;

	return 0;
}
