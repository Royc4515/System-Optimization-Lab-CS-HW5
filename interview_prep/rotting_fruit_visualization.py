"""
Interactive Visualization Tool for the Rotting Fruit Problem

This module provides a visual representation of how rot spreads through a grid
of fresh and rotten fruits using matplotlib animations and numpy for efficient
grid state management.

The visualization displays:
- Fresh fruits (green)
- Rotten fruits (red)
- Empty cells (white)
- Grid state evolution at each minute
- Time progression with smooth animations
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.animation import FuncAnimation
from matplotlib.colors import ListedColormap, BoundaryNorm
from collections import deque
from typing import List, Tuple, Optional
import time


class RottingFruitVisualizer:
    """
    A visualization tool for simulating and displaying the Rotting Fruit problem.
    
    The grid uses the following color scheme:
    - 0: Empty cell (white)
    - 1: Fresh fruit (green)
    - 2: Rotten fruit (red)
    """
    
    # Color definitions for the grid states
    COLORS = ['white', 'green', 'red']
    COLOR_MAP = ListedColormap(COLORS)
    NORM = BoundaryNorm([-0.5, 0.5, 1.5, 2.5], len(COLORS))
    
    # Grid cell values
    EMPTY = 0
    FRESH = 1
    ROTTEN = 2
    
    def __init__(self, grid: List[List[int]], speed: float = 0.5):
        """
        Initialize the visualizer with a grid configuration.
        
        Args:
            grid: 2D list where 0=empty, 1=fresh, 2=rotten
            speed: Animation speed multiplier (0.1 to 2.0)
        """
        self.original_grid = np.array(grid, dtype=int)
        self.grid = self.original_grid.copy()
        self.rows, self.cols = self.grid.shape
        self.speed = speed
        self.minute = 0
        self.time_states = [self.grid.copy()]
        self.queue = deque()
        self.directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
        
        # Initialize queue with rotten fruits
        self._initialize_rotten_queue()
        
        # Simulate the entire process to get all states
        self.all_states = self._simulate_all_states()
        self.max_minutes = len(self.all_states) - 1
        
    def _initialize_rotten_queue(self) -> None:
        """Find all initially rotten fruits and add them to the queue."""
        self.queue = deque()
        for i in range(self.rows):
            for j in range(self.cols):
                if self.grid[i, j] == self.ROTTEN:
                    self.queue.append((i, j, 0))
    
    def _simulate_all_states(self) -> List[np.ndarray]:
        """
        Simulate the entire rotting process and return all grid states.
        
        Returns:
            List of grid states, one for each minute
        """
        grid = self.original_grid.copy()
        states = [grid.copy()]
        queue = deque()
        
        # Find all initially rotten fruits
        for i in range(self.rows):
            for j in range(self.cols):
                if grid[i, j] == self.ROTTEN:
                    queue.append((i, j))
        
        minute = 0
        while queue:
            minute += 1
            next_queue = deque()
            
            # Process all rotten fruits at current minute
            while queue:
                row, col = queue.popleft()
                
                # Spread rot to adjacent fresh fruits
                for dr, dc in self.directions:
                    new_row, new_col = row + dr, col + dc
                    
                    # Check bounds
                    if 0 <= new_row < self.rows and 0 <= new_col < self.cols:
                        if grid[new_row, new_col] == self.FRESH:
                            grid[new_row, new_col] = self.ROTTEN
                            next_queue.append((new_row, new_col))
            
            # Add state if rot spread this minute
            if next_queue:
                states.append(grid.copy())
            queue = next_queue
        
        return states
    
    def create_visualization(self, show_grid_lines: bool = True) -> None:
        """
        Create and display an interactive animation of the rotting process.
        
        Args:
            show_grid_lines: Whether to display grid lines (default: True)
        """
        fig, (ax, info_ax) = plt.subplots(
            1, 2, figsize=(14, 6),
            gridspec_kw={'width_ratios': [1, 1]}
        )
        
        # Set up main grid plot
        ax.set_xlim(-0.5, self.cols - 0.5)
        ax.set_ylim(-0.5, self.rows - 0.5)
        ax.set_aspect('equal')
        ax.invert_yaxis()
        ax.set_xlabel('Column', fontsize=11, fontweight='bold')
        ax.set_ylabel('Row', fontsize=11, fontweight='bold')
        ax.set_title('Rotting Fruit Grid Visualization', fontsize=13, fontweight='bold')
        
        # Set up grid lines if requested
        if show_grid_lines:
            ax.set_xticks(np.arange(-0.5, self.cols, 1), minor=True)
            ax.set_yticks(np.arange(-0.5, self.rows, 1), minor=True)
            ax.grid(which='minor', color='gray', linestyle='-', linewidth=0.5, alpha=0.3)
        
        # Create image for grid display
        im = ax.imshow(
            self.all_states[0],
            cmap=self.COLOR_MAP,
            norm=self.NORM,
            interpolation='nearest'
        )
        
        # Set up info plot (text display)
        info_ax.axis('off')
        info_text = info_ax.text(
            0.05, 0.95,
            '',
            transform=info_ax.transAxes,
            fontsize=11,
            verticalalignment='top',
            fontfamily='monospace',
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8)
        )
        
        # Legend
        legend_text = info_ax.text(
            0.05, 0.45,
            'Legend:\n🟩 Empty (0)\n🟩 Fresh (1)\n🟥 Rotten (2)',
            transform=info_ax.transAxes,
            fontsize=10,
            verticalalignment='top',
            bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.8)
        )
        
        def update_frame(frame: int) -> None:
            """Update animation frame."""
            state = self.all_states[min(frame, len(self.all_states) - 1)]
            im.set_array(state)
            
            # Count fresh and rotten fruits
            fresh_count = np.sum(state == self.FRESH)
            rotten_count = np.sum(state == self.ROTTEN)
            
            info_text.set_text(
                f'Minute: {frame}\n'
                f'Fresh Fruits: {fresh_count}\n'
                f'Rotten Fruits: {rotten_count}\n'
                f'Grid Size: {self.rows}×{self.cols}\n'
                f'Status: {"Complete" if fresh_count == 0 else "Spreading"}'
            )
            
            return im, info_text
        
        # Create animation
        interval = int(1000 / (self.speed * 2))  # milliseconds per frame
        anim = FuncAnimation(
            fig, update_frame,
            frames=self.max_minutes + 2,
            interval=interval,
            repeat=True,
            repeat_delay=2000,
            blit=False
        )
        
        plt.tight_layout()
        plt.show()
    
    def create_step_by_step_visualization(self, minutes_to_show: Optional[int] = None) -> None:
        """
        Create a static multi-panel visualization showing step-by-step progression.
        
        Args:
            minutes_to_show: Number of key states to display (default: show all)
        """
        if minutes_to_show is None:
            states_to_show = self.all_states
            frame_indices = list(range(len(self.all_states)))
        else:
            # Show evenly distributed states
            num_states = min(minutes_to_show, len(self.all_states))
            frame_indices = np.linspace(0, len(self.all_states) - 1, num_states, dtype=int)
            states_to_show = [self.all_states[i] for i in frame_indices]
        
        num_states = len(states_to_show)
        cols = min(4, num_states)
        rows_needed = (num_states + cols - 1) // cols
        
        fig, axes = plt.subplots(rows_needed, cols, figsize=(15, 4 * rows_needed))
        if rows_needed == 1 and cols == 1:
            axes = np.array([[axes]])
        elif rows_needed == 1 or cols == 1:
            axes = axes.reshape(rows_needed, cols)
        
        axes = axes.flatten()
        
        for idx, (state, ax) in enumerate(zip(states_to_show, axes)):
            ax.imshow(state, cmap=self.COLOR_MAP, norm=self.NORM, interpolation='nearest')
            ax.set_title(f'Minute {frame_indices[idx]}', fontweight='bold')
            ax.set_xticks([])
            ax.set_yticks([])
            
            # Add grid lines
            for i in range(self.rows + 1):
                ax.axhline(i - 0.5, color='black', linewidth=0.5)
            for j in range(self.cols + 1):
                ax.axvline(j - 0.5, color='black', linewidth=0.5)
            
            # Statistics
            fresh = np.sum(state == self.FRESH)
            rotten = np.sum(state == self.ROTTEN)
            ax.text(
                0.5, -0.15,
                f'Fresh: {fresh}, Rotten: {rotten}',
                transform=ax.transAxes,
                ha='center',
                fontsize=9
            )
        
        # Hide unused subplots
        for ax in axes[num_states:]:
            ax.set_visible(False)
        
        plt.suptitle('Rotting Fruit Problem: Step-by-Step Progression', 
                     fontsize=14, fontweight='bold', y=0.995)
        plt.tight_layout()
        plt.show()
    
    def get_time_to_rot_all(self) -> int:
        """
        Get the time (in minutes) when all fresh fruits become rotten.
        
        Returns:
            Minutes needed to rot all fruits, or -1 if impossible
        """
        if not self.all_states:
            return 0
        
        final_state = self.all_states[-1]
        if np.any(final_state == self.FRESH):
            return -1  # Some fruits will never rot
        
        return len(self.all_states) - 1
    
    def print_simulation_summary(self) -> None:
        """Print a summary of the simulation results."""
        initial_state = self.original_grid
        final_state = self.all_states[-1]
        
        initial_fresh = np.sum(initial_state == self.FRESH)
        initial_rotten = np.sum(initial_state == self.ROTTEN)
        final_fresh = np.sum(final_state == self.FRESH)
        final_rotten = np.sum(final_state == self.ROTTEN)
        
        time_to_rot = self.get_time_to_rot_all()
        
        print("=" * 50)
        print("ROTTING FRUIT SIMULATION SUMMARY")
        print("=" * 50)
        print(f"Grid Size: {self.rows}×{self.cols}")
        print(f"\nInitial State:")
        print(f"  Fresh Fruits: {initial_fresh}")
        print(f"  Rotten Fruits: {initial_rotten}")
        print(f"  Empty Cells: {np.sum(initial_state == self.EMPTY)}")
        print(f"\nFinal State:")
        print(f"  Fresh Fruits: {final_fresh}")
        print(f"  Rotten Fruits: {final_rotten}")
        print(f"  Empty Cells: {np.sum(final_state == self.EMPTY)}")
        print(f"\nTime to Rot All Fruits: {time_to_rot} minutes" 
              if time_to_rot >= 0 else "\nResult: Cannot rot all fruits")
        print("=" * 50)


def example_visualization_1():
    """Example 1: Simple 3x3 grid."""
    grid = [
        [2, 1, 1],
        [1, 1, 1],
        [1, 1, 1]
    ]
    visualizer = RottingFruitVisualizer(grid, speed=1.0)
    visualizer.print_simulation_summary()
    visualizer.create_visualization()


def example_visualization_2():
    """Example 2: Larger grid with obstacles."""
    grid = [
        [2, 1, 1, 0, 1],
        [1, 0, 1, 1, 1],
        [1, 1, 2, 1, 0],
        [0, 1, 1, 1, 1],
        [1, 1, 1, 0, 2]
    ]
    visualizer = RottingFruitVisualizer(grid, speed=1.0)
    visualizer.print_simulation_summary()
    visualizer.create_step_by_step_visualization(minutes_to_show=6)


def example_visualization_3():
    """Example 3: Grid where not all fruits can rot."""
    grid = [
        [2, 1, 1],
        [0, 0, 0],
        [1, 1, 1]
    ]
    visualizer = RottingFruitVisualizer(grid, speed=1.0)
    visualizer.print_simulation_summary()
    visualizer.create_visualization()


if __name__ == "__main__":
    print("Rotting Fruit Problem - Interactive Visualization Tool\n")
    print("Select an example to visualize:")
    print("1. Simple 3x3 grid")
    print("2. Larger 5x5 grid with obstacles")
    print("3. Grid with unreachable fruits")
    
    choice = input("\nEnter choice (1-3) or press Enter for animation demo: ").strip()
    
    if choice == "1":
        print("\nRunning Example 1...")
        example_visualization_1()
    elif choice == "2":
        print("\nRunning Example 2...")
        example_visualization_2()
    elif choice == "3":
        print("\nRunning Example 3...")
        example_visualization_3()
    else:
        print("\nRunning Example 1 (Animation)...")
        example_visualization_1()
