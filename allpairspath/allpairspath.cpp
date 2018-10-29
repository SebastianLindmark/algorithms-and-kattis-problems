//Author Sebastian Lindmark
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


void floydWarshall(vector<vector<long long int>> &graph, int numNodes) {


    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j] && graph[i][k] < numeric_limits<long int>::max() &&
                    graph[k][j] < numeric_limits<long int>::max()) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    for (int j = 0; j < numNodes; j++) {
        for (int i = 0; i < numNodes; i++) {
            for (int k = 0; k < numNodes; k++) {
                bool negativeCostToItself = graph[k][k] < 0;
                bool existsPath = graph[j][k] < numeric_limits<long int>::max() && graph[k][i] < numeric_limits<long int>::max();
                if (negativeCostToItself && existsPath) {
                    graph[j][i] = numeric_limits<long int>::min();
                }

            }
        }
    }
}

int main() {


    long int numNodes, numEdges, numQueries;
    while (scanf("%ld %ld %ld", &numNodes, &numEdges, &numQueries)) {

        if (numNodes == 0 && numEdges == 0 && numQueries == 0) {
            return 0;
        }


        vector<vector<long long int>> distances;
        for (int i = 0; i < numNodes; i++) {
            vector<long long int> arr;
            for (int j = 0; j < numNodes; j++) {
                if (i == j) {
                    arr.push_back(0);
                } else {
                    arr.push_back(numeric_limits<long int>::max());
                }
            }
            distances.push_back(arr);
        }


        for (int i = 0; i < numEdges; i++) {
            long int srcNode, dstNode, cost;
            scanf("%ld %ld %ld", &srcNode, &dstNode, &cost);
            if (cost < distances[srcNode][dstNode]) {
                distances[srcNode][dstNode] = cost;
            }
        }

        floydWarshall(distances, numNodes);

        for (int i = 0; i < numQueries; i++) {
            long int x, y;
            scanf("%ld%ld", &x, &y);

            if (distances[x][y] == numeric_limits<long int>::max()) {
                printf("Impossible\n");
            } else if (distances[x][y] == numeric_limits<long int>::min()) {
                printf("-Infinity\n");
            } else {
                printf("%lld\n", distances[x][y]);
            }
        }
        printf("\n");
    }


    return 0;
}