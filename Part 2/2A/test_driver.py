from buy_and_sell import Solution

def test():
    prices = [7, 1, 5, 3, 6, 4]
    expected = 5
    sol = Solution()
    result = sol.maxProfit(prices)
    if result == expected:
        print(f"Test Passed: Max Profit is {result}")
    else:
        print(f"Test Failed: Expected {expected}, got {result}")

if __name__ == "__main__":
    test()
