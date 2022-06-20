#include <stdio.h>

int maxProfit(int* prices, int pricesSize){
    int maxprofit = 0;
    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] > prices[i-1]) maxprofit += prices[i] - prices[i-1];
    }
    return maxprofit;
}

void main() {
    int prices[6] = {7, 1, 5, 3, 6, 4};
    printf("%d", maxProfit(prices, 6));
}


//动态规划？