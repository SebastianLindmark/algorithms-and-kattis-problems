#include <iostream>
#include <queue>
using namespace std;

void loadCars(int lengthOfFerry,queue<int>& cars){
    int carsAtFerryLength = 0;

    while(!cars.empty() && carsAtFerryLength + cars.front() <= lengthOfFerry){
        int carLength = cars.front();
        cars.pop();
        carsAtFerryLength += carLength;
     }
}



int calculateWaitingTurns(bool atLeftDock,int lengthOfFerry,queue<int>& leftCars,queue<int>& rightCars){
    int turns = 0;

    while(!leftCars.empty() || !rightCars.empty()){
        if(atLeftDock){
            loadCars(lengthOfFerry,leftCars);
            atLeftDock = false;
        }else{
            loadCars(lengthOfFerry,rightCars);
            atLeftDock= true;
        }
        turns++;
    }

    return turns;

}


const string string_left = "left";

void readInput(){
    int noOfTestCases = 0;
    std::cin >> noOfTestCases;
    for(int i = 0; i < noOfTestCases; ++i){
        int lengthOfFerry = 0;
        int noOfCars = 0;

        std::cin >> lengthOfFerry;
        std::cin >> noOfCars;

        lengthOfFerry *= 100;

        queue<int> leftCars;
        queue<int> rightCars;

        for(int i = 0; i < noOfCars; ++i){

            int lengthOfCar = 0;
            string startPosition = "";


            std::cin >> lengthOfCar;
            std::cin >> startPosition;

            if(startPosition == string_left){
                leftCars.push(lengthOfCar);
            }else{
                rightCars.push(lengthOfCar);
            }
        }

        int turns = calculateWaitingTurns(true,lengthOfFerry,leftCars,rightCars);
        std::cout << turns << std::endl;
}
}




int main()
{
    readInput();
}