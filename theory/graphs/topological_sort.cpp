#include <vector> // std::vector<>
#include <stdexcept> // std::runctime_error
#include <functional> // std::function<>()
#include <algorithm> // std::reverse

class Solution {
private:

    // Unweighted
    std::vector<std::vector<int>> edgeListToAdjList(std::vector<std::vector<int>>& edgeList, const int& n) {
        std::vector<std::vector<int>> adjList(
            n,
            std::vector<int>()
        );

        for (const std::vector<int>& edge : edgeList) {
            int v{ edge[0] }, adjV{ edge[1] };
            adjList[v].push_back(adjV);
        }

        return adjList;
    }

    std::vector<int> topologicalSortUnweightedList(std::vector<std::vector<int>>& adjList) {
        // A recursive function that performs all the DFS-related processing logic or an unvisited node.
        static std::function<void(const int&, std::vector<std::vector<int>>&, std::vector<bool>&, std::vector<int>&)> dfsVisit = [&](const int& currNode, std::vector<std::vector<int>>& adjList, std::vector<bool>& visited, std::vector<int>& processedList) {
            if (visited[currNode]) {
                // throw std::runtime_error("You cannot visit a node more than once");
                return;
            }

            visited[currNode] = true;

            // Iterate through all the nodes adjacent to the current one
            for (const int& neighbour : adjList[currNode])
                // Visit any unvisited neighbours
                if (!visited[neighbour]) {
                    dfsVisit(neighbour, adjList, visited, processedList);
                }

            processedList.push_back(currNode);
            };

        // --------------------------------

        const int n{ adjList.size() };
        std::vector<bool> visited(n, false);
        std::vector<int> processedList{};

        // Iterate through all the nodes that haven't been visited yet
        for (int node{}; node < n; node++) {
            if (!visited[node]) {
                // Visiting an unvisited node
                dfsVisit(node, adjList, visited, processedList);
            }
        }

        std::reverse(processedList.begin(), processedList.end());
        return processedList;
    }

    // TODO
    std::vector<int> topologicalSortWeightedList(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> topologicalSortUnweightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }

    // TODO
    std::vector<int> topologicalSortWeightedMatrix(/* ??? */) {
        // ...
        return std::vector<int>();
    }


public:
    std::vector<int> topoSort(int V, std::vector<std::vector<int>>& edges) { // TODO: make it support other graphs (weighted, adj. matrix)
        std::vector<std::vector<int>> adjList = edgeListToAdjList(edges, V);
        return topologicalSortUnweightedList(adjList);
    }
};
