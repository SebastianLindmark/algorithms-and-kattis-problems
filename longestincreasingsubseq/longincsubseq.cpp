#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <cmath>

//Author Sebastian Lindmark

using namespace std;


vector<int> lis(vector<int> &original, int n) {
    int LIS[n + 1];
    int parent[n];
    int maxLengthFound = 0;

    for (int i = 0; i < n; i++) {
        int low = 1;
        int high = maxLengthFound;

        while (low <= high) {
            int mid = std::ceil((low + high) / 2);
            if (original[LIS[mid]] < original[i]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        parent[i] = LIS[low - 1];
        LIS[low] = i;


        if (low > maxLengthFound) {
            maxLengthFound = low;
        }
    }

    //int res[maxLengthFound];
    vector<int> res;
    int nextIndex = LIS[maxLengthFound];
    for (int k = maxLengthFound - 1; k >= 0; k--) {
        res.push_back(nextIndex);
        nextIndex = parent[nextIndex];
    }

    return res;
}


int main() {

    int maxLengthFound = 0;
    int n;
    while (cin >> n) {

        int parent[n];
        vector<int> original;
        int LIS[n];
        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;
            original.push_back(num);
            LIS[i] = 0;
            parent[i] = 0;
        }
        vector<int> result = lis(original, n);
        cout << result.size() << endl;

        for (int i = result.size() - 1; i >= 0; i--) {
            cout << result[i] << " ";
        }
    }
    return 0;
}