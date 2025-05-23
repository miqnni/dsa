#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // SOLUTION 1: Brute-Force
        // for (int i = 0; i < nums.size(); i++) {
        //     for (int j = i + 1; j < nums.size(); j++) {
        //         if (nums[i] + nums[j] == target) {
        //             return vector<int>{i, j};
        //         }
        //     }
        // }

        // return vector<int>{-1, -1};

        // SOLUTION 2: Two-Pass Hash Table
        // std::map<int, int> valIdx;
        // for (int i{}; i < nums.size(); i++)
        //     valIdx[nums[i]] = i;

        // for (int i{}; i < nums.size(); i++)
        // {
        //     int remaining{target - nums[i]};
        //     int soughtIndex{-1};
        //     if (valIdx.count(remaining) && (soughtIndex = valIdx[remaining]) != i)
        //         return vector<int>{i, soughtIndex};
        // }

        // return vector<int>{-1, -1};

        // SOLUTION 3: Two-Pass Hash Table
        std::map<int, int> valIdx;
        for (int i{}; i < nums.size(); i++)
        {
            int remaining{ target - nums[i] };
            if (valIdx.count(remaining))
                return { valIdx[remaining], i };
            valIdx[nums[i]] = i;
        }

        return std::vector<int>{-1, -1};
    }
};
