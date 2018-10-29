#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <map>
#include <bitset>

using namespace std;


vector<int> split(string s, int size) {


    vector<int> result;
    int i = 0;
    while (i < s.length()) {

        if (s[i] == 'v') {
            i += 2;
        } else if (s[i] == 'X') {
            result.push_back(stoi(s.substr(i + 1)));
            i += 2;
        } else if (s[i] == '~') {
            result.push_back((stoi(s.substr(i + 2)) * -1));
            i += 3;
        } else {
            i += 1;
        }
    }
    return result;
}


int main() {

    int numTests;
    cin >> numTests;

    for (int tLoop = 0; tLoop < numTests; tLoop++) {

        int numVariables, numClauses;
        cin >> numVariables >> numClauses;
        cin.ignore();

        vector<vector<int>> variables;

        for (int i = 0; i < numClauses; i++) {
            string line;
            std::getline(std::cin, line);
            vector<int> result = split(line, numVariables);
            variables.push_back(result);
        }
        bool haveResult = false;
        for (int integer = 0; integer < pow(2, numVariables); integer++) {
            bitset<20> bs(integer);
            bool satisfiedEverything = true;
            for (vector<int> clause : variables) {
                bool satisfiedClause = false;
                for (int i = 0; i < clause.size(); i++) {

                    if (clause[i] > 0) {
                        if (bs[abs(clause[i]) - 1] == 1) {
                            satisfiedClause = true;
                            break;
                        }
                    } else {

                        if (bs[abs(clause[i]) - 1] == 0) {
                            satisfiedClause = true;
                            break;
                        }
                    }
                }

                    if (!satisfiedClause) {
                        satisfiedEverything = false;
                        break;
                    }
                }

                if (satisfiedEverything) {
                    haveResult = true;
                    break;
                }
            }

            if (haveResult) {
                cout << "satisfiable" << endl;
            } else {
                cout << "unsatisfiable" << endl;
            }
        }

        return 0;

    }
