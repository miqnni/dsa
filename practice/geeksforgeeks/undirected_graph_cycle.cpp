// We can use either BFS or DFS

#include <vector> // std::vector<>
#include <queue> // std::queue<>
#include <utility> // std::pair<>, std::make_pair()

class Solution {
private:
    using v1d = std::vector<int>;
    using v2d = std::vector<std::vector<int>>;
    using vPair = std::pair<int, int>;

    v2d edgesToAdjList(const v2d& edges, const int& n) {
        v2d adjList(
            n,
            v1d()
        );

        for (const v1d& edge : edges) {
            const int v{ edge[0] }, vAdj{ edge[1] };
            adjList[v].push_back(vAdj);
            adjList[vAdj].push_back(v);
        }
        return adjList;
    }

    bool dfsVisitCycleCheck(const int& currNode, const v2d& adjList, std::vector<bool>& visited, const int& prevNode) {

        visited[currNode] = true;

        // Visit adjacent nodes. If any node has already been visited and has a different
        // parent than the current node, a cycle is detected.
        for (const int& vAdj : adjList[currNode]) {
            if (!visited[vAdj]) {
                if (dfsVisitCycleCheck(vAdj, adjList, visited, currNode)) {
                    return true;
                }
                continue;
            }

            // Here, we know vAdj is visited
            // Now, the only possibility of there not being a cycle
            // is if it is backtracking to go currNode --> vAdj.
            if (vAdj != prevNode)
                return true; // Since vAdj is not our node's "parent", we have a cycle.

            // Check the next adjacent node, if it exists (continue the loop)
        }

        return false;
    }

    bool dfsSolution(const v2d& adjList) {
        const int n{ static_cast<int>(adjList.size()) };
        std::vector<bool> visited(n, false);

        for (int node{}; node < n; node++) {
            if (visited[node])
                continue;

            // A new connected component begins
            if (dfsVisitCycleCheck(node, adjList, visited, -1))
                return true;
        }
        return false;
    }

    bool bfsCycleCheck(const int& startNode, const v2d& adjList, std::vector<bool>& visited) {
        visited[startNode] = true;

        std::queue<vPair> q;
        q.push(std::make_pair(startNode, -1));


        while (!q.empty()) {
            int currNode{ q.front().first }, prevNode{ q.front().second };
            q.pop();

            for (const int& vAdj : adjList[currNode]) {
                if (!visited[vAdj]) {
                    // Visit the adj. node and add it to the queue
                    visited[vAdj] = true;
                    q.push(std::make_pair(vAdj, currNode));

                    continue;
                }

                // Now we know that the vAdj node has been visited.
                // If visiting it is not direct backtracking, we have a cycle.
                if (vAdj != prevNode)
                    return true;
            }
        }

        return false;
    }

    bool bfsSolution(const v2d& adjList) {
        const int n{ static_cast<int>(adjList.size()) };
        std::vector<bool> visited(n, false);

        for (int node{}; node < n; node++) {
            if (visited[node])
                continue;

            // A new connected component begins. Let's do BFS on it and check
            // if there is a cycle in that particular component.
            if (bfsCycleCheck(node, adjList, visited))
                return true;
        }

        return false;
    }

public:
    bool isCycle(int V, std::vector<std::vector<int>>& edges) {
        const v2d adjList = edgesToAdjList(edges, V);
        return bfsSolution(adjList);
    }
};