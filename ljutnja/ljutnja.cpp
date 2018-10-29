#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;


int main() {

    int numChildren;
    int numCandy;


    cin >> numCandy;
    cin >> numChildren;

    vector<int> children(numChildren);
    for (int i = 0; i < numChildren; ++i) {
        cin >> children[i];
    }
    children.push_back(0);


    sort(children.begin(), children.end(), std::greater<int>());

    vector<long long int> result(numChildren);

    for (int i = 0; i < children.size() - 1; i++) {

        int elementsToReduce = i + 1;
        int diff = children[i] - children[i + 1];
        int minimum = diff;
        //watch out for infinite loops! -- Done!
        if (minimum * elementsToReduce > numCandy) {
            //spread it out
            int rounds = numCandy / elementsToReduce;
            int left = numCandy % elementsToReduce;
            //Should finish and calculate

            int value = (children[i] - rounds); //the amount the children will be reduced by

            for (int k = 0; k <= i; k++) {

                if (k < left) {
                    result[k] = value - 1;
                } else {
                    result[k] = value;
                }
            }

            for (int k = i + 1; k < result.size(); k++) {
                result[k] = children[k];
            }

            numCandy = 0;

            break;


        } else {
            numCandy -= minimum * elementsToReduce;
        }

    }

    if (numCandy > 0) {
        cout << 0;
        return 0;
    }

    long long int sum = 0;


    for (int i = 0; i < result.size(); i++) {
        long int value = result[i];
        long int sqrt_val = value*value;
        sum += sqrt_val;
    }

    cout << sum << endl;


}