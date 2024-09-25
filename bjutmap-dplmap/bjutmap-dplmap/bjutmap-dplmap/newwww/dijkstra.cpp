#include "dijkstra.h"
#include <vector>
#include <algorithm>  // 使用std::min函数

const int INF = 10000;  // 表示不可达的距离

// Dijkstra算法实现
std::vector<int> dijkstra(const std::vector<std::vector<int>>& graph, int startNode, std::vector<int>& previousNode) {
    int numberOfNodes = graph.size();  // 图中顶点的数量
    std::vector<int> shortestDistances(numberOfNodes, INF);  // 记录从起点到每个顶点的最短距离
    std::vector<bool> visited(numberOfNodes, false);  // 记录某个顶点是否已经被访问过

    // 起点到自己的距离为0
    shortestDistances[startNode] = 0;

    // 初始化previousNode数组为-1，表示前驱节点未知
    previousNode = std::vector<int>(numberOfNodes, -1);

    // 寻找numberOfNodes - 1个最短路径的顶点
    for (int i = 0; i < numberOfNodes - 1; i++) {
        int closestNode = -1;  // 当前最近的未访问顶点
        for (int currentNode = 0; currentNode < numberOfNodes; currentNode++) {
            if (!visited[currentNode] && (closestNode == -1 || shortestDistances[currentNode] < shortestDistances[closestNode])) {
                closestNode = currentNode;  // 更新最近的顶点
            }
        }

        // 松弛（更新）这个最近顶点的邻居节点的距离
        for (int neighbor = 0; neighbor < numberOfNodes; neighbor++) {
            if (graph[closestNode][neighbor] != INF && shortestDistances[neighbor] > shortestDistances[closestNode] + graph[closestNode][neighbor]) {
                shortestDistances[neighbor] = shortestDistances[closestNode] + graph[closestNode][neighbor];
                previousNode[neighbor] = closestNode;  // 记录前驱节点
            }
        }

        // 标记这个顶点为已访问
        visited[closestNode] = true;
    }

    return shortestDistances;
}
