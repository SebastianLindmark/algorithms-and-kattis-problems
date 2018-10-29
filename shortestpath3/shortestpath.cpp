//Author Sebastian Lindmark
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Edge;

class Node;


class Edge {
public:
    Edge(Node *u_, Node *v_, long long int cost_) : src{u_}, dst{v_} {
        cost = cost_;
    }

    Node *src;
    Node *dst;
    long long int cost;
};

class Node {
public:
    vector<Edge *> edges;
    long long int distance = numeric_limits<long int>::max();
    Node *parent;
    long long int index;
};


struct CmpEdgePtrs {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->distance > rhs->distance;
    }
};


void bellmanFord(vector<Node *> &graph, vector<Edge *> edges, int numNodes, int numEdges, int startIndex) {

    graph[startIndex]->distance = 0;

    for (int i = 1; i < numNodes; i++) {
        for (int inner = 0; inner < numEdges; inner++) {
            Node *srcNode = edges[inner]->src;
            Node *dstNode = edges[inner]->dst;
            long long int weight = edges[inner]->cost;
            if (srcNode->distance != numeric_limits<long int>::max() &&
                srcNode->distance + weight < dstNode->distance) {
                dstNode->distance = srcNode->distance + weight;
            }
        }
    }
    bool optimized = true;
    for (int k = 0; k < numEdges; k++) {
        for (int i = 0; i < numEdges; i++) {
            //check if we have an infinite cycle
            Node *srcNode = edges[i]->src;
            Node *dstNode = edges[i]->dst;
            long long int weight = edges[i]->cost;


            if (srcNode->distance == numeric_limits<long int>::min()) {
                dstNode->distance = numeric_limits<long int>::min();
            } else if (srcNode->distance != numeric_limits<long int>::max() &&
                       srcNode->distance + weight < dstNode->distance) {

                dstNode->distance = numeric_limits<long int>::min();
                optimized = false;
            }
        }
        if (optimized) {
            break;
        }
    }

}


int main() {
    int numNodes;
    while (cin >> numNodes) {

        int numEdges;
        scanf("%d", &numEdges);

        int numQueries;
        scanf("%d", &numQueries);

        int startIndex;
        scanf("%d", &startIndex);

        if (numNodes == 0 && numEdges == 0 && numQueries == 0 && startIndex == 0) {
            return 0;
        }

        vector<Node *> nodeList;
        vector<Edge *> edgeList;

        for (int i = 0; i < numNodes; i++) {
            Node *node = new Node{};
            node->index = i;
            node->parent = node;
            nodeList.push_back(node);
        }


        for (int i = 0; i < numEdges; i++) {
            int start, end, cost;
            scanf("%d", &start);
            scanf("%d", &end);
            scanf("%d", &cost);

            Node *startNode = nodeList[start];
            Node *endNode = nodeList[end];

            Edge *edge = new Edge(startNode, endNode, cost);
            startNode->edges.push_back(edge);
            edgeList.push_back(edge);
        }

        bellmanFord(nodeList, edgeList, nodeList.size(), edgeList.size(), startIndex);

        for (int i = 0; i < numQueries; i++) {
            long long int endNodeIndex;
            scanf("%lld", &endNodeIndex);

            if (endNodeIndex > nodeList.size() - 1 ||
                nodeList[endNodeIndex]->distance == numeric_limits<long int>::max()) {
                printf("%s\n", "Impossible");
            } else if (nodeList[endNodeIndex]->distance == numeric_limits<long int>::min()) {
                printf("%s\n", "-Infinity");
            } else {
                printf("%lld\n", nodeList[endNodeIndex]->distance);
            }
        }
        printf("\n");
    }
}