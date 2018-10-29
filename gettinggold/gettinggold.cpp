#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>

#include <queue>

//Author Sebastian Lindmark

using namespace std;


bool inside_bounds(vector<vector<char>> &arr, int col, int row) {
    return row >= 0 && row < arr.size() && col >= 0 && col < arr[0].size();
}


bool inside_bounds(vector<vector<char>> &arr, pair<int, int> pos) {
    return inside_bounds(arr, pos.first, pos.second) && arr[pos.second][pos.first] != '#';

}

bool isDraft(vector<vector<char>> &arr, int col, int row) {
    if (inside_bounds(arr, col + 1, row) && arr[row][col + 1] == 'T') {
        return true;
    }

    if (inside_bounds(arr, col - 1, row) && arr[row][col - 1] == 'T') {
        return true;
    }

    if (inside_bounds(arr, col, row + 1) && arr[row + 1][col] == 'T') {
        return true;
    }

    if (inside_bounds(arr, col, row - 1) && arr[row - 1][col] == 'T') {
        return true;
    }

    return false;

}


int main() {
    int cols, rows;
    cin >> cols;
    cin >> rows;

    vector<vector<char>> arr;
    int playerCol = 0;
    int playerRow = 0;
    int gold = 0;

    bool visited[rows][cols];
    for (int row = 0; row < rows; row++) {
        vector<char> vec;
        for (int col = 0; col < cols; col++) {
            char c;
            cin >> c;

            visited[row][col] = false;
            if (c == 'P') {
                playerCol = col;
                playerRow = row;
                c = '.'; //heh, hax by haxxor
            }
            vec.push_back(c);
        }
        arr.push_back(vec);
    }

    //unordered_map<pair<int, int>, bool> visited;



    vector<pair<int, int>> unvisited;
    unvisited.push_back(make_pair(playerCol, playerRow));

    while (!unvisited.empty()) {

        pair<int, int> &pos = unvisited.front();
        if (!visited[pos.second][pos.first]) {

            auto pos = unvisited[0];
            int col = pos.first;
            int row = pos.second;

            if (arr[row][col] == '.' || arr[row][col] == 'G') {

                if (!isDraft(arr, col, row)) {


                    pair<int, int> nb1{col, row + 1};
                    pair<int, int> nb2{col, row - 1};
                    pair<int, int> nb3{col + 1, row};
                    pair<int, int> nb4{col - 1, row};

                    if (inside_bounds(arr, nb1) && !visited[nb1.second][nb1.first]) {
                        unvisited.push_back(nb1);
                    }

                    if (inside_bounds(arr, nb2) && !visited[nb2.second][nb2.first]) {
                        unvisited.push_back(nb2);
                    }

                    if (inside_bounds(arr, nb3) && !visited[nb3.second][nb3.first]) {
                        unvisited.push_back(nb3);
                    }

                    if (inside_bounds(arr, nb4) && !visited[nb4.second][nb4.first]) {
                        unvisited.push_back(nb4);
                    }

                }


                if (arr[row][col] == 'G') {
                    gold++;
                }
            }
            visited[pos.second][pos.first] = true;
        }
        unvisited.erase(unvisited.begin());
    }

    cout << gold << endl;

}
