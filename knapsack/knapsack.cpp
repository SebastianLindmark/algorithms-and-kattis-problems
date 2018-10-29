//Author Sebastian Lindmark

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * The struct to store the pair cost and weight
 * */
struct ValueWeight {
public:
    ValueWeight(long long int c, long long int w) {
        cost = c;
        weight = w;
    }

    long long int getValue() {
        return cost;
    }

    long long int getWeight() {
        return weight;
    }

private:
    long long int cost;
    long long int weight;
};

/*
 * This function calculates the maximum value given maximum capacity, using DP.
 * Returns the indices of the rows used in the result
 *
 */
vector<long long int> knapsack(int numElems, int capacity, vector<ValueWeight> &valueWeight) {

    long long int mtx[numElems][capacity];

    for (int i = 0; i < numElems; i++) {
        for (int j = 0; j < capacity; j++) {
            long long int currentValue = valueWeight[i].getValue();
            long long int currentWeight = valueWeight[i].getWeight();

            if (j == 0 || i == 0) {
                mtx[i][j] = 0;
                continue;
            }
            if (i != 0) {
                if (currentWeight <= j) {
                    long long int diff = j - currentWeight;
                    long long int max = std::max(currentValue + mtx[i - 1][diff], mtx[i - 1][j]);
                    mtx[i][j] = max;
                } else {
                    mtx[i][j] = mtx[i - 1][j];
                }
            }
        }
    }

    vector<long long int> result;
    long long int row = numElems - 1;
    long long int col = capacity - 1;
    while (true) {
        if (row <= 0 || col < 0 || mtx[row][col] == 0) {
            break;
        } else if (mtx[row][col] != mtx[row - 1][col]) {
            result.push_back(row - 1); //-1 since we have empty first row
            long long int currentWeight = valueWeight[row].getWeight();
            col -= currentWeight;
        }
        row -= 1;
    }


    //Prints the matrix for debug purpose

    /*for (int i = 0; i < numElems; i++) {
        for (int j = 0; j < capacity; j++) {
            cout << mtx[i][j] << " ";
        }
        cout << endl;
    }*/

    return result;
}


int main() {


    float c;
    while (cin >> c) {

        long long int numElems;
        cin >> numElems;
        long long int capacity = (long long int) c + 1;
        vector<ValueWeight> valueWeight;
        valueWeight.push_back(ValueWeight(1337, 1337)); //Push back a dummy to compensate for the empty initial row

        for (int i = 0; i < numElems; i++) {
            long long int cost, weight;
            cin >> cost;
            cin >> weight;
            valueWeight.push_back(ValueWeight(cost, weight));
        }

        numElems += 1; //compensate for initial empty row
        vector<long long int> result = knapsack(numElems, capacity, valueWeight);

        cout << result.size() << endl;
        for (auto elem : result) {
            cout << elem << " ";
        }
        cout << endl;
    }
    return 0;
}