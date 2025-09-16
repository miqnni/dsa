// #define INF 0x3f3f3f3f

#include <iostream>
#include <vector>
#include <limits> // std::numeric_limits<int>::max()
#include <queue> // std::priority_queue

class Solution {
private:
    static constexpr int inf = std::numeric_limits<int>::max();

    using IntPair = std::pair<int, int>;
    using AdjacencyList = std::vector<std::vector<IntPair>>;
    using PQ = std::priority_queue<IntPair, std::vector<IntPair>, std::greater<IntPair>>;

    void printAdjacencyList(AdjacencyList g, std::ostream& out = std::cout) {
        out << "{\n";
        for (std::vector<std::pair<int, int>> adjNodes : g) {
            out << "\t" << "{ ";
            for (std::pair<int, int> adjNode : adjNodes) {
                out << "(" << adjNode.first << ", " << adjNode.second << "), ";
            }
            out << "}\n";
        }
        out << "}\n";
    }

    AdjacencyList createAdjacencyList(int nodeCount, std::vector<std::vector<int>>& edgeList) {
        AdjacencyList g(
            nodeCount,
            std::vector<IntPair>()
        );

        for (const std::vector<int>& edge : edgeList) {
            int vFrom = edge[0], vTo = edge[1], weight = edge[2];
            g[vFrom].push_back({ vTo, weight });
        }
        return g;

    }

public:
    std::vector<int> dijkstra(int V, std::vector<std::vector<int>>& edges, int src) {
        AdjacencyList g = createAdjacencyList(V, edges);

        std::vector<int> d(V, inf);
        d[src] = 0;

        std::vector<bool> visited(V, false);
        std::vector<int> parent(V, -1);

        /*
        pq.push(std::make_pair(0, src));
        int v0 = pq.top().second;
        pq.pop();
        pq.empty()
        */
        PQ pq;
        pq.push(std::make_pair(0, src));


        while (!pq.empty()) {
            int v0 = pq.top().second;
            pq.pop();

            if (visited[v0])
                continue;

            visited[v0] = true;

            for (const IntPair vPair : g[v0]) {
                int v1 = vPair.first, w = vPair.second;
                if (visited[v1])
                    continue;

                int newDistance = d[v0] + w;
                if (newDistance < d[v1]) {
                    d[v1] = newDistance;
                    pq.push(std::make_pair(newDistance, v1));
                }
            }
        }

        return d;
    }
};