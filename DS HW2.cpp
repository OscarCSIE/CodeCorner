#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include <fstream>

// get a random edge
std::pair<int, int> generateRandomEdge(int n, const std::vector<std::vector<int>>& adjacencyMatrix) {
    int a = rand() % n;
    int b = rand() % n;
    //not self edge and not exist
    while (a == b || adjacencyMatrix[a][b]) {
        a = rand() % n;
        b = rand() % n;
    }
    return std::make_pair(a, b);
}


//empty matrix that is vector of vector == 2d array
std::vector<std::vector<int>> createAdjacencyMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    return matrix;
}

//empty list that is vector of vector == 2d array
std::vector<std::vector<int>> createAdjacencyList(int n) {
    std::vector<std::vector<int>> list(n);
    return list;
}

//v: current vertex
//visited: vector of bool to check if the vertex is visited or not
//adjacencyMatrix: 2d vector to store the graph
//edges: vector of pair to store the edges
//parent: parent of the current vertex

//TODO: GET BETTER AT CODING THIS THING

void DFS_Utility(int v, std::vector<bool>& visited, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector< std::pair<int, int> >& edges, int parent) {//parent for edge type checking
    visited[v] = true;

    //visit the node not visited yet
    for (int i = 0; i < adjacencyMatrix[v].size(); i++) {
        if (adjacencyMatrix[v][i] && !visited[i]) {//if exist and not visited
            edges.push_back({v, i});
            DFS_Utility(i, visited, adjacencyMatrix, edges, v);
        }
    }
}

void DFS(int v, const std::vector<std::vector<int>>& adjacencyMatrix) {
    std::vector<bool> visited(adjacencyMatrix.size(), false);
    std::vector<std::pair<int, int>> edges;

    DFS_Utility(v, visited, adjacencyMatrix, edges, -1); // Start DFS from vertex v with no parent

    std::cout << "\nDFS Edges: ";
    for (const auto& edge : edges) {
        std::cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    std::cout << "\n";

    std::cout << "DFS Path: ";
    for (int i = 0; i < edges.size(); i++) {
        if (i == 0) {
            std::cout << edges[i].first << " -> " << edges[i].second << " ";
        } else {
            std::cout << "-> " << edges[i].second << " ";
        }
    }
    //write all the edge[i].first and second to a csv file
    std::ofstream file;
    file.open("DFS.csv");
    for (int i = 0; i < edges.size(); i++) {
        file << edges[i].first <<","<< edges[i].second<< "\n";
    }
    file.close();

    std::cout << "\nDFS as a adjacency matrix: \n";
    std::vector<std::vector<int>> adjacencyMatrixDFS = createAdjacencyMatrix(adjacencyMatrix.size());
    for (const auto& edge : edges) {
        adjacencyMatrixDFS[edge.first][edge.second] = 1;
    }
    for (const auto &row : adjacencyMatrixDFS) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

//v: current vertex
//visited: vector of bool to check if the vertex is visited or not
//adjacencyMatrix: 2d vector to store the graph

//edges: vector of pair to store the edges

void BFS(int v, const std::vector<std::vector<int>>& adjacencyMatrix) {
    std::vector<bool> visited(adjacencyMatrix.size(), false);//nobody is visited yet
    std::queue<int> queue;//queue to store the vertices -> for the path
    std::vector<std::pair<int, int>> edges;//edge record
    visited[v] = true;
    queue.push(v);

    while (!queue.empty()) {
        v = queue.front();
        queue.pop();

        for (int i = 0; i < adjacencyMatrix[v].size(); i++) {
            if (adjacencyMatrix[v][i] && !visited[i]) {
                edges.push_back({v, i});
                queue.push(i);
                visited[i] = true;
            }
        }
    }

    std::cout << "\nBFS Edges: ";
    for (const auto& edge : edges) {
        std::cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    std::cout << "\n";

    std::cout << "BFS Path: ";
    for (int i = 0; i < edges.size(); i++) {
        if (i == 0) {
            std::cout << edges[i].first << " -> " << edges[i].second << " ";
        } else {
            std::cout << "-> " << edges[i].second << " ";
        }
    }
    std::cout << "\nBFS as a adjacency matrix: \n";
    std::vector<std::vector<int>> adjacencyMatrixBFS = createAdjacencyMatrix(adjacencyMatrix.size());
    for (const auto& edge : edges) {
        adjacencyMatrixBFS[edge.first][edge.second] = 1;
    }
    for (const auto &row : adjacencyMatrixBFS) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    std::ofstream file;
    file.open("BFS.csv");
    for (int i = 0; i < edges.size(); i++) {
        file << edges[i].first <<","<< edges[i].second<< "\n";
    }
    file.close();
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
    //write the matrix into a csv file
    std::ofstream file;
    file.open("adjacencyMatrix.csv");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(adjacencyMatrix[i][j]){
                file << i <<","<< j << "\n";
            }
        }
    }
    file.close();

    std::cout << "Adjacency List:\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << ": ";
        for (int j : adjacencyList[i]) {
            std::cout << j << " -> ";
        }
        std::cout << "END\n";
    }
    std::cout << "\nDFS Result: ";
    DFS(0, adjacencyMatrix);
    std::cout << "\n";

    std::cout << "\nBFS Result: ";
    BFS(0, adjacencyMatrix);
    std::cout << "\n";

    return 0;
}