#include <iostream>
#include <stdlib.h>

using namespace std;


long int count(long int n) {

    long int result = 0;
    long int i = 1;
    long int a,b,c = 0;

    while(true) {
        auto divRem = div(n, i);
        b = divRem.quot;
        c = divRem.rem;
        auto divRem2 = div(b, 10L);
        a = divRem2.quot;
        b = divRem2.rem;

        if (a == 0) {
            return result;
        }

        if (b == 0) {
            result += (a - 1) * i + c + 1;
        } else {
            result += a * i;
        }

        i *= 10;
    }
}

int main()
{
    long int upperBound, lowerBound;
    while(cin >> lowerBound) {

        cin >> upperBound;

        if (lowerBound == -1 && upperBound == -1) {
            return 0;
        }

        long int high = count(upperBound);
        long int low = count(lowerBound);

//        cout << "HIGH "<<high << endl;
//        cout << "LOW "<< low << endl;

        if (lowerBound == 0) {
            cout << 1 + high << endl;
        } else {
            string lowString = to_string(lowerBound);
            int numZeroes = 0;
            for (int i = 0; i < lowString.length(); i++) {
                if (lowString[i] == '0') {
                    numZeroes += 1;
                }
            }
            cout << numZeroes + high - low << endl;
        }
    }
    return 0;
}







