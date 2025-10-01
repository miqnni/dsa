#include <vector> // std::vector<>
#include <queue> // std::queue<>

class Solution {
private:
    std::vector<int> bfsUnweightedList(std::vector<std::vector<int>>& adj) {
        int s{ 0 };
        int n{ static_cast<int>(adj.size()) };
        std::queue<int> q; // We'll be adding nodes there after visiting them for the first time
        std::vector<bool> visited(n, false);
        std::vector<int> reachedNodes;

        // Base
        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            // Take a node from the queue
            int currNode{ q.front() };
            q.pop();

            // Add the node to the reached nodes list.
            reachedNodes.push_back(currNode);

            // Add the adjacent nodes to the queue if they haven't been visited yet
            for (const int adjNode : adj[currNode]) {
                if (visited[adjNode])
                    continue;

                // Visit the node and add it to the queue
                visited[adjNode] = true;
                q.push(adjNode);
            }

        }

        return reachedNodes;

    }

    // TODO
    std::vector<int> bfsWeightedList(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> bfsUnweightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> bfsWeightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }

public:
    // Function to return Breadth First Traversal of given graph.
    std::vector<int> bfs(std::vector<std::vector<int>>& adj) {
        return bfsUnweightedList(adj);
    }
};