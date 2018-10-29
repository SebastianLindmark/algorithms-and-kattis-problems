//Author Sebastian Lindmark

#include <iostream>
#include <vector>

using namespace std;


struct Node {
public:
    Node(long long int r,long long int d) : rank{r}, data{d} {};
    long long int rank;
    long long int data;
    Node *parent;
};


Node *getParent(Node *node) {
    if (node->parent->data != node->data) {
        node->parent = getParent(node->parent);
    }
    return node->parent;
}


void unionSets(Node *node1, Node *node2) {
    Node *rootNode1 = getParent(node1);
    Node *rootNode2 = getParent(node2);


    if (rootNode1->data != rootNode2->data) {

        if (rootNode1->rank > rootNode2->rank) {
            rootNode2->parent = rootNode1;
        } else if (rootNode1->rank < rootNode2->rank) {
            rootNode1->parent = rootNode2;
        } else {
            rootNode1->rank = rootNode1->rank + 1;
            rootNode2->parent = rootNode1;
        }
    }
}

bool unionFind(Node *node1, Node *node2) {
    return getParent(node1)->data == getParent(node2)->data;
}

int main() {

    long long int numElems;
    long long int lines;

    scanf("%lld", &numElems);
    scanf("%lld", &lines);

    vector<Node *> arr;

    for (long long int i = 0; i < numElems; i++) {
        Node *node = new Node(0, i);
        node->parent = node;
        arr.push_back(node);
    }


    for (long long int i = 0; i < lines; i++) {
        char c;
        scanf(" %c", &c);

        long long int index1, index2;
        scanf("%lld", &index1);
        scanf("%lld", &index2);

        if (c == '?') {
            if (unionFind(arr[index1], arr[index2])) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else {
            unionSets(arr[index1], arr[index2]);
        }
    }


    return 0;
}