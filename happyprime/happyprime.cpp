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


int isPrime(int num)
{
    bool foundPrime = true;

    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            foundPrime = false;
            break;
        }
    }
    return foundPrime;
}



bool isHappyPrime(int num){
    unordered_set<int> hasBeen;

    if(num == 1){
        return false;
    }

    while(num != 1) {
        if(hasBeen.find(num) != hasBeen.end()){
            break;
        }else{
            hasBeen.insert(num);
        }

        int sum = 0;
        string stringNum = std::to_string(num);
        for (int i = 0; i < stringNum.length(); i++) {
            int n = stoi(string(1, stringNum[i]));
            sum += n * n;
        }
        num = sum;
    }

    return num == 1;
}


int main() {

        int numTests;
        cin >> numTests;


        for(int t = 0; t < numTests; t++){
            int testNumber;
            int happyPrime;
            cin >> testNumber >> happyPrime;
            if(isPrime(happyPrime)){
                bool res = isHappyPrime(happyPrime);

                if(res){
                    cout << testNumber << " " << happyPrime << " YES" << endl;
                }else{
                    cout << testNumber << " " << happyPrime << " NO" << endl;
                }
            }else{
                cout << testNumber << " " << happyPrime << " NO" << endl;
            }
        }


        return 0;
    }
