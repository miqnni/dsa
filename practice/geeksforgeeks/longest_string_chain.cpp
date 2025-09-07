// TODO: Optimise in order to avoid Time Limit Exceeded.
// For instance, generate possible predecessors in order to check all words in the words array / vector.

#include <vector> // std::vector
#include <string> // std::string 
#include <unordered_map> // std::unordered_map
#include <iostream> // std::cout, std::endl
#include <algorithm> // std::max

class Solution {
    bool isPredecessor(std::string shorterWord, std::string longerWord) {
        if (shorterWord.length() != longerWord.length() - 1)
            return false;

        for (int i{}; i < longerWord.length(); i++) {
            std::string longerWordWithoutLetter{ longerWord.substr(0, i) + longerWord.substr(i + 1) };
            // std::cout << longerWordWithoutLetter << std::endl;
            if (longerWordWithoutLetter == shorterWord)
                return true;
        }
        return false;
    }

    int longestStringChainMemoInner(std::vector<std::string>& words, std::unordered_map<std::string, int>& memo, std::string currWord) {
        // Check if the subproblem has not been already solved.
        std::unordered_map<std::string, int>::iterator foundResult{ memo.find(currWord) };
        if (foundResult != memo.end())
            return foundResult->second;

        // Base case
        if (currWord.length() == 1) {
            memo[currWord] = 1;
            return 1;
        }

        int maxChainLength{};
        for (const std::string& word : words) {
            if (isPredecessor(word, currWord)) {
                maxChainLength = std::max(
                    maxChainLength,
                    1 + longestStringChainMemoInner(words, memo, word)
                );
            }
        }
        return maxChainLength;

        // Find the maximum recursion depth for the current word.

    }

    int longestStringChainMemoOuter(std::vector<std::string>& words) {
        std::unordered_map<std::string, int> memo;
        int maxVal{ 1 };
        for (const std::string& word : words) {
            maxVal = std::max(maxVal, longestStringChainMemoInner(words, memo, word));
        }
        return maxVal;
    }
public:
    int longestStringChain(std::vector<std::string>& words) {

        return longestStringChainMemoOuter(words);
    }
};

// ********************************

void driver() {
    Solution sol;
    std::vector<std::string> vin({
        "ba", "b", "a", "bca", "bda", "bdca" // 4
        // "abc", "a", "ab" // 3
        // "abcd", "dbqca" // 1
        });
    std::cout << "OUTPUT: " << sol.longestStringChain(vin) << std::endl;
}