// LEETCODE 1143

#include <string> // std::string
#include <vector> // std::vector<>
#include <algorithm> // std::max()

class Solution {
public:
    int lcs(std::string& s1, std::string& s2) {
        int n1{ static_cast<int>(s1.size()) }, n2{ static_cast<int>(s2.size()) };
        std::vector<std::vector<int>> tab(
            s1.size() + 1,
            std::vector<int>(
                s2.size() + 1,
                0
            )
        );

        for (int i{ n1 - 1 }; i >= 0; i--) {
            for (int j{ n2 - 1 }; j >= 0; j--) {
                if (s1[i] == s2[j]) {
                    tab[i][j] = tab[i + 1][j + 1] + 1;
                    continue;
                }

                tab[i][j] = std::max(tab[i + 1][j], tab[i][j + 1]);
            }
        }

        return tab[0][0];
    }
};
