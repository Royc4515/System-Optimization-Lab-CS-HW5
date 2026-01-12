#include <stdio.h>
#include <math.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize < 2) return 0;
    int max_pro = 0;
    int min_buy = INFINITY;
    for ( int i = 0; i< pricesSize; i++) {
        if (prices[i]<min_buy){
            min_buy= prices[i];
        }
        else if (prices[i]- min_buy > max_pro){
            max_pro = prices[i]- min_buy;
        }
    }
    return max_pro;
}

