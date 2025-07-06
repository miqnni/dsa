package leetcode

// import "fmt"

func islandPerimeter(grid [][]int) int {
	var startCellRow int
	var startCellCol int
	var startCellFound bool = false
	for row := 0; row < len(grid) && !startCellFound; row++ {
		for col := 0; col < len(grid[0]) && !startCellFound; col++ {
			if grid[row][col] == 1 {
				startCellRow = row
				startCellCol = col
				startCellFound = true
			}
		}
	}

	// fmt.Printf("%d , %d\n", startCellRow, startCellCol)

	perimeter := 0
	directions := [4][2]int{
		{-1, 0}, // N
		{0, 1},  // E
		{1, 0},  // S
		{0, -1}, // W
	}

	visited := make([][]bool, len(grid))
	for i := range visited {
		visited[i] = make([]bool, len(grid[0]))
	}

	var innerFunc func(int, int)
	islandDFS := func(currCellRow int, currCellCol int) {

		// fmt.Printf("-- CALL: (%d, %d)\n", currCellRow, currCellCol)

		visited[currCellRow][currCellCol] = true

		for _, dir := range directions {
			nextCellRow := currCellRow + dir[0]
			nextCellCol := currCellCol + dir[1]

			if nextCellRow < 0 || nextCellRow >= len(grid) || nextCellCol < 0 || nextCellCol >= len(grid[0]) || grid[nextCellRow][nextCellCol] == 0 {
				// fmt.Printf("Perimeter increased: from (%d, %d) to (%d, %d) \n", currCellRow, currCellCol, nextCellRow, nextCellCol)
				perimeter++
			} else if !visited[nextCellRow][nextCellCol] {
				// fmt.Printf("NOT VISITED\n")
				innerFunc(nextCellRow, nextCellCol)
			}
		}

	}

	innerFunc = islandDFS
	islandDFS(startCellRow, startCellCol)

	return perimeter
}
