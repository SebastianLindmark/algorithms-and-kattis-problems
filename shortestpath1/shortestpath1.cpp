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

};


struct CmpEdgePtrs {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->distance > rhs->distance;
    }
};


vector<Node *> & djikstra(vector<Node *> & graph, int startIndex){
    priority_queue<Node *, vector<Node *>, CmpEdgePtrs> unvisited;
    Node *startNode = graph[startIndex];
    startNode->distance = 0;
    unvisited.push(startNode);


    while (!unvisited.empty()) {

        Node * node = unvisited.top();
        unvisited.pop();

        for (auto edge : node->edges) {
            if (node->distance + edge->cost < edge->v->distance) {
                edge->v->distance = node->distance + edge->cost;
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
            int start, end, cost;
            scanf("%d", &start);
            scanf("%d", &end);
            scanf("%d", &cost);

            Node *startNode = nodeList[start];
            Node *endNode = nodeList[end];

            Edge *edge = new Edge{startNode, endNode, cost};
            startNode->edges.push_back(edge);
        }

        nodeList = djikstra(nodeList,startIndex);

        for(int i =0; i < numQueries; i++){
            long long int endNodeIndex;
            scanf("%lld", &endNodeIndex);

            if(endNodeIndex >= numNodes || nodeList[endNodeIndex]->distance == numeric_limits<long long int>::max()){
                printf("%s\n","Impossible");
            }else{
                printf("%lld\n",nodeList[endNodeIndex]->distance);
            }
        }
        printf("\n");
}
}
