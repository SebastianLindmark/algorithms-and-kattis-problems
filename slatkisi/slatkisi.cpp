//Author Sebastian Lindmark

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {

    long long int price;
    long long int zeroes;
    cin >> price;
    cin >> zeroes;

    long long int billSize = 1;
    for (int i = 0; i < zeroes; i++) {
        billSize *= 10;
    }

    long double p = ((long double )price) / ((long double )billSize);
    cout << std::fixed <<(int)(std::round(p) * billSize) << endl;

    return 0;
}