#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

#include <queue>

//Author Sebastian Lindmark

using namespace std;


class Edge;

class Node;


class Edge {
public:
    Edge(Node *u_, Node *v_, long long int cost_) : u{u_}, v{v_} {
        cost = cost_;
    }
    Node *u;
    Node *v;
    long long int cost;
};

class Node {
public:
    vector<Edge *> edges;
    long long int distance = numeric_limits<long long int>::max();
    Node *parent;
    long long int index;
    long int pickedUp = 0;
    long int itemsThatCanBePickedup;
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
            if (node->distance + edge->cost < edge->v->distance) {
                edge->v->distance = node->distance + edge->cost;
                edge->v->parent = node;
                edge->v->pickedUp = node->pickedUp + edge->v->itemsThatCanBePickedup;
                unvisited.push(edge->v);
            } else if (node->distance + edge->cost == edge->v->distance &&
                       node->pickedUp + edge->v->itemsThatCanBePickedup > edge->v->pickedUp) {
                edge->v->distance = node->distance + edge->cost;
                edge->v->parent = node;
                edge->v->pickedUp = node->pickedUp + edge->v->itemsThatCanBePickedup;
                unvisited.push(edge->v);
            }
        }
    }
    return graph;
}


int main() {
    int numNodes;
    scanf("%d", &numNodes);

    vector<Node *> nodeList;

    for (int i = 0; i < numNodes; i++) {
        long int items;
        scanf("%ld", &items);

        Node *node = new Node{};
        node->index = i;
        node->parent = node;
        node->itemsThatCanBePickedup = items;
        nodeList.push_back(node);
    }

    int numEdges;
    scanf("%d", &numEdges);


    for (int i = 0; i < numEdges; i++) {
        int start, end, cost;
        scanf("%d", &start);
        scanf("%d", &end);
        scanf("%d", &cost);

        start = start - 1;
        end = end - 1;

        Node *startNode = nodeList[start];
        Node *endNode = nodeList[end];

        Edge *edge1 = new Edge{startNode, endNode, cost};
        Edge *edge2 = new Edge{endNode, startNode, cost};
        startNode->edges.push_back(edge1);
        endNode->edges.push_back(edge2);
    }

    nodeList[0]->pickedUp = nodeList[0]->itemsThatCanBePickedup;
    nodeList = djikstra(nodeList, 0);

    long int endNodeIndex;
    endNodeIndex = numNodes - 1;

    if (endNodeIndex >= numNodes || nodeList[endNodeIndex]->distance == numeric_limits<long long int>::max()) {
        printf("%s\n", "impossible"); //TODO can this be I?
    } else {
        printf("%lld ", nodeList[endNodeIndex]->distance);
        printf("%lld\n", nodeList[endNodeIndex]->pickedUp);
    }
}
