#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

#include <queue>
#include <cmath>

//Author Sebastian Lindmark

using namespace std;


class Edge;

class Node;


class Edge {
public:
    Edge(Node *v_, int t0_, int P_, int cost_) : v{v_}, t0{t0_}, P{P_}, cost{cost_} {
    }

    long long int getCost(double t) {
        /*if (P == 0) {
            if (t != t0 || t >= t0) {
                return numeric_limits<long long int>::max();
            } else {
                return t0- t + cost;
            }
        }*/

        if (t0 >= t) {
            return t0 - t + cost;
        } else {
            return (P * std::ceil(((double) (t - t0)) / ((double) P))) + t0 - t + cost; //hax by HAXXOR
        }
    }

    bool isAllowed(long long int t) {
        return P != 0 || (P == 0 && t0 >= t);
    }

    Node *v;
    int t0;
    int P;
    long long int cost;


};

class Node {
public:
    vector<Edge *> edges;
    long long int distance = numeric_limits<long long int>::max();
    Node *parent;
    long long int index;

};


struct CmpEdgePtrs {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->distance > rhs->distance;
    }
};


vector<Node *> &djikstra(vector<Node *> &graph, int startIndex) {
    priority_queue<Node *, vector<Node *>, CmpEdgePtrs> unvisited;
    Node *startNode = graph[startIndex];
    startNode->distance = 0;
    unvisited.push(startNode);

    while (!unvisited.empty()) {

        Node *node = unvisited.top();
        unvisited.pop();

        for (auto edge : node->edges) {
            if (edge->isAllowed(node->distance) && node->distance + edge->getCost(node->distance) < edge->v->distance) {
                edge->v->distance = node->distance + edge->getCost(node->distance);
                edge->v->parent = node;
                unvisited.push(edge->v);
            }
        }
    }
    return graph;
}


int main() {
    int numNodes;
    while (cin >> numNodes) {
        vector<Node *> nodeList;


        int numEdges;
        scanf("%d", &numEdges);

        int numQueries;
        scanf("%d", &numQueries);

        int startIndex;
        scanf("%d", &startIndex);

        if (numNodes == 0 && numEdges == 0 && numQueries == 0 && startIndex == 0) {
            return 0;
        }

        for (int i = 0; i < numNodes; i++) {
            Node *node = new Node{};
            node->index = i;
            node->parent = node;
            nodeList.push_back(node);
        }


        for (int i = 0; i < numEdges; i++) {
            int start, end, cost, t0, P;
            scanf("%d", &start);
            scanf("%d", &end);
            scanf("%d", &t0);
            scanf("%d", &P);
            scanf("%d", &cost);

            Node *startNode = nodeList[start];
            Node *endNode = nodeList[end];

            Edge *edge = new Edge{endNode, t0, P, cost};
            startNode->edges.push_back(edge);
        }

        nodeList = djikstra(nodeList, startIndex);

        for (int i = 0; i < numQueries; i++) {
            long long int endNodeIndex;
            scanf("%lld", &endNodeIndex);

            if (endNodeIndex >= numNodes || nodeList[endNodeIndex]->distance == numeric_limits<long long int>::max()) {
                printf("%s\n", "Impossible");
            } else {
                printf("%lld\n", nodeList[endNodeIndex]->distance);
            }
        }
        printf("\n");

        for (int i = 0; i < nodeList.size(); i++) {
            Node *node = nodeList[i];

            for (int k = 0; k < node->edges.size(); k++) {
                Edge *edge = node->edges[k];
                delete edge;
                edge = NULL;
            }
            node->edges.erase(node->edges.begin(), node->edges.end());
            delete node;
            node = NULL;
        }
        nodeList.erase(nodeList.begin(), nodeList.end());


    }
}
