#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <cmath>
#include <iomanip>
#include <unordered_set>

using namespace std;


struct Node {
    long int id;
};

bool BFS(vector<vector<long int>> &costs, int numNodes, vector<vector<long int>> &neighbours, vector<int> &backtrack,
         long int start, long int end) {

    vector<bool> visited(numNodes, false);
    queue<long int> unvisited;
    visited[start] = true;
    unvisited.push(start);
    while (!unvisited.empty()) {
        int node = unvisited.front();
        unvisited.pop();

        for (int i = 0; i < neighbours[node].size(); i++) {
            long int neighbour = neighbours[node][i];
            if (costs[node][neighbour] > 0 && !visited[neighbour] && node != neighbour) {
                unvisited.push(neighbour);
                backtrack[neighbour] = node;
                visited[neighbour] = true;
                if (neighbour == end) {
                    return true;
                }
            }
        }

    }

    return false;
}

pair<long int, vector<vector<long int>>>
fordFulkersson(vector<vector<long int>> costs, vector<vector<long int>> &neighbours, int numNodes, int start, int end) {
    vector<int> backtrack(numNodes, -1);
    long int totalFlow = 0;
    while (BFS(costs, numNodes, neighbours, backtrack, start, end)) {

        long int flow = numeric_limits<long int>::max();
        long int cur = end;
        while (backtrack[cur] != -1) {
            if (flow > costs[backtrack[cur]][cur]) {
                flow = costs[backtrack[cur]][cur];
            }
            cur = backtrack[cur];
        }

        cur = end;
        while (backtrack[cur] != -1) {
            costs[backtrack[cur]][cur] -= flow;
            costs[cur][backtrack[cur]] += flow;
            cur = backtrack[cur];
        }

        totalFlow += flow;
    }
    return make_pair(totalFlow, costs);

}

struct pair_hash {
    inline std::size_t operator()(const std::pair<long int, long int> &v) const {
        return v.first * 31 + v.second;
    }
};

int main() {
    long int numNodes, numEdges, sourceId, sinkId;
    unordered_set<pair<long int, long int>, pair_hash> directions;

    vector<vector<long int>> neighbours;

    scanf("%ld", &numNodes);
    scanf("%ld", &numEdges);
    scanf("%ld", &sourceId);
    scanf("%ld", &sinkId);


    vector<vector<long int>> costs;

    for (int i = 0; i < numNodes; i++) {
        vector<long int> cost(numNodes, 0);
        costs.push_back(cost);
        vector<long int> neighbour;
        neighbours.push_back(neighbour);
    }

    for (int i = 0; i < numEdges; i++) {
        long int start, end, c;

        scanf("%ld", &start);
        scanf("%ld", &end);
        scanf("%ld", &c);
        costs[start][end] = c;
        directions.insert(make_pair(start, end));
        neighbours[start].push_back(end);
        neighbours[end].push_back(start);
    }


    pair<long int, vector<vector<long int>>> result = fordFulkersson(costs, neighbours, numNodes, sourceId, sinkId);
    long int flow = result.first;
    vector<vector<long int>> copyCosts = result.second;

    long int edgesUsed = 0;
    for (int i = 0; i < numNodes; i++) {
        for (int k = 0; k < numNodes; k++) {
            if (i != k && costs[k][i] - copyCosts[k][i] > 0 && directions.find(make_pair(k, i)) != directions.end()) {
                edgesUsed++;
            }
        }
    }
    cout << numNodes << " " << flow << " " << edgesUsed << " " << endl;

    for (int i = 0; i < numNodes; i++) {
        for (int k = 0; k < numNodes; k++) {
            if (i != k && costs[k][i] - copyCosts[k][i] > 0 && directions.find(make_pair(k, i)) != directions.end()) {
                cout << k << " " << i << " " << costs[k][i] - copyCosts[k][i] << endl;
            }
        }
    }

    return 0;
}

