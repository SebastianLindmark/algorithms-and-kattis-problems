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

    int teams, matchesLeft;
    while (true) {
        scanf("%d",&teams);


        if(teams == -1){
            return 0;
        }

        scanf("%d",&matchesLeft);

        vector<int> initialTeamScores;
        for (int i = 0; i < teams; i++) {
            int teamScore;
            scanf("%d",&teamScore);
            initialTeamScores.push_back(teamScore);
        }

        vector<vector<long int>> graph;

        int SOURCE_ID = 0;
        long int SINK_ID = teams + matchesLeft + 1;

        vector<vector<long int>> neighbours;

        for (int i = 0; i < teams + matchesLeft + 2; i++) { //source + sink node
            vector<long int> cost(teams + matchesLeft + 2, 0);
            graph.push_back(cost);
            vector<long int> neighbour;
            neighbours.push_back(neighbour);
        }

        //source to matches
        for (int i = 1; i < matchesLeft + 1; i++) {
            graph[0][i] = 2;
        }

        vector<pair<int, int>> matches;
        int matchesWithoutOurTeamInIt = 0;
        int ourTeamExtraPoints = 0;
        for (long int i = 1; i < matchesLeft + 1; i++) {
            int team1, team2;
            scanf("%d",&team1);
            scanf("%d",&team2);
            matches.push_back(make_pair(team1, team2));
            if (team1 == teams || team2 == teams) {
                ourTeamExtraPoints += 2;

            } else {
                matchesWithoutOurTeamInIt += 2;
                graph[i][matchesLeft + team1] = 999; // since team index are 1-indexed
                graph[i][matchesLeft + team2] = 999; // since team index are 1-indexed

                neighbours[0].push_back(i);
                neighbours[i].push_back(0);
                neighbours[i].push_back(matchesLeft + team1); //1 + matchesLeft + team1 -1
                neighbours[i].push_back(matchesLeft + team2); //1 + matchesLeft + team1 -1
                neighbours[matchesLeft + team1].push_back(i);
                neighbours[matchesLeft + team2].push_back(i);
            }
        }

        bool quit = false;
        int ourTeamFinalScore = initialTeamScores.back() + ourTeamExtraPoints;

        for (int i = 0; i < initialTeamScores.size() - 1; i++) {
            if (ourTeamFinalScore <= initialTeamScores[i]) {
                printf("%s\n","NO");
                quit = true;
                break;
            }
        }
        if (!quit) {
            for (long int i = matchesLeft + 1; i < matchesLeft + teams + 1; i++) {
                int capacity = ourTeamFinalScore - initialTeamScores[i - matchesLeft - 1] - 1;
                graph[i][SINK_ID] = capacity;
                neighbours[i].push_back(SINK_ID);
                neighbours[SINK_ID].push_back(i);
            }

            int numNodes = teams + matchesLeft + 2;
            pair<long int, vector<vector<long int>>> pair_result = fordFulkersson(graph, neighbours, numNodes, 0,
                                                                                  numNodes - 1);
            long int flow = pair_result.first;
            vector<vector<long int>> result = pair_result.second;

            long int edgesUsed = 0;

            int sum = 0;
            for (int k = 1; k < 1 + matchesLeft; k++) {
                sum += result[k][0];
            }

            if (sum != matchesWithoutOurTeamInIt) {
                printf("%s\n","NO");

            } else {

                for (int i = 0; i < matches.size(); i++) {

                    pair<int, int> match = matches[i];

                    if (match.first == teams) {
                        printf("%s ","0");
                    } else if (match.second == teams) {
                        printf("%s ","2");
                    } else {

                        int matchIndex = i + 1;
                        int teamIndex1 = matchesLeft + match.first;
                        int teamIndex2 = matchesLeft + match.second;

                        if (result[teamIndex1][matchIndex] == 2) {
                            printf("%s ","0");
                        } else if (result[teamIndex2][matchIndex] == 2) {
                            printf("%s ","2");
                        } else {
                            printf("%s ","1");
                        }

                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}

