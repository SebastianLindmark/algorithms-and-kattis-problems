#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {

public:
    Interval(double _a, double _b, double _length, int _index) : a{_a}, b{_b}, length{_length}, index{_index} {};
    double a;
    double b;
    double length;
    int index;
};

vector<Interval> find_intervals(double B, Interval lastFoundInterval, vector<Interval> &intervals) {
    vector<Interval> result;

    for (auto it2 = intervals.begin(); it2 != intervals.end(); ++it2) {
        Interval foundInterval(-1, lastFoundInterval.b, -1, -1);
        auto bestMatchIterator = intervals.begin();
        for (auto it = it2; it != intervals.end(); ++it) {
            Interval interval = *it;

            if (interval.a <= lastFoundInterval.b && interval.b >= B) {
                //we have found a valid solution
                result.push_back(interval);
                return result;
            } else if (interval.a <= lastFoundInterval.b && interval.b > foundInterval.b) {
                foundInterval = interval;
                bestMatchIterator = it;
            }

        }
        if (foundInterval.index == -1) {
            //no valid solution
            return {};
        } else {
            //we have found an interval.
            result.push_back(foundInterval);
            foundInterval.index = -1; //reset the foundInterval index.
            foundInterval.length = -1; //reset the foundInterval length.
            lastFoundInterval = foundInterval;
            it2 = bestMatchIterator;
        }
    }

    return {};
}

int main() {
    double A;
    double B;


    while (cin >> A >> B) {
        int numIntervals;
        cin >> numIntervals;

        vector<Interval> intervals;

        for (int i = 0; i < numIntervals; ++i) {
            double a, b;
            cin >> a;
            cin >> b;

            if (a < A) {
                a = A;
            }
            if (b > B) {
                b = B;
            }

            double length = b - a;
            intervals.push_back(Interval(a, b, length, i));
        }


        sort(intervals.begin(), intervals.end(), [](Interval &i1, Interval &i2) {
            return i1.a < i2.a;
        });

        //find the longest starting interval
        Interval startingInterval{-1, -1, -1, -1};
        auto startingIntervalIt = intervals.begin();
        for (auto it = intervals.begin(); it != intervals.end(); ++it) {
            Interval interval = *it;
            if (interval.a <= A) {
                if (interval.length >= startingInterval.length) {
                    startingInterval = interval;
                    startingIntervalIt = it;
                }
            } else {
                //Since ordered by a, no one can be before/on A.
                break;
            }
        }

        if (startingInterval.index == -1) {
            cout << "impossible" << endl;
        } else if (startingInterval.a <= A && startingInterval.b >= B) {
            cout << "1" << endl;
            cout << startingInterval.index << endl;
        } else {
            Interval startingIntervalCopy = startingInterval;
            intervals.erase(startingIntervalIt);

            Interval lastFoundInterval = startingInterval;
            vector<Interval> result = find_intervals(B, startingInterval, intervals);

            if (result.empty()) {
                cout << "impossible" << endl;
            } else {
                result.push_back(startingIntervalCopy);
                cout << result.size() << endl;
                for (int i = 0; i < result.size(); ++i) {
                    cout << result[i].index << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;

}