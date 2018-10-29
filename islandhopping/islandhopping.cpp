//Author Sebastian Lindmark
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
public:
    Node(double _x, double _y, long long int r, long long int id) : x{_x}, y{_y}, rank{r}, index{id} {};
    long long int rank;
    long long int index;
    double x;
    double y;
    Node *parent;
};


struct Edge {
    Edge(Node *s, Node *d, double c) : src{s}, dest{d}, cost{c} {};
    Node *src;
    Node *dest;
    double cost;
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
    long long int cases;
    scanf("%lli", &cases);
    for (int caseIndex = 0; caseIndex < cases; caseIndex++) {
        long long int numIslands;
        scanf("%lli", &numIslands);

        vector<Node *> nodes;
        vector<Edge> edges;


        for (long long int index = 0; index < numIslands; ++index) {
            double islandX, islandY;
            scanf("%lf", &islandX);
            scanf("%lf", &islandY);

            Node *node = new Node(islandX, islandY, 0, index);
            node->parent = node;
            nodes.push_back(node);
        }

        for (int outer = 0; outer < numIslands; outer++) {
            for (int inner = outer + 1; inner < numIslands; inner++) {
                Node *node1 = nodes[outer];
                Node *node2 = nodes[inner];
                double a = node2->x - node1->x;
                double b = node2->y - node1->y;
                double cost = std::sqrt((a * a) + (b * b));
                edges.push_back(Edge{node1, node2, cost});
            }
        }

        sort(edges.begin(), edges.end(), [](Edge &first, Edge &second) { return first.cost < second.cost; });

        vector<Edge> result;
        double totalCost = 0;
        for (int i = 0; i < edges.size(); i++) {
            if (!unionFind(edges[i].src, edges[i].dest)) {
                unionSets(edges[i].src, edges[i].dest);
                totalCost += edges[i].cost;
                result.push_back(edges[i]);
            }
        }
        printf("%0.3f\n",totalCost);
    }
    return 0;
}