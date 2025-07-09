#include <vector>
#include <stdexcept>

// DFS of a graph represented by an Adjacency Matrix
class Solution {
private:
    /**
     * A recursive function that performs all the DFS-related processing logic
     * for an unvisited node.
     */
    void dfsVisit(const int &currNode, std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<int> &path) {
        if (visited[currNode])
            throw std::runtime_error("You cannot visit a node more than once");
        
        visited[currNode] = true;
        path.push_back(currNode);
        
        // Iterate through all the nodes adjacent to the current one
        for (const int &neighbour : adj[currNode])
            // Visit any unvisited neighbours
            if (!visited[neighbour]) {
                dfsVisit(neighbour, adj, visited, path);
            }
    }

public:
    std::vector<int> dfs(std::vector<std::vector<int>> &adj) {
        // Code here
        const int n{adj.size()};
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
};