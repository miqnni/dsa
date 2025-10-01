#include <vector> // std::vector<>
#include <stdexcept> // std::runctime_error
#include <functional> // std::function<>()

class Solution {
private:
    std::vector<int> dfsUnweightedList(std::vector<std::vector<int>>& adj) {
        // A recursive function that performs all the DFS-related processing logic or an unvisited node.
        static std::function<void(const int&, std::vector<std::vector<int>>&, std::vector<bool>&, std::vector<int>&)> dfsVisit = [&](const int& currNode, std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& path) {
            if (visited[currNode])
                throw std::runtime_error("You cannot visit a node more than once");

            visited[currNode] = true;
            path.push_back(currNode);

            // Iterate through all the nodes adjacent to the current one
            for (const int& neighbour : adj[currNode])
                // Visit any unvisited neighbours
                if (!visited[neighbour]) {
                    dfsVisit(neighbour, adj, visited, path);
                }
            };

        // --------------------------------

        const int n{ adj.size() };
        std::vector<bool> visited(n, false);
        std::vector<int> path{};

        // Iterate through all the nodes that haven't been visited yet
        for (int node{}; node < n; node++) {
            if (!visited[node]) {
                // Visiting an unvisited node
                dfsVisit(node, adj, visited, path);
            }
        }

        return path;
    }

    // TODO
    std::vector<int> dfsWeightedList(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> dfsUnweightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> dfsWeightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }


public:
    std::vector<int> dfs(std::vector<std::vector<int>>& adj) { // TODO: make it support other graphs (weighted, adj. matrix)
        return dfsUnweightedList(adj);
    }
};