from collections import deque
from typing import List

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        """
        Determines the minimum time (in minutes) for all fresh oranges to rot.
        Uses BFS (Breadth-First Search) to simulate the spreading of rot.
        
        Args:
            grid: 2D list where 0=empty, 1=fresh, 2=rotten
            
        Returns:
            Minimum minutes for all fresh oranges to rot, or -1 if impossible
        """
        
        # === SETUP PHASE ===
        # Create a Queue
        queue = deque()
        
        # Variable – Fresh Count (number of fresh oranges)
        fresh_count = 0
        
        # Variable – Time (minutes passed)
        time = 0
        
        # First Pass (Setup):
        # Go through the entire matrix, cell by cell
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                # If the cell is Rotten:  Add it to the Queue immediately
                if grid[row][col] == 2:
                    queue.append((row, col))
                # If the cell is Fresh: Add +1 to the Fresh Count
                elif grid[row][col] == 1:
                    fresh_count += 1
                # If the cell is Empty: Do nothing
        
        # === MAIN LOOP (The Infection) ===
        # Run this loop as long as the Queue is not empty AND Fresh Count > 0
        while queue and fresh_count > 0:
            # Start of Minute:  Add +1 to the Time
            time += 1
            
            # The Wave:  Check the current size of the Queue
            # We will only process this specific number of oranges (this represents one minute of spreading)
            queue_size = len(queue)
            
            # For each orange in this current wave
            for _ in range(queue_size):
                row, col = queue.popleft()
                
                # Check its 4 adjacent neighbors (Up, Down, Left, Right)
                neighbors = [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]
                
                for neighbor_row, neighbor_col in neighbors: 
                    # Bounds check
                    if 0 <= neighbor_row < len(grid) and 0 <= neighbor_col < len(grid[0]):
                        # If the neighbor is Fresh: 
                        if grid[neighbor_row][neighbor_col] == 1:
                            # Change it to Rotten in the matrix (so we don't count it twice)
                            grid[neighbor_row][neighbor_col] = 2
                            
                            # Subtract 1 from the Fresh Count
                            fresh_count -= 1
                            
                            # Add it to the Queue (it will infect others in the next minute)
                            queue.append((neighbor_row, neighbor_col))
                        
                        # If the neighbor is Rotten or Empty:  Do nothing
        
        # === FINAL CHECK ===
        # Check if Fresh Count is 0:
        if fresh_count == 0:
            # If yes:  We successfully rotted everything.  Return the Time.
            return time
        else:
            # If no: Some oranges are isolated and safe. Return -1.
            return -1