//Author Sebastian Lindmark
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
public:
    Node(long long int r, long long int id) : rank{r}, index{id} {};
    long long int rank;
    long long int index;
    Node *parent;
};


struct Edge {
    Edge(Node *s, Node *d, long long int c) : src{s}, dest{d}, cost{c} {};
    Node *src;
    Node *dest;
    long long int cost;
};

Node *getParent(Node *node) {
    if (node->parent->index != node->index) {
        node->parent = getParent(node->parent);
    }
    return node->parent;
}

void unionSets(Node *node1, Node *node2) {
    Node *rootNode1 = getParent(node1);
    Node *rootNode2 = getParent(node2);

    if (rootNode1->index == rootNode2->index) {
        return;
    } else {
        if (rootNode1->rank < rootNode2->rank) {
            rootNode1->parent = rootNode2;
        } else if (rootNode1->rank > rootNode2->rank) {
            rootNode2->parent = rootNode1;
        } else {
            rootNode1->rank = rootNode1->rank + 1;
            rootNode2->parent = rootNode1;
        }
    }
}

bool unionFind(Node *a, Node *b) {
    return getParent(a)->index == getParent(b)->index;
}


int main() {
    long long int numNodes;
    while (scanf("%lli", &numNodes)) {

        long long int numEdges;
        scanf("%lli", &numEdges);

        vector<Node *> nodes;
        vector<Edge> edges;

        if (numNodes == 0 && numEdges == 0) {
            return 0;
        }

        for (long long int index = 0; index < numNodes; ++index) {
            Node *node = new Node(0, index);
            node->parent = node;
            nodes.push_back(node);
        }
        for (int k = 0; k < numEdges; ++k) {
            long long int srcNodeIndex, dstNodeIndex, cost;
            scanf("%lli", &srcNodeIndex);
            scanf("%lli", &dstNodeIndex);
            scanf("%lli", &cost);


            if (srcNodeIndex > dstNodeIndex) {
                edges.push_back(Edge(nodes[dstNodeIndex], nodes[srcNodeIndex], cost));
            } else {
                edges.push_back(Edge(nodes[srcNodeIndex], nodes[dstNodeIndex], cost));
            }
        }
        sort(edges.begin(), edges.end(), [](Edge &first, Edge &second) { return first.cost < second.cost; });
        vector<Edge> result;
        long long int totalCost = 0;
        for (int i = 0; i < numEdges; i++) {
            if (!unionFind(edges[i].src, edges[i].dest)) {
                unionSets(edges[i].src, edges[i].dest);
                totalCost += edges[i].cost;
                result.push_back(edges[i]);
            }
        }

        if (numNodes - 1 == result.size()) {
            sort(result.begin(), result.end(),
                 [](Edge &first, Edge &second) {

                     if (first.src->index == second.src->index) {
                         return first.dest->index <= second.dest->index;
                     } else {
                         return first.src->index <= second.src->index;
                     }
                 });
            cout << totalCost << endl;
            for (auto edge : result) {
                cout << edge.src->index << " " << edge.dest->index << endl;
            }
        } else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}