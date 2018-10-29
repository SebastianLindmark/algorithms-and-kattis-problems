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


struct Line{

public:
    Line(double _x1, double _y1, double _x2, double _y2){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }

    double x1,x2,y1,y2;

    double getDistance(){
        double xDiff = (x1-x2);
        double yDiff = (y1-y2);
        return sqrt(xDiff * xDiff +  yDiff * yDiff);
    }

};


double calculateArea(vector<Line> & lines){
    double s = (lines[0].getDistance() + lines[1].getDistance() + lines[2].getDistance())/2;
    double area = sqrt(s* (s  - lines[0].getDistance())* (s  - lines[1].getDistance()) * (s  - lines[2].getDistance()));
    return area;
}


double calculateAngle(vector<Line> & lines, int index){

    double a = lines[0].getDistance();
    double b = lines[1].getDistance();
    double c = lines[2].getDistance();

    double oppositeLength, side1,side2;

    if(index == 0){
        oppositeLength = b;
        side1 = a;
        side2 = c;
    }else if(index == 1) {
        oppositeLength = c;
        side1 = a;
        side2 = b;
    }else if(index == 2){
        oppositeLength = a;
        side1 = b;
        side2 = c;
    }

    double angle = acos(((oppositeLength * oppositeLength) - (side1 * side1) - (side2 * side2)) / (-2*side1 * side2));
    return angle * (180.0 / M_PI);

}


int main() {
//3 3 3 4 5 3
        int numTriangles;
        cin  >> numTriangles;

        for(int p = 0; p < numTriangles; p++){

            vector<Line> lines;

            int x1,x2,x3,y1,y2,y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            lines.push_back(Line{x1,y1,x2,y2});
            lines.push_back(Line{x2,y2,x3,y3});
            lines.push_back(Line{x1,y1,x3,y3});


            if(calculateArea(lines) > 0.01){
                cout << "Case #" << p + 1<< ":" << " ";
                double angle1 = calculateAngle(lines,0);
                double angle2 = calculateAngle(lines,1);
                double angle3 = calculateAngle(lines,2);

                double a = lines[0].getDistance();
                double b = lines[1].getDistance();
                double c = lines[2].getDistance();

                double deg90 = 90.0;
                double epsilon = 0.00001;

                if(abs(a - b) > epsilon && abs(a - c) > epsilon && abs(b-c) > epsilon){
                    cout << "scalene ";
                }else if (abs(a - b) < epsilon || abs(a - c) < epsilon || abs(b-c) < epsilon){
                    cout << "isosceles ";
                }

////1 1 1 4 3 2
//21 -104 -112 30 287 -372



                if(abs(angle1 - deg90) < epsilon || abs(angle2 - deg90) < epsilon || abs(angle3 - deg90) < epsilon){
                    cout << "right ";

                }else if(angle1 - deg90 > epsilon || angle2 - deg90 > epsilon || angle3 - deg90 > epsilon){
                    cout << "obtuse ";
                }else{
                    cout << "acute ";
                }

                cout << "triangle" << endl;
            }else{
                cout << "Case #" << p + 1 << ":" << " not a triangle" << endl;
            }


        }



        return 0;
    }
