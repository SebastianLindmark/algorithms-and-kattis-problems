#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <bits/unordered_set.h>
#include <cmath>
#include <iomanip>

using namespace std;


int main() {


    long int upper, queries;
    cin >> upper;
    cin >> queries;

    vector<bool> increments(upper + 1);

    for (long int i = 0; i <= upper; i++) {
        increments[i] = true;
    }

    //Sieve of Eratosthenes
    for (long int i = 2; i <= sqrt(upper); i++) {

        if (increments[i] == true) {

            for (long int j = i * i; j <= upper; j += i) {
                increments[j] = false;
            }
        }
    }

    long int count = 0;
    for (long int i = 2; i <= upper; i++) {
        if (increments[i] == true) {
            count++;
        }
    }
    cout << count << endl;

    increments[0] = false;
    increments[1] = false;
    for (int i = 0; i < queries; i++) {
        long int number;
        cin >> number;
        if (increments[number]) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }


    return 0;
}