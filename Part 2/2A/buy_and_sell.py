from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) < 2 : return 0
        max_pro = 0
        min_buy= float('inf')
        for price in prices:
            if price < min_buy:
                min_buy = price
            elif price-min_buy>max_pro:
                max_pro = price- min_buy
        return max_pro
