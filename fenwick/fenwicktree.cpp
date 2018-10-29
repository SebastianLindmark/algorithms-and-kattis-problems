#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>

//Author Sebastian Lindmark

using namespace std;

/*
 * Stores the Fenwick tree. Implements functions to sum and to change the tree
*/

struct BitTree {
public:
    BitTree(long long int s) {
        size = s;

        for (long long int i = 0; i < s; i++) {
            biTree.push_back(0);
            arr.push_back(0);
        }
        biTree.push_back(0);

        create_tree();
    }

    /*
     * Creates an empty tree
     *
    */
    void create_tree() {
        for (long long int i = 0; i < size; i++) {
            update_tree(i, arr[i]);
        }
    }

    /*
     * Updates the biTree using 2^index jumps
    */
    void update_tree(long long int i, long long int value) {
        long long int index{i + 1};
        while (index <= size) {
            biTree[index] += value;
            index = index + (index & (-index));
        }
    }

    void add(long long int index, long long int value) {
        update_tree(index, value);
    }

    /*
     * Using 2^index steps to sum from 0 to index.
     *
    */

    long long int sum(long long int index) {
        long long int sum = 0;
        while (index > 0) {
            sum += biTree[index];
            index = index - (index & (-index));
        }
        return sum;
    }

    long long int size;
    vector<long long int> biTree;
    vector<long long int> arr;
};

int main() {

    long long int size, operations;
    scanf("%lld", &size);
    scanf("%lld", &operations);

    BitTree bitTree(size);

    for (long long int i = 0; i < operations; i++) {
        char op;
        scanf(" %c", &op);

        if (op == '+') {
            long long int n1, n2;
            scanf("%lld", &n1);
            scanf("%lld", &n2);
            bitTree.add(n1, n2);
        } else {
            long long int n1;
            scanf("%lld", &n1);
            printf("%lld\n", bitTree.sum(n1));
        }
    }

    return 0;
}