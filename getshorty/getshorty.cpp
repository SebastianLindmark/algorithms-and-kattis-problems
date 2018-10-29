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
    Edge(Node *u_, Node *v_, double cost_) : u{u_}, v{v_} {
        cost = cost_;
    }

    Node *u;
    Node *v;
    double cost;
};

class Node {
public:
    vector<Edge *> edges;
    double distance = 0;
    Node *parent;
    long long int index;

};


struct CmpEdgePtrs {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->distance < rhs->distance; //sort bigger first
    }
};


vector<Node *> & djikstra(vector<Node *> & graph, int startIndex){
    priority_queue<Node *, vector<Node *>, CmpEdgePtrs> unvisited;
    Node *startNode = graph[startIndex];
    startNode->distance = 1;
    unvisited.push(startNode);


    while (!unvisited.empty()) {

        Node * node = unvisited.top();
        unvisited.pop();

        for (auto edge : node->edges) {
            if (node->distance * edge->cost > edge->v->distance) {
                edge->v->distance = node->distance * edge->cost;
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

        int startIndex = 0;

        if (numNodes == 0 && numEdges == 0) {
            return 0;
        }

        for (int i = 0; i < numNodes; i++) {
            Node *node = new Node{};
            node->index = i;
            node->parent = node;
            nodeList.push_back(node);
        }


        for (int i = 0; i < numEdges; i++) {
            int start, end;
            double cost;

            scanf("%d", &start);
            scanf("%d", &end);
            scanf("%lf", &cost);

            Node *startNode = nodeList[start];
            Node *endNode = nodeList[end];

            Edge *edge1 = new Edge{startNode, endNode, cost};
            Edge *edge2 = new Edge{endNode, startNode, cost};
            startNode->edges.push_back(edge1);
            endNode->edges.push_back(edge2);
        }

        nodeList = djikstra(nodeList,startIndex);
        printf("%.4lf\n",nodeList[numNodes -1 ]->distance);
    }
}