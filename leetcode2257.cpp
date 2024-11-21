#include <iostream>
#include <string>
#include <vector>
#include <map>

class Solution {
private:
    void printGrid(const std::vector<std::vector<int>>& grid) {
        size_t m = grid.size();
        size_t n = grid[0].size();
        for (int i{}; i < m; i++) {
            for (int j{}; j < n; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    enum TileState {
        Free = 0,
        HasGuard = 1,
        HasWall = 2,
        GuardedUp = 3,
        GuardedDown = 4,
        GuardedRight = 5,
        GuardedLeft = 6,
    };

public:
    int countUnguarded(int m, int n, std::vector<std::vector<int>>& guards, std::vector<std::vector<int>>& walls) {

        // 0 -- nothing
        // 1 -- is guarded
        // 2 -- has guard
        // 3 -- has wall
        std::vector<std::vector<TileState>> grid(
            m,
            std::vector<TileState>(n)
        );
        for (int i{}; i < m; i++) {
            for (int j{}; j < n; j++) {
                grid[i][j] = Free;
            }
        }

        for (const auto& wall : walls) {
            int wallPosI{ wall[0] };
            int wallPosJ{ wall[1] };

            grid[wallPosI][wallPosJ] = HasWall;
        }

        for (const auto& guard : guards) {
            int guardPosI{ guard[0] };
            int guardPosJ{ guard[1] };

            grid[guardPosI][guardPosJ] = HasGuard;

            // up
            for (int i{ guardPosI - 1 }; i >= 0; i--) {
                if (grid[i][guardPosJ] == HasGuard || grid[i][guardPosJ] == HasWall || grid[i][guardPosJ] == GuardedDown)
                    break;
                grid[i][guardPosJ] = GuardedUp;
            }

            // down
            for (int i{ guardPosI + 1 }; i < m; i++) {
                if (grid[i][guardPosJ] == HasGuard || grid[i][guardPosJ] == HasWall || grid[i][guardPosJ] == GuardedUp)
                    break;
                grid[i][guardPosJ] = GuardedDown;
            }

            // left
            for (int j{ guardPosJ - 1 }; j >= 0; j--) {
                if (grid[guardPosI][j] == HasGuard || grid[guardPosI][j] == HasWall || grid[guardPosI][guardPosJ] == GuardedRight)
                    break;
                grid[guardPosI][j] = GuardedLeft;
            }

            // right
            for (int j{ guardPosJ + 1 }; j < n; j++) {
                if (grid[guardPosI][j] == HasGuard || grid[guardPosI][j] == HasWall || grid[guardPosI][j] == GuardedLeft)
                    break;
                grid[guardPosI][j] = GuardedRight;
            }

        }

        int freeCount{};
        for (int i{}; i < m; i++) {
            for (int j{}; j < n; j++) {
                if (grid[i][j] == Free)
                    freeCount++;
            }
        }

        // printGrid(grid);

        return freeCount;

    }
};