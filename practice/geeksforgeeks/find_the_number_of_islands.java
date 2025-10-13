// LEETCODE 200, but with diagonal cells treated as adjacent

import java.util.Arrays;

// For directions
import java.util.List;
import java.util.ArrayList;

// For the BFS solution
import java.util.Queue;
import java.util.LinkedList;

class Cell {
    private int i;
    private int j;
    
    public Cell(int i, int j) {
        this.i = i;
        this.j = j;
    }
    
    public int getI() {
        return i;
    }
    
    public int getJ() {
        return j;
    }
    
    public void add(Cell other) {
        this.i += other.getI();
        this.j += other.getJ();
    }
}

class Solution {
    // GFG version
    private static final char LAND_SYMBOL = 'L';
    private static final char WATER_SYMBOL = 'W';

    // LeetCode version
    // private static final char LAND_SYMBOL = '1';
    // private static final char WATER_SYMBOL = '0';

    private static List<Cell> initializeDirectionList() {
        List<Cell> directions = new ArrayList<>();
        directions.add(new Cell(-1, 0)); // N
        directions.add(new Cell(0, 1)); // E
        directions.add(new Cell(1, 0)); // S
        directions.add(new Cell(0, -1)); // W

        // Diagonal directions: GFG version only
        directions.add(new Cell(-1, 1)); // NE
        directions.add(new Cell(1, 1)); // SE
        directions.add(new Cell(1, -1)); // SW
        directions.add(new Cell(-1, -1)); // NW
        return directions;
    }
    
    private static boolean gridDegenerated(char[][] grid) {
        return grid.length == 0 || grid[0].length == 0;
    }
    
    private static boolean cellInBounds(char[][] grid, int i, int j) {
        // Verify that the grid is not degenerated
        if (gridDegenerated(grid))
            return false;
        
        // Verify i (rows)
        if (i < 0 || i >= grid.length)
            return false;
            
        // Verify j (columns)
        if (j < 0 || j >= grid[0].length)
            return false;
            
        return true;
    }
    
    private static boolean cellInBounds(char[][] grid, Cell cell) {
        return cellInBounds(grid, cell.getI(), cell.getJ());
    }
    
    private static void gridBFS(char[][] grid, List<Cell> directions, int startI, int startJ) {
        if (gridDegenerated(grid) || !cellInBounds(grid, startI, startJ) || grid[startI][startJ] != LAND_SYMBOL)
            return; // Nothing to do here
        
        // Initialize queue
        Queue<Cell> bfsCellQueue = new LinkedList<>();
        
        // Add the first cell to the queue (and replace it with water immediately)
        grid[startI][startJ] = WATER_SYMBOL;
        bfsCellQueue.add(new Cell(startI, startJ));
        
        
        // While queue is not empty, take the cell, process it (replace with water)
        // and add its neighbors to the queue
        while (!bfsCellQueue.isEmpty()) {
            
            // Take the cell
            Cell currCell = bfsCellQueue.remove();
            int currI = currCell.getI(), currJ = currCell.getJ();
            
            // DEBUG
            // System.out.printf("Visited (%d, %d) -- %c\n", currI, currJ, grid[currI][currJ]);
            
            // TLE!!! Replacing with water here leads to duplicates
            // grid[currI][currJ] = 'W';
            
            // Add neighbors to the queue
            for (Cell direction : directions) {
                // Determine the next cell to visit
                Cell nextCell = new Cell(currI, currJ);
                nextCell.add(direction);
                
                // Validate the cell
                if (!cellInBounds(grid, nextCell))
                    continue;
                
                // Skip the cell if it has no land (do not add them to the queue)
                int nextI = nextCell.getI(), nextJ = nextCell.getJ();
                if (grid[nextI][nextJ] != LAND_SYMBOL)
                    continue;
                
                // Add the cell to the queue so that it can be visited.
                // Replace with water at the same time (doing it after removing
                // the element from the queue will lead to duplicates and unnecessary
                // visits).
                grid[nextI][nextJ] = WATER_SYMBOL;
                bfsCellQueue.add(nextCell);
            }
        }
    }
    
    // Inner method
    // ASSUMPTIONS:
    // - the grid has a positive width and height (i.e. is not degenerated)
    // - the cell exists (i, j are not out of bounds)
    // - the cell has not been visited
    // - the cell has value 'L' (land)
    private static void gridDFSVisit(char[][] grid, List<Cell> directions, int currI, int currJ) {
        // Visit the current cell + replace it by water
        grid[currI][currJ] = WATER_SYMBOL;
        
        // Recursively visit the neighbors
        for (Cell direction : directions) {
            // Determine the next cell to visit
            Cell nextCell = new Cell(currI, currJ);
            nextCell.add(direction);
            
            // Skip cells that are out of bounds
            if (!cellInBounds(grid, nextCell))
                continue;
            
            // Skip cells that have no land
            int nextI = nextCell.getI();
            int nextJ = nextCell.getJ();
            if (grid[nextI][nextJ] != LAND_SYMBOL)
                continue;
            
            // Visit a cell with land
            gridDFSVisit(grid, directions, nextI, nextJ);
        }
    }
    
    // DFS driver function
    private static void gridDFS(char[][] grid, List<Cell> directions, int startI, int startJ) {
        if (gridDegenerated(grid) || !cellInBounds(grid, startI, startJ) || grid[startI][startJ] != LAND_SYMBOL)
            return; // Nothing to do here
        
        // Visited array -- not necessary as we mark the visited cells with 'W' (Water => do not visit)
        // Visit the current cell and (recursively) its neighbors
        gridDFSVisit(grid, directions, startI, startJ);
    }
    

    // numIslands in LeetCode version
    public int countIslands(char[][] grid) {
        if (gridDegenerated(grid))
            return 0;
        
        List<Cell> directions = initializeDirectionList();
        int islandsCount = 0;
        
        for (int i = 0; i < grid.length; i++)  {
            for (int j = 0; j < grid[i].length; j++) {
                // Skip water
                if (grid[i][j] != LAND_SYMBOL)
                    continue;
                
                // Island found: add it to the counter and run DFS or BFS
                islandsCount++;
                // gridDFS(grid, directions, i, j); // DFS version
                gridBFS(grid, directions, i, j); // BFS version
            }
        }
        
        return islandsCount;
    }
}