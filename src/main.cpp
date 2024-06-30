#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "maze.h"

#define SIDE_TOP 1
#define SIDE_RIGHT 2
#define SIDE_BOTTOM 3
#define SIDE_LEFT 4

// Initialization
int screenWidth = 800 * 2;
int screenHeight = 450 * 2;
int mazeSize = 5;
int cellSize = 100;

void DrawOutline(int x, int y, int w, int h, int thickness, Color outline, Color inside)
{
    // fillllllllll
    DrawRectangle((x)-w / 2, (y)-h / 2, w, h, inside);

    // outlaine
    for (int i = 0; i < thickness; i++)
    {
        DrawRectangleLines((x)-w / 2 - i, (y)-h / 2 - i, w + 2 * i, h + 2 * i, outline);
    }
}

void DrawGridLines(int x, int y, int w, int h, int cellSize, Color lineColor, std::vector<std::vector<std::vector<int>>> &cellSides)
{
    int left = x - w / 2;
    int top = y - h / 2;
    int rows = cellSides.size();
    int cols = cellSides[0].size();
    int paddedCellSize = cellSize;

        for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            int cellX = left + col * paddedCellSize;
            int cellY = top + row * paddedCellSize;

            //dont ask
            if (std::find(cellSides[row][col].begin(), cellSides[row][col].end(), SIDE_TOP) == cellSides[row][col].end())
            {
                if (row == 0 || std::find(cellSides[row-1][col].begin(), cellSides[row-1][col].end(), SIDE_BOTTOM) == cellSides[row-1][col].end())
                {
                    DrawLine(cellX, cellY, cellX + cellSize, cellY, lineColor);
                }
            }
            if (std::find(cellSides[row][col].begin(), cellSides[row][col].end(), SIDE_RIGHT) == cellSides[row][col].end())
            {
                if (col == cols - 1 || std::find(cellSides[row][col+1].begin(), cellSides[row][col+1].end(), SIDE_LEFT) == cellSides[row][col+1].end())
                {
                    DrawLine(cellX + cellSize, cellY, cellX + cellSize, cellY + cellSize, lineColor);
                }
            }
            if (std::find(cellSides[row][col].begin(), cellSides[row][col].end(), SIDE_BOTTOM) == cellSides[row][col].end())
            {
                if (row == rows - 1 || std::find(cellSides[row+1][col].begin(), cellSides[row+1][col].end(), SIDE_TOP) == cellSides[row+1][col].end())
                {
                    DrawLine(cellX, cellY + cellSize, cellX + cellSize, cellY + cellSize, lineColor);
                }
            }
            if (std::find(cellSides[row][col].begin(), cellSides[row][col].end(), SIDE_LEFT) == cellSides[row][col].end())
            {
                if (col == 0 || std::find(cellSides[row][col-1].begin(), cellSides[row][col-1].end(), SIDE_RIGHT) == cellSides[row][col-1].end())
                {
                    DrawLine(cellX, cellY, cellX, cellY + cellSize, lineColor);
                }
            }
        }
    }
}

int main()
{

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Maze generator");

    SetTargetFPS(60);

    Maze test(mazeSize, mazeSize);
    test.generate();
    test.displayMaze();

    std::vector<std::vector<std::vector<int>>> maze = test.getMaze();

    // TraceLog(LOG_INFO, "info");

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawOutline(screenWidth / 2, screenHeight / 2, cellSize * mazeSize, cellSize * mazeSize, 5, BLACK, RAYWHITE);
        DrawGridLines(screenWidth / 2, screenHeight / 2, cellSize * mazeSize, cellSize * mazeSize, cellSize, RED, maze);
        EndDrawing();
    }

    return 0;
}
