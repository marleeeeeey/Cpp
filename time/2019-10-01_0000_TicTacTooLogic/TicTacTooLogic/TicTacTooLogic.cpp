#include <iostream>
#include  <string>
#include <vector>
#include <cassert>

using Line = std::string;
using Lines = std::vector<std::string>;
using Matrix = Lines;

Lines getHorizontalLines(const Matrix & matrix)
{
    return matrix;
}

Lines getVerticalLines(const Matrix & matrix)
{
    if (matrix.empty())
    {
        return Lines();
    }

    Lines returnLines;
    returnLines.resize(matrix.at(0).size());

    for (unsigned row = 0; row < matrix.size(); row++)
    {
        auto horLine = matrix.at(row);
        for (unsigned col = 0; col < horLine.size(); col++)
        {
            auto curSimbol = horLine.at(col);
            returnLines[col].push_back(curSimbol);
        }
    }

    return returnLines;
}

Lines getDiagonalLines(const Matrix & matrix)
{
    if(matrix.empty())
    {
        return Lines();
    }

    auto squareSize = matrix.size();
    if(squareSize != 3)
    {
        throw std::exception("Size of matrix doesn't equale to 3");
    }

    Line leftDiag;
    Line rightDiag;

    for(unsigned i = 0; i < squareSize; i++)
    {
        if(matrix.at(i).size() != squareSize)
        {
            throw std::exception("It is not square matrix");            
        }

        auto ch01 = matrix[i][i];
        auto ch02 = matrix[i][squareSize - i - 1];
        leftDiag.push_back(ch01);
        rightDiag.push_back(ch02);
    }

    Lines allDiags{ leftDiag, rightDiag };

    return allDiags;
}

Lines getAllLines(const Matrix& matrix)
{
    Lines allLines;
    auto horLines = getHorizontalLines(matrix);
    auto verLines = getVerticalLines(matrix);
    auto diagLines = getDiagonalLines(matrix);
    allLines.insert(allLines.end(), horLines.begin(), horLines.end());
    allLines.insert(allLines.end(), verLines.begin(), verLines.end());
    allLines.insert(allLines.end(), diagLines.begin(), diagLines.end());
    return allLines;
}

int main()
{
    const Matrix matrix
    {
        "123",
        "456",
        "789",
    };
    Lines expectedDiags{ "159", "357" };
    Lines expectedVerticalLines{ "147", "258", "369" };
    Lines expectedAllLines
    {
        "123",
        "456",
        "789",
        "147",
        "258",
        "369",
        "159",
        "357",
    };

    assert(getHorizontalLines(matrix) == matrix);
    Lines diags = getDiagonalLines(matrix);
    assert(diags == expectedDiags);
    Lines verticalLines = getVerticalLines(matrix);
    assert(verticalLines == expectedVerticalLines);
    Lines allLines = getAllLines(matrix);
    assert(allLines == expectedAllLines);

    std::cout << "Test Passed!\n";
}
