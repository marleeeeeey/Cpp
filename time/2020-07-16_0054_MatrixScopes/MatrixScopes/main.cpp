#include <iostream>
#include <vector>

const int defaultValue = -1;

int getScope(std::vector<std::vector<int>> & matrix, size_t x, size_t y)
{
    if (x >= matrix.size() || y >= matrix.at(0).size()) return 0;

    if (matrix[x][y] == defaultValue)
        matrix[x][y] = getScope(matrix, x - 1, y) + getScope(matrix, x, y - 1);

    return matrix[x][y];
}

int main()
{
    size_t sizeX = 4;
    size_t sizeY = 4;
    std::vector<std::vector<int>> matrix(sizeX, std::vector<int>(sizeY, defaultValue));
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 0;

    std::cout << getScope(matrix, sizeX-1, sizeY-1);
}