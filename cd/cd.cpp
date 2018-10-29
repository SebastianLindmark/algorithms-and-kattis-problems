#include <iostream>


void readInput(){
    while(true){
        long int noOfJack;
        long int noOfJill;

        std::cin >> noOfJack >> noOfJill;

        if(noOfJack == 0 && noOfJill == 0){
            return;
        }

        int jackCDIndexes[noOfJack];
        int jillCDIndexes[noOfJill];


        for(int i = 0; i < noOfJack; ++i){
            std::cin >> jackCDIndexes[i];
        }

        for(int i = 0; i < noOfJill; i++){
            std::cin >> jillCDIndexes[i];
        }

        int cdsToSell = 0;
        int lastFoundJillIndex = 0;

        for(int i = 0; i < noOfJack;i++){
            for(int k = lastFoundJillIndex; k < noOfJill; k++){
                if(jackCDIndexes[i] == jillCDIndexes[k]){
                    cdsToSell++;
                    lastFoundJillIndex = k + 1;
                    break;
                }else if(jackCDIndexes[i] < jillCDIndexes[k]){
                    break;
                }
            }
        }
        std::cout << cdsToSell << std::endl;
    }



}



int main()
{
    readInput();
    return 0;
}
