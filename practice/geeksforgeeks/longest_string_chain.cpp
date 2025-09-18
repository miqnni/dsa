// LEETCODE 1048

#include <vector> // std::vector<>
#include <string> // std::string 
#include <unordered_map> // std::unordered_map<>
// #include <iostream> // std::cout, std::endl
#include <algorithm> // std::max(), std::sort()
#include <unordered_set> // std::unordered_set<>

class Solution {
private:
    std::unordered_set<std::string> wordsSet;
    std::unordered_map<std::string, int> memo;

    int lcsInner(std::string chosenWord) {
        // Check if the solution for this subproblem (word)
        // does not already exist
        if (memo.find(chosenWord) != memo.end())
            return memo[chosenWord];

        int maxChainLen{ 1 }; // Trivial answer: {chosenWord}.length()

        // Generate the word's predecessors
        for (int removedCharIdx{}; removedCharIdx < chosenWord.length(); removedCharIdx++) {
            std::string predecessor{
                chosenWord.substr(0, removedCharIdx) + chosenWord.substr(removedCharIdx + 1)
            };

            // Check if the predecessor is inside the provided words list / vector
            if (wordsSet.find(predecessor) == wordsSet.end())
                continue;

            // Now that we know that the current predecessor is inside `words`,
            // run its own subproblem recursively
            maxChainLen = std::max(maxChainLen, 1 + lcsInner(predecessor));
        }

        memo[chosenWord] = maxChainLen;
        return maxChainLen;
    }

public:
    int longestStringChain(std::vector<std::string>& words) {
        wordsSet = std::unordered_set<std::string>(words.begin(), words.end());

        // Sort the words in order to start with the longest ones
        std::sort(words.begin(), words.end(),
            [](const std::string& wA, const std::string& wB) {
                return wA.size() < wB.size(); // Sort DESCENDING, hence `<` instead of `>`
            }
        );

        int maxAns{};

        for (const std::string& word : words) {
            maxAns = std::max(maxAns, lcsInner(word));
        }

        return maxAns;
    }
};