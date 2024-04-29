#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>

std::pair<int, int> generateRandomEdge(int n, const std::vector<std::vector<int>>& adjacencyMatrix) {
    int a = rand() % n;
    int b = rand() % n;
    while (a == b || adjacencyMatrix[a][b]) {
        a = rand() % n;
        b = rand() % n;
    }
    return std::make_pair(a, b);
}
std::vector<std::vector<int>> createAdjacencyMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    return matrix;
}
std::vector<std::vector<int>> createAdjacencyList(int n) {
    std::vector<std::vector<int>> list(n);
    return list;
}

void DFS_Utility(int v, std::vector<bool>& visited, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<std::pair<int, int>>& edges, int parent) {
    visited[v] = true;

    for (int i = 0; i < adjacencyMatrix[v].size(); ++i) {
        if (adjacencyMatrix[v][i]) {
            edges.push_back({v, i});
            if (!visited[i]) {
                DFS_Utility(i, visited, adjacencyMatrix, edges, v);
            }
        }
    }
}

void DFS(int v, const std::vector<std::vector<int>>& adjacencyMatrix) {
    std::vector<bool> visited(adjacencyMatrix.size(), false);
    std::vector<std::pair<int, int>> edges;
    std::stack<int> stack;
    stack.push(v);

    while (!stack.empty()) {
        v = stack.top();
        stack.pop();

        if (!visited[v]) {
            visited[v] = true;
            std::cout << v << " ";
            for (int i = adjacencyMatrix[v].size() - 1; i >= 0; --i) {
                if (adjacencyMatrix[v][i]) {
                    edges.push_back({v, i});
                    stack.push(i);
                }
            }
        }
    }

    std::cout << "\nDFS Edges: ";
    for (const auto& edge : edges) {
        std::cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    std::cout << "\n";
}

void BFS(int v, const std::vector<std::vector<int>>& adjacencyMatrix) {
    std::vector<bool> visited(adjacencyMatrix.size(), false);
    std::queue<int> queue;
    std::vector<std::pair<int, int>> edges;
    visited[v] = true;
    queue.push(v);

    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        std::cout << v << " ";

        for (int i = 0; i < adjacencyMatrix[v].size(); ++i) {
            if (adjacencyMatrix[v][i] && !visited[i]) {
                queue.push(i);
                visited[i] = true;
                edges.push_back({v, i});
            }
        }
    }

    std::cout << "\nBFS Edges: ";
    for (const auto& edge : edges) {
        std::cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    std::cout << "\n";
}

int main() {
    srand(time(0));

    int n, e;
    std::cout << "Enter number of nodes: ";
    std::cin >> n;
    std::cout << "Enter number of edges: ";
    std::cin >> e;
    if(e > (n * (n - 1) / 2)){// (C N取2)
        std::cout << "That's too many edges\n";
        std::cout << "The maximum number of edges for " << n << " nodes is " << (n * (n - 1) / 2) << "\n";
        return 0;
    }
    
    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix(n);
    std::vector<std::vector<int>> adjacencyList = createAdjacencyList(n);

    for (int i = 0; i < e; i++) {
        std::pair<int, int> edge = generateRandomEdge(n, adjacencyMatrix);

        while (adjacencyMatrix[edge.first][edge.second]) {
            edge = generateRandomEdge(n, adjacencyMatrix);
        }
        adjacencyMatrix[edge.first][edge.second] = 1;
        adjacencyMatrix[edge.second][edge.first] = 1;
        
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first);
    }
    for (int i = 0; i < n; i++) {
        std::sort(adjacencyList[i].begin(), adjacencyList[i].end());
    }

    std::cout << "Adjacency Matrix:\n";
    for (const auto &row : adjacencyMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Adjacency List:\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << ": ";
        for (int j : adjacencyList[i]) {
            std::cout << j << " -> ";
        }
        std::cout << "END\n";
    }
    std::cout << "DFS: ";
    DFS(0, adjacencyMatrix);
    std::cout << "\n";

    std::cout << "BFS: ";
    BFS(0, adjacencyMatrix);
    std::cout << "\n";

    return 0;
}