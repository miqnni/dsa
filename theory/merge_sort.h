#pragma once

#include <iostream>
#include <vector>
#include <functional> // std::function
#include <iterator> // std::distance, std::next

class MergeSort
{
//private:
//	void pv(std::vector<int> &v)
//	{
//		if (v.empty())
//		{
//			std::cout << "[]";
//			return;
//		}
//
//		// If vector is not empty.
//		std::cout << "[" << v[0];
//		for (int i{ 1 }; i < v.size(); i++)
//		{
//			std::cout << ", " << v[i];
//		}
//		std::cout << "]";
//	}

public:
	// TODO:
	// - Use GitHub
	// - Java implementation (download intelliJ) + repository `dsa-java`
	// - Use templates in order to be able
	// to sort vectors with ANY type of data that
	// has an overloaded operator <=.
	// - Overload (OR maybe use templates?) the function `sort()` so that
	// it can take different containers, not just
	// vectors.
	std::vector<int> &sort(std::vector<int> &nums, std::function<bool(int, int)> op = 
		[](int a, int b)
		{
			return a <= b;
		}
	)
	{
		size_t n{ nums.size() };

		if (n < 2)
		{
			return nums;
		};
		
		// if n >= 2
		// Split the vector into two parts.
		std::vector<int> vleft{ nums.begin(), nums.begin() + n/2};
		std::vector<int> vright{ nums.begin() + n/2, nums.end()};
		std::vector<int> vmerged{};

		// Sort both parts recursively.
		sort(vleft, op);
		sort(vright, op);

		// Merge two vectors `vleft` and `vright` after sorting them.
		std::vector<int>::iterator il{ vleft.begin() }, ir{vright.begin()};
		while (il != vleft.end() && ir != vright.end())
		{
			if (op(*il, *ir)) // with default argument: if(*il <= *ir)
			{
				vmerged.push_back(*il);
				il++;
				continue;
			}

			vmerged.push_back(*ir);
			ir++;
		}
		if (il != vleft.end())
		{
			// This means the `while` loop above ended because of
			// reaching the end of `vright`.
			// Move the contents of the remaining `vleft` elements to the
			// result vector `vmerged`.
			vmerged.insert(
				vmerged.end(),
				std::make_move_iterator(il),
				std::make_move_iterator(vleft.end())
			);
			nums = std::move(vmerged);
			return nums;
		}
		// (else) if ir != vleft.end()
		vmerged.insert(
			vmerged.end(),
			std::make_move_iterator(ir),
			std::make_move_iterator(vright.end())
		);
		nums = std::move(vmerged);
		return nums;
	}

	void sort(const std::vector<int>::iterator iStart, const std::vector<int>::iterator iEnd, const std::function<bool(int, int)> op =
		[](int a, int b)
		{
			return a <= b;
		}
	)
	{
		ptrdiff_t n{ std::distance(iStart, iEnd)};
		// OR:
		//auto n{ std::distance(iStart, iEnd)};

		if (n < 2)
		{
			return;
		};

		// if n >= 2
		// Split the vector into two parts.		
		std::vector<int>::iterator leftStart{iStart};
		std::vector<int>::iterator leftEnd{ std::next(iStart, n / 2) };
		std::vector<int>::iterator rightStart{ std::next(iStart, n / 2) };
		std::vector<int>::iterator rightEnd{iEnd};

		// Sort both parts recursively.
		sort(leftStart, leftEnd, op);
		sort(rightStart, rightEnd, op);


		// Merge two (sorted) parts of the original vector
		// into one (local, temporary) vector.
		std::vector<int> merged{};
		std::vector<int>::iterator il{ leftStart }, ir{ rightStart };
		while (il != leftEnd && ir != rightEnd)
		{
			if (op(*il, *ir)) // With default argument: if(*il <= *ir)
			{
				merged.push_back(*il);
				il++;
				continue;
			}

			merged.push_back(*ir);
			ir++;
		}
		while (il != leftEnd)
		{
			merged.push_back(*il);
			il++;
		}
		while (ir != rightEnd)
		{
			merged.push_back(*ir);
			ir++;
		}
		
		// Move the contents of the temporary `merged` vector
		// to the original vector using iterators.
		size_t mergedIdx{};
		for (std::vector<int>::iterator iOrig{ iStart }; iOrig != iEnd; iOrig++)
		{
			*iOrig = std::move(merged[mergedIdx]);
			mergedIdx++;
		}

		return;
	}
};