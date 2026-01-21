#include <stdio.h>
#include <stdlib.h>
#include "buy_and_sell.c"

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int size = 6;
    int expected = 5; // Buy at 1, sell at 6
    
    int result = maxProfit(prices, size);
    
    if (result == expected) {
        printf("Test Passed: Max Profit is %d\n", result);
        return 0;
    } else {
        printf("Test Failed: Expected %d, got %d\n", expected, result);
        return 1;
    }
}
