#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <bits/unordered_set.h>

//Author Sebastian Lindmark

using namespace std;

int main() {
    //                  0       1       2     3      4      5      6       7
    string words[8] = {"NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

    int choices[8][3] =
            {
                    {1, 2, 4}, // NNN
                    {5, 3, 0}, //NNY
                    {6, 0, 3}, //NYN
                    {7, 1, 2}, //NYY
                    {0, 6, 5}, //YNN
                    {1, 7, 4}, //YNY
                    {2, 4, 7}, //YYN
                    {3, 5, 6} //YYY
            };

    int testCases;
    int numPriests;
    cin >> testCases;


    for (int tc = 0; tc < testCases; tc++) {
        cin >> numPriests;
        int preistPriorities[numPriests][8];
        for (int p = 0; p < numPriests; p++) {
            for (int i = 0; i < 8; i++) {
                int choice;
                cin >> choice;
                preistPriorities[p][i] = choice - 1; //fix the index offset
            }
        }

        int result[8];
        for (int i = 0; i < 8; i++) {
            result[i] = i;
        }

        for (int i = numPriests - 1; i >= 0; i--) {
            int temp[8];
            for (int selection = 0; selection < 8; selection++) {
                int choice1 = choices[selection][0];
                int choice2 = choices[selection][1];
                int choice3 = choices[selection][2];

                int index1 = result[choice1];
                int index2 = result[choice2];
                int index3 = result[choice3];

                int prioVal1 = preistPriorities[i][index1];
                int prioVal2 = preistPriorities[i][index2];
                int prioVal3 = preistPriorities[i][index3];

                vector<int> minArray{prioVal1, prioVal2, prioVal3};
                vector<int>::iterator result = std::min_element(std::begin(minArray), std::end(minArray));
                int minIndex = std::distance(std::begin(minArray), result);

                if (minIndex == 0) {
                    temp[selection] = index1;
                } else if (minIndex == 1) {
                    temp[selection] = index2;
                } else {
                    temp[selection] = index3;
                }
            }

            for (int i = 0; i < 8; i++) {
                result[i] = temp[i];
            }

        }
        string finalword = words[result[0]];
        cout << finalword << endl;

    }
}