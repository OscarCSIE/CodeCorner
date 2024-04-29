#include <iostream>
#include <vector>
#include <cstdlib>
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

int main() {
    srand(time(0));

    int n, e;
    std::cout << "Enter number of nodes: ";
    std::cin >> n;
    std::cout << "Enter number of edges: ";
    std::cin >> e;
    if(e > (n * (n - 1) / 2)){// (Cn取2)
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
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
    return 0;
}