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
    int historyPointer = 0;
    bool fillerDone = false;
    std::vector<int> checkDirections;
    std::vector<int> dirTemplate = {1, 2, 3, 4};
    std::vector<std::vector<int>> history = {};

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
                history.push_back({currRow, currCol});
                fillerDone = false;
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
                history.push_back({currRow, currCol});
                fillerDone = false;
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
                history.push_back({currRow, currCol});
                fillerDone = false;
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
                history.push_back({currRow, currCol});
                fillerDone = false;
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
            std::cout << "dead end" << std::endl;

            history.pop_back();
            std::vector<int> lastPos = history.back();

            //! jak cofło pozycje to sie to nie moze juz wykonywac
            std::cout << "1 " << fillerDone << std::endl;
            if (fillerDone == false)
            {
                std::cout << "2" << std::endl;
                int last = 0;
                switch (lastCell)
                {
                case 1:
                    last = 3;
                    fillerDone = true;
                    break;
                case 2:
                    last = 4;
                    fillerDone = true;
                    break;
                case 3:
                    last = 1;
                    fillerDone = true;
                    break;
                case 4:
                    last = 2;
                    fillerDone = true;
                    break;
                default:
                    break;
                }
                maze[currRow][currCol].push_back(last);
                std::cout << "3" << std::endl;
            }
            std::cout << "4" << std::endl;
            //! last pos sie sra o coś i nie działa
            std::cout << history.back()[0] << " " << history.back()[0] << std::endl;
            for (int i = 0; i < history.size(); i++)
            {
                std::cout << "5 " << history[i][0] << " " << history[i][1] << std::endl;
            }
            
            //std::cout << "4 " << lastPos[0] << " " << lastPos[1] << std::endl;

            currRow = lastPos[0];
            currCol = lastPos[1];
            std::cout << "5" << std::endl;

            for (int dir : lastPos)
            {
                std::cout << dir << " ";
            }
            std::cout << std::endl;

            if (isFull())
            {
                std::cout << "its full" << std::endl;
                break;
            }
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
                if (maze[i][j].size() == 0)
                {
                    std::cout << "0";
                }
                else
                {
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

bool Maze::isFull()
{
    for (int i = 0; i < maze.size(); ++i)
    {
        for (int j = 0; j < maze[0].size(); ++j)
        {
            if (maze[i][j].empty())
                return false;
        }
    }
    return true;
}

//----------------------------------//
//     The not important stuff      //
//----------------------------------//

std::vector<std::vector<std::vector<int>>> Maze::getMaze()
{
    return maze;
}