#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <bits/unordered_set.h>

using namespace std;

int forward = 0;
int left = 1;
int back = 2;
int backward = 3;


struct Dice {

public:
    Dice(int r, int c) {
        row = r;
        col = c;
    }

    void actionForward() {
        int tempUp, tempDown, tempForward, tempBackward;

        tempDown = forward;
        tempForward = up;
        tempBackward = down;
        tempUp = backward;

        down = tempDown;
        forward = tempForward;
        backward = tempBackward;
        up = tempUp;
    }

    void actionBackward() {
        int tempUp, tempDown, tempForward, tempBackward;

        tempDown = backward;
        tempForward = down;
        tempBackward = up;
        tempUp = forward;

        down = tempDown;
        forward = tempForward;
        backward = tempBackward;
        up = tempUp;
    }

    void actionLeft() {
        int tempUp, tempDown, tempLeft, tempRight;

        tempDown = left;
        tempLeft = up;
        tempRight = down;
        tempUp = right;

        down = tempDown;
        left = tempLeft;
        right = tempRight;
        up = tempUp;
    }

    void actionRight() {
        int tempUp, tempDown, tempLeft, tempRight;

        tempDown = right;
        tempLeft = down;
        tempRight = up;
        tempUp = left;

        down = tempDown;
        left = tempLeft;
        right = tempRight;
        up = tempUp;
    }


    void doAction(int action) {
        if (action == 0) {
            actionForward();
            row--;
        } else if (action == 1) {
            actionBackward();
            row++;
        } else if (action == 2) {
            actionLeft();
            col--;
        } else if (action == 3) {
            actionRight();
            col++;
        }
    }

    int up = 1;
    int down = 6;
    int forward = 4;
    int backward = 3;
    int right = 2;
    int left = 5;


    int row;
    int col;

};


struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int> &v) const {
        return v.first * 31 + v.second;
    }
};

int main() {
    int numTestCases;
    cin >> numTestCases;

    for (int testCase = 0; testCase < numTestCases; testCase++) {

        int mapSize;
        cin >> mapSize;

        string map[mapSize][mapSize];
        unordered_set<pair<int, int>, pair_hash> visited[mapSize][mapSize];

        int startRow;
        int startCol;

        int goalRow;
        int goalCol;

        for (int row = 0; row < mapSize; row++) {
            for (int col = 0; col < mapSize; col++) {
                char ground;
                cin >> ground;
                map[row][col] = ground;
                if (ground == 'S') {
                    startRow = row;
                    startCol = col;
                }

                if (ground == 'H') {
                    goalRow = row;
                    goalCol = col;
                }
            }
        }

        Dice d{startRow, startCol};
        queue<Dice> unvisited;
        unvisited.emplace(d);

        while (!unvisited.empty()) {
            Dice current = unvisited.front();
            unvisited.pop();

            for (int i = 0; i < 4; i++) {

                Dice copy = current;
                copy.doAction(i);
                if (copy.row >= 0 && copy.row < mapSize && copy.col >= 0 && copy.col < mapSize) {

                    if (map[copy.row][copy.col] != "*") {
                        pair<int, int> dir = make_pair(copy.down, copy.forward);
                        if (visited[copy.row][copy.col].find(dir) == visited[copy.row][copy.col].end()) {
                            visited[copy.row][copy.col].emplace(dir);
                            unvisited.emplace(copy);
                        }
                    }

                }
            }
        }

        bool found = false;
        for (int i = 1; i < 7; i++) {
            pair<int, int> dir = make_pair(5, i);
            if (visited[goalRow][goalCol].find(dir) != visited[goalRow][goalCol].end()) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }

    }


    return 0;
}