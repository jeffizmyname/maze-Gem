#pragma once
#include <vector>

class Maze {

private: 
    int width {0};
    int height {0};

    std::vector<std::vector<std::vector<int>>> maze;

public:
    //constructors
    Maze();
    Maze(int w, int h);

    //getters setters
    std::vector<std::vector<std::vector<int>>> getMaze();

    //methodes
    void generate();
    void displayMaze();
    bool compare(std::vector<int>& v1, std::vector<int>& v2);
    void addValueIfNotPresent(std::vector<int>& vec, int value);
    bool areEqual(const std::vector<int>& vec1, const std::vector<int>& vec2);
    bool isFull();

};