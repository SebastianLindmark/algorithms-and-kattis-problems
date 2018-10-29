#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int print_num(int number) {


    int index = 0;
    int base7 = 1;


    while (number >= base7) {
        base7 *= 7;
    }
    base7 /= 7;

    vector<int> result;
    int x = number;
    while (base7 >= 1) {
        int res = x / base7;
        if (res == 3) {
            res = 5;
        } else if (res == 4) {
            res = 9;
        } else if (res == 5) {
            res = 8;
        }
        result.push_back(res);
        x = x % base7;
        base7 /= 7;
    }

    reverse(result.begin(), result.end());
    for (auto res : result) {
        cout << res;
    }

    cout << endl;


    return 0;
}


int main() {


    int number;
    while (cin >> number) {
        print_num(number);
    }

    return 0;
}