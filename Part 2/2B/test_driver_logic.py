from rotting_fruit import Solution

def test():
    # Grid: [[2,1,1],[1,1,0],[0,1,1]]
    # Expected: 4 minutes
    grid = [[2,1,1],[1,1,0],[0,1,1]]
    expected = 4
    
    sol = Solution()
    result = sol.orangesRotting(grid)
    
    if result == expected:
        print(f"Test Passed: Time to rot is {result}")
    else:
        print(f"Test Failed: Expected {expected}, got {result}")

if __name__ == "__main__":
    test()
