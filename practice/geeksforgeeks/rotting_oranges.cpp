#include <vector> // std::vector<>
#include <utility> // std::pair<>
#include <queue> // std::queue<>

class Solution {
private:
    using xy = std::pair<int, int>;

public:
    int orangesRotting(std::vector<std::vector<int>>& mat) {
        int n{ static_cast<int>(mat.size()) };
        int m{ static_cast<int>(mat[0].size()) };

        int freshOranges{}, timeUnits{};

        std::queue<xy> q;
        // std::vector<std::vector<bool>> visited(
        //     n,
        //     std::vector<bool>(false, m)
        // );

        std::vector<xy> directions = {
            {-1, 0}, // up
            {0, 1}, // right
            {1, 0}, // down
            {0, -1} // left
        };

        // Pre-work
        for (int i{}; i < n; i++) {
            for (int j{}; j < m; j++) {
                switch (mat[i][j]) {
                case 1: // Fresh
                    freshOranges++;
                    break;
                case 2: // rotten
                    q.push({ i, j });
                default:
                    break;
                }
            }
        }

        while (!q.empty() && freshOranges > 0) {
            // Now we have a SNAPSHOT of the queue in the current time unit
            int savedQSize{ static_cast<int>(q.size()) };

            // Take all rotten oranges from the queue
            // and make the adjacent ones rotten.
            // This will be a single unit of time
            for (int ro{}; ro < savedQSize; ro++) {
                xy currXY{ q.front() };
                q.pop();

                for (const xy& direction : directions) {
                    int nextI{ currXY.first + direction.first }, nextJ{ currXY.second + direction.second };

                    if (nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= m || mat[nextI][nextJ] != 1)
                        continue; // Out of bounds or not fresh, so can't be made rotten

                    // Make rotten and add to queue
                    xy nextCell = { nextI, nextJ };
                    mat[nextI][nextJ] = 2;
                    freshOranges--;
                    q.push(nextCell);
                }
            }
            timeUnits++;
        }

        // Check if there are any fresh oranges left
        return freshOranges > 0 ? -1 : timeUnits;
    }
};