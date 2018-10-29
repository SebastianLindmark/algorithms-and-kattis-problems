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


string run() {

    int stringLength, numSuffixes;
    cin >> stringLength >> numSuffixes;
    char word[stringLength];

    bool impossible = false;

    for (int i = 0; i < stringLength; i++) {
        word[i] = '*';
    }


    for (int i = 0; i < numSuffixes; i++) {

        int suffixStart;
        string subword;

        cin >> suffixStart;
        suffixStart -= 1;
        cin >> subword;

        bool foundStar = false;

        for (int k = 0; k < subword.length(); k++) {

            if(subword[k] == '*'){
                foundStar = true;
                break;
            }

            if (word[suffixStart + k] == subword[k] || word[suffixStart + k ] == '*') {
                word[suffixStart + k] = subword[k];
            }

            if(word[suffixStart + k ] != '*' && word[suffixStart + k] != subword[k]){
                impossible = true;
            }

        }

        for (int k = 0; k < subword.length() && foundStar; k++) {

            if(subword[subword.length() - 1 - k] == '*'){
                break;
            }


            if(word[stringLength - 1 - k ] == '*'){
                word[stringLength - 1 - k] = subword[subword.length() - 1 - k];
            }


            if(word[stringLength - 1 - k] != '*' && word[stringLength - 1 - k] != subword[subword.length() - 1 - k]){
                impossible = true;
            }


        }

    }

    if(impossible){
        return "IMPOSSIBLE";
    }

    string builder = "";
    for (int i = 0; i < stringLength; i++) {

        if (word[i] == '*') {
            return "IMPOSSIBLE";
        }
        builder += word[i];
    }

    return builder;


}

int main() {

    int testCases = 0;
    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        string result = run();
        cout << result << endl;
    }
}