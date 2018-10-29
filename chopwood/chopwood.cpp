#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {

    int n;
    scanf("%d", &n);
    int tree[n];
    unordered_map<int, int> parentValens;
    for (int i = 0; i < n; ++i) {
        int input;
        scanf("%d", &input);
        tree[i] = input;
        parentValens[input] += 1;
    }

    int currentMin = 1;
    if (tree[n - 1] != n + 1) {
        printf("%s", "Error");
    } else {
        for (int j = 0; j < n; ++j) {
            int cur = tree[j];
            if (j > 0 && currentMin > tree[j - 1] && parentValens[tree[j - 1]] == 0) {
                printf("%d\n", tree[j - 1]);
                parentValens[cur] -= 1;
                continue;
            } else {
                for (int i = currentMin; i <= n; ++i) {
                    if (parentValens[i] == 0) {
                        printf("%d\n", i);
                        parentValens[cur] -= 1;
                        currentMin = i + 1;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}