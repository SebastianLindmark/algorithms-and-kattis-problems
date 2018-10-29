#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

#include <queue>

//Author Sebastian Lindmark

using namespace std;


pair<int, int> getHorsePosition(int i) {
    if (i == 0) {
        return make_pair(-1, 2);
    } else if (i == 1) {
        return make_pair(1, 2);
    } else if (i == 2) {
        return make_pair(2, -1);
    } else if (i == 3) {
        return make_pair(2, 1);
    } else if (i == 4) {
        return make_pair(-1, -2);
    } else if (i == 5) {
        return make_pair(1, -2);
    } else if (i == 6) {
        return make_pair(-2, 1);
    } else if (i == 7) {
        return make_pair(-2, -1);
    }
}

string getHorseCharacter(int i) {
    if (i == 0) {
        return "a";
    } else if (i == 1) {
        return "b";
    } else if (i == 2) {
        return "c";
    } else if (i == 3) {
        return "d";
    } else if (i == 4) {
        return "e";
    } else if (i == 5) {
        return "f";
    } else if (i == 6) {
        return "g";
    } else if (i == 7) {
        return "h";
    }


}


int stringToInt(string pos) {
    if (pos == "a") {
        return 0;
    } else if (pos == "b") {
        return 1;
    } else if (pos == "c") {
        return 2;
    } else if (pos == "d") {
        return 3;
    } else if (pos == "e") {
        return 4;
    } else if (pos == "f") {
        return 5;
    } else if (pos == "g") {
        return 6;
    } else if (pos == "h") {
        return 7;
    }
}


struct Position {
public:
    Position(int r, int c, int s) : row{r}, col{c}, steps{s} {}

    int row = 0;
    int col = 0;
    int steps = 0;

    string getKey() {
        return getHorseCharacter(col) + to_string(row);
    }

    string getKeyAsKattisWantIt() {
        return getHorseCharacter(col) + to_string(row + 1);
    }

};

int main() {


    int cases;
    scanf("%d", &cases);

    for (int i = 0; i < cases; i++) {

        vector<vector<string>> found;

        for (int i = 0; i < 8; i++) {
            vector<string> res;
            found.push_back(res);
        }


        string pos;
        cin >> pos;
        int col = stringToInt(pos.substr(0, 1));
        int row = stoi(pos.substr(1, 2)) - 1;
        row = 7 - row;

        Position p{row, col, 0};

        queue<Position> unvisited;
        unvisited.emplace(p);
        unordered_map<string, bool> visited;

        while (!unvisited.empty()) {
            Position startPosition = unvisited.front();
            unvisited.pop();
            for (int i = 0; i < 8; i++) {
                pair<int, int> horseJump = getHorsePosition(i);
                Position newPosition{startPosition.row + horseJump.first, startPosition.col + horseJump.second,
                                     startPosition.steps};

                if (newPosition.row >= 0 && newPosition.row < 8 && newPosition.col >= 0 && newPosition.col < 8) {

                    if (visited.find(newPosition.getKey()) == visited.end()) {
                        //cout << "Visiting " << newPosition.row << " " << getHorseCharacter(newPosition.col) << endl;
                        visited[newPosition.getKey()] = true;
                        newPosition.steps++;
                        unvisited.emplace(newPosition);
                        found[newPosition.steps].push_back(newPosition.getKey());
                    }

                }
            }

        }

        for (int i = 7; i >= 0; i--) {
            if (found[i].size() > 0) {


                vector<string> result = found[i];

                sort(result.begin(), result.end(), [](string &s1, string &s2) {
                    string col1 = s1.substr(0, 1);
                    int row1 = 7 - stoi(s1.substr(1, 2)) + 1;


                    string col2 = s2.substr(0, 1);
                    int row2 = 7 - stoi(s2.substr(1, 2)) + 1;

                    if(row1 == row2){
                        return col1 < col2;
                    }
                    return row1 > row2;

                });


                cout << i << " ";
                for (int loop = 0; loop < result.size(); loop++) {
                    string key = result[loop];
                    string col = key.substr(0, 1);
                    int row = 7 - stoi(key.substr(1, 2)) + 1;
                    cout << col + to_string(row) << " ";
                }
                cout << endl;
                break;
            }
        }

    }


    return 0;
}