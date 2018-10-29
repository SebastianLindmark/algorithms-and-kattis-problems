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

using namespace std;


int getOccurenceIndex(char c, string word) {

    for (int i = word.size() - 1; i >= 0; i--) {
        if (word[i] == c) {
            return i;
        }
    }
    return -1;
}

int main() {


    int runs;
    cin >> runs;
    //runs = 2;

    for (int r = 0; r < runs; r++) {
        unordered_map<char, int> frequencies;
        string originalWord;
        cin >> originalWord;


        for (char c : originalWord) {
            auto it = frequencies.find(c);
            if (it == frequencies.end()) {
                frequencies.insert({c, 1});
            } else {
                frequencies.insert({c, it->second++});
            }
        }

        bool impossible = false;
        bool foundUnevenFrequency = false;
        char unevenChar;
        for (auto iter = frequencies.begin(); iter != frequencies.end(); ++iter) {

            if (iter->second % 2 != 0) {
                if (foundUnevenFrequency) {
                    cout << "Impossible" << endl;
                    impossible = true;
                    break;
                } else {
                    foundUnevenFrequency = true;
                    unevenChar = iter->first;
                }
            }
        }


        if (impossible) {
            continue;
        }

        int distanceSum = 0;
        int indexOffset = 0;
        for (int i = 0; i < originalWord.size() / 2; i++) {

            //cout << "Shifting " << originalWord[i] << endl;
            int reversedIndex = originalWord.size() - 1 - i + indexOffset;
            bool found = false;
            int distanceToMove = 0;
            for (int k = reversedIndex; k > i; k--) {

                if (originalWord[i] == originalWord[k]) {
                    distanceToMove = reversedIndex - k;
                    distanceSum += distanceToMove;
                    string c = string(1, originalWord[k]);
                    originalWord.erase(k, 1);
                    originalWord.insert(reversedIndex, c);
                    found = true;
                    break;
                }
            }
            if(!found){
                indexOffset = 1;
            }
        }


        if (foundUnevenFrequency) {

            for (int i = 0; i < originalWord.size() / 2; i++) {
                int reversedIndex = originalWord.size() - 1 - i;

                if (originalWord[i] != originalWord[reversedIndex]) {
                    int halfsize = originalWord.size() / 2;
                    distanceSum += halfsize - i;
                    string c = string(1, originalWord[i]);
                    originalWord.erase(i, 1);
                    originalWord.insert(halfsize, c);
                    //cout << "Have to move word " << halfsize - i << endl;
                    break;
                }
            }
        }
        cout << distanceSum << endl;
        //cout << originalWord << endl;
    }
//xvhkctloekvtvvoilgmvjqjholpbbojtkaqvecvmpgglcjxtgvfbpfipppakc
    return 0;
}








