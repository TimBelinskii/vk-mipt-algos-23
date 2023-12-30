#include <iostream>
#include "vector"
#include "queue"

class Graph {
    int numberNodes;
    int **matrix;

public:
    void enter() {
        /// Вводить граф необходимо в следующем виде
        /// 3
        /// 1: 2, 3
        /// 2: 1, 3
        /// 3: 1, 2

        for (int i = 0; i < numberNodes; i++) {
            std::string in;
            std::getline(std::cin, in);
            int u = std::stoi(in.substr(0, in.find(':'))) - 1;
            in = in.substr(in.find(' ') + 1, in.size() - in.find(' ') - 1);
            while (in.find(' ') != -1) {
                int v = std::stoi(in.substr(0, in.find(','))) - 1;
                matrix[u][v] = 1;
                matrix[v][u] = 1;
                in = in.substr(in.find(' ') + 1, in.size() - in.find(' ') - 1);
            }
            int v = std::stoi(in.substr(0, in.find(','))) - 1;
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }
    }

    void print() {
        for (int i = 0; i < numberNodes; i++) {
            for (int j = 0; j < numberNodes; j++) {
                std::cout << matrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void dfs(int *visited, const int &current = 0, const int &color = 1, bool *cycle = nullptr) {
        if (cycle == nullptr) {
            cycle = new bool{false};
        }
        visited[current] = color;
        for (int j = 0; j < numberNodes; j++) {
            if (matrix[current][j] == 1 && visited[j] == 0) {
                dfs(visited, j, color, cycle);
            } else if (visited[j] != 0) {
                *cycle = true;
            }
        }
    }

    void bfs(int *visited, const int &start = 0, bool *cycle = nullptr) {
        if (cycle == nullptr) {
            cycle = new bool{false};
        }
        std::queue<int> nodes;
        std::queue<int> parents;
        nodes.push(start);
        parents.push(-1);
        while (!nodes.empty()) {
            int current = nodes.front();
            int previous = parents.front();
            nodes.pop();
            parents.pop();
            visited[current] = 1;
            for (int i = 0; i < numberNodes; i++) {
                if (matrix[current][i] != 0 && previous != i && visited[i] == 0) {
                    nodes.push(i);
                    parents.push(current);
                } else if (visited[i] != 0) {
                    *cycle = true;
                }
            }
        }
    }

    std::pair<int, int *> find_connected_components() {
        int col = 1;
        int *vis = new int[numberNodes];
        for (int i = 0; i < numberNodes; i++) {
            vis[i] = 0;
        }
        for (int i = 0; i < numberNodes; i++) {
            if (vis[i] == 0) {
                dfs(vis, i, col);
                col++;
            }
        }
        return std::make_pair(col - 1, vis);
    }

    bool has_cycle() {
        int *vis = new int[numberNodes];
        bool *res = new bool{false};
        for (int i = 0; i < numberNodes; i++) {
            vis[i] = 0;
        }
        for (int i = 0; i < numberNodes; i++) {
            if (vis[i] == 0) {
                dfs(vis, i, 1, res);
                if (*res) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_tree() {
        int *vis = new int[numberNodes];
        for (int i = 0; i < numberNodes; i++) {
            vis[i] = 0;
        }
        bool *res = new bool{false};
        bfs(vis, 0, res);
        if (*res) {
            return true;
        }
        for (int i = 0; i < numberNodes; i++) {
            if (vis[i] == 0) {
                return false;
            }
        }
        return true;
    }

    Graph(const int &num) {
        numberNodes = num;
        matrix = new int *[numberNodes];
        for (int i = 0; i < numberNodes; i++) {
            matrix[i] = new int[numberNodes];
            for (int j = 0; j < numberNodes; j++) {
                matrix[i][j] = 0;
            }
        }
    }
};


int main() {
    int n;
    std::string in;
    getline(std::cin, in);
    n = stoi(in);
    Graph g1(n);
    g1.enter();
    std::cout << g1.is_tree();
    return 0;
}
