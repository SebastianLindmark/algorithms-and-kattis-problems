#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <bits/unordered_set.h>
#include <cmath>
#include <iomanip>

using namespace std;

double polygonArea(vector<double> &X, vector<double> &Y, int numPoints) {

    double area = 0;
    int j = numPoints - 1;

    for (int i = 0; i < numPoints; i++) {

        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i;
    }

    return area / 2;
}


int main() {

    int numPoints;
    while (true) {
        cin >> numPoints;

        if (numPoints == 0) {
            return 0;
        }
        vector<double> X;
        vector<double> Y;
        for (int i = 0; i < numPoints; i++) {
            double x, y;
            cin >> x >> y;
            X.push_back(x);
            Y.push_back(y);
        }

        double res = polygonArea(X, Y, numPoints);
        if (res < 0) {
            std::cout << "CCW ";
        } else {
            std::cout << "CW " ;
        }
        printf("%.1f\n",abs(res));
    }


    return 0;
}