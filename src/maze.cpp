#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "maze.h"

Maze::Maze() {}

Maze::Maze(int w, int h)
{
    width = w;
    height = h;
    maze.resize(width, std::vector<std::vector<int>>(height, std::vector<int>()));
}

void Maze::generate()
{
    int currRow = height - 1;
    int currCol = 0;
    int lastCell = 0;
    std::vector<int> checkDirections;
    std::vector<int> dirTemplate = {1, 2, 3, 4};

    while (true)
    {
        /*
        *
        ?   wich direction you can move (free space no wall)
        *
        *   1 up
        *   2 right
        *   3 down
        *   4 left
        */
        int randomDirection = GetRandomValue(1, 4);

        switch (randomDirection)
        {
        case 1:
            if (currRow > 0 && maze[currRow - 1][currCol].empty())
            {
                maze[currRow][currCol].push_back(randomDirection);
                lastCell = randomDirection;
                currRow--;
                checkDirections.clear();
            }
            else
            {
                addValueIfNotPresent(checkDirections, randomDirection);
            }
            break;

        case 2:
            if (currCol < width - 1 && maze[currRow][currCol + 1].empty())
            {
                maze[currRow][currCol].push_back(randomDirection);
                lastCell = randomDirection;
                currCol++;
                checkDirections.clear();
            }
            else
            {
                addValueIfNotPresent(checkDirections, randomDirection);
            }
            break;

        case 3:
            if (currRow < height - 1 && maze[currRow + 1][currCol].empty())
            {
                maze[currRow][currCol].push_back(randomDirection);
                lastCell = randomDirection;
                currRow++;
                checkDirections.clear();
            }
            else
            {
                addValueIfNotPresent(checkDirections, randomDirection);
            }
            break;

        case 4:
            if (currCol > 0 && maze[currRow][currCol - 1].empty())
            {
                maze[currRow][currCol].push_back(randomDirection);
                lastCell = randomDirection;
                currCol--;
                checkDirections.clear();
            }
            else
            {
                addValueIfNotPresent(checkDirections, randomDirection);
            }
            break;

        default:
            std::cout << "Invalid direction" << std::endl;
            break;
        }

        std::cout << "------------------------" << std::endl;
        for (int dir : checkDirections)
        {
            std::cout << dir << " ";
        }
        std::cout << std::endl;

        std::cout << "Direction: " << randomDirection << std::endl;
        std::cout << "Current position: " << currRow << " " << currCol << std::endl;

        displayMaze();

        if (compare(checkDirections, dirTemplate))
        {
            int last = 0;
            switch (lastCell)
            {
            case 1:
                last = 3;
                break;
            case 2:
                last = 4;
                break;
            case 3:
                last = 1;
                break;
            case 4:
                last = 2;
                break;
            default:
                break;
            }
            maze[currRow][currCol].push_back(last);
            break;
        }
    }
}

void Maze::displayMaze()
{
    std::cout << "Maze dimensions: " << maze.size() << "x" << maze[0].size() << "x" << maze[0][0].size() << std::endl;
    std::cout << "Maze content:" << std::endl;
    std::cout << "{" << std::endl;
    for (size_t i = 0; i < maze.size(); ++i)
    { // iterate over rows
        std::cout << " ";
        std::cout << "{";
        for (size_t j = 0; j < maze[i].size(); ++j)
        { // iterate over columns
            std::cout << "{";
            for (size_t k = 0; k < maze[i][j].size(); ++k)
            { // iterate over layers
                if(maze[i][j].size() == 0) {
                    std::cout << "0";
                } else {
                    std::cout << maze[i][j][k];
                }
                if (k != maze[i][j].size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "}";
            if (j != maze[i].size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        if (i != maze.size() - 1)
        {
            std::cout << "," << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}

bool Maze::areEqual(const std::vector<int> &vec1, const std::vector<int> &vec2)
{
    if (vec1.size() != vec2.size())
    {
        return false; // Vectors are not equal if they have different sizes
    }

    for (size_t i = 0; i < vec1.size(); ++i)
    {
        if (vec1[i] != vec2[i])
        {
            return false; // Vectors are not equal if corresponding elements differ
        }
    }

    return true; // Vectors are equal
}

bool Maze::compare(std::vector<int> &v1, std::vector<int> &v2)
{
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}

void Maze::addValueIfNotPresent(std::vector<int> &vec, int value)
{
    if (std::find(vec.begin(), vec.end(), value) == vec.end())
    {
        vec.push_back(value);
    }
}


//----------------------------------//
//     The not important stuff      //
//----------------------------------//

std::vector<std::vector<std::vector<int>>> Maze::getMaze() {
    return maze;
}