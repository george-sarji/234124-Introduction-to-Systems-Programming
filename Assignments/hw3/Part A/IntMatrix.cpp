#include "Auxiliaries.h"
#include "IntMatrix.h"

namespace mtm
{
    mtm::IntMatrix::IntMatrix(Dimensions dims, int value)
    {
        // Get the row and column dimensions.
        rows = dims.getRow();
        cols = dims.getCol();
        // Create the required amount of rows.
        matrix = new int *[rows];
        // Iterate through the rows and assign each of them their own column data.
        for (int current = 0; current < rows; current++)
        {
            // Initiate current object to a col length array.
            matrix[current] = new int[cols];
            // Assign the default value into the current cell.
            for (int col = 0; col < cols; col++)
            {
                matrix[current][col] = value;
            }
        }
    }

    mtm::IntMatrix::IntMatrix(const IntMatrix &intMatrix)
    {
        // Assign the dims.
        // Get the dimensions as required.
        rows = intMatrix.height();
        cols = intMatrix.width();
        // Create the required rows in the matrix.
        matrix = new int *[rows];
        for (int row = 0; row < rows; row++)
        {
            matrix = new int *[cols];
            // Iterate through the items, assign the values.
            for (int col = 0; cols < col; col++)
            {
                matrix[row][col] = intMatrix.getCell(row, col);
            }
        }
    }

    // ! Functions

    IntMatrix mtm::IntMatrix::Identity(int dim)
    {
        // Create the dimensions.
        Dimensions dims(dim, dim);
        // Create a matrix according to said dims.
        IntMatrix matrix(dims);
        // Now iterate through the matrix and set the primary diagonal to 1.
        for (int i = 0; i < dim; i++)
        {
            // setCell to 1.
            matrix.setCell(i, i, 1);
        }
        // Return the constructed identity matrix.
        return matrix;
    }

    IntMatrix mtm::IntMatrix::transpose()
    {
        // Get the matrix dimensions.
        int rows = height();
        int cols = width();
        Dimensions dims(cols, rows);
        // Create a new matrix.
        IntMatrix transposed(dims);
        // Iterate over the original matrix and transpose.
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                // Assign the proper values.
                // Set the (i, j) in the original matrix into the (j, i).
                transposed.setCell(j, i, getCell(i, j));
            }
        }
        return transposed;
    }

    // ! Operator overloads

    // Operator overload for matrix addition.
    IntMatrix mtm::IntMatrix::operator+(const IntMatrix &matrix)
    {
        // Create a new matrix that's a copy of the current.
        IntMatrix result = *this;
        // Iterate through the matrices and start assigning the proper values.
        for (int i = 0; i < height(); i++)
        {
            for (int j = 0; j < width(); j++)
            {
                // Set the current cell into the result of original(i,j) + matrix(i,j).
                result.setCell(i, j, getCell(i, j) + matrix.getCell(i, j));
            }
        }
        // Return the result.
        return result;
    }

    // Operator overload for matrix and scalar addition (matrix+scalar)
    IntMatrix mtm::IntMatrix::operator+(const int &number)
    {
        // Create a new matrix that's a copy of the current.
        IntMatrix result = *this;
        // Iterate through the current matrix.
        for (int i = 0; i < height(); i++)
        {
            for (int j = 0; j < width(); j++)
            {
                // Add the scalar to the current cell (i,j)
                result.setCell(i, j, getCell(i, j) + number);
            }
        }
        // Return the result.
        return result;
    }

    // Operator overload for matrix and scalar addition (scalar+matrix)
    IntMatrix operator+(int number, const IntMatrix &matrix)
    {
        // Create a new matrix that's a copy of the current matrix.
        IntMatrix result = matrix;
        // Go through the current matrix.
        for (int i = 0; i < matrix.height(); i++)
        {
            for (int j = 0; j < matrix.width(); j++)
            {
                // Set the current cell (i,j) to matrix(i,j) + scalar
                result.setCell(i, j, result.getCell(i, j) + number);
            }
        }
        // Return the result matrix.
        return result;
    }

    // Operator overload for matrix and scalar addition (matrix+=scalar)
    IntMatrix mtm::IntMatrix::operator+=(const int &number)
    {
        // Modify the current matrix instead of a new one.
        // Go through the matrix itself.
        for (int i = 0; i < height(); i++)
        {
            for (int j = 0; j < width(); j++)
            {
                // Set the current cell (i,j) to current(i,j) + scalar
                setCell(i, j, getCell(i, j) + number);
            }
        }
        // Return the current matrix.
        return *this;
    }

    // Operator overload for matrix subtraction
    IntMatrix mtm::IntMatrix::operator-(const IntMatrix &matrix)
    {
        // Create a new matrix that's a copy of the current.
        IntMatrix result = *this;
        // Iterate through the matrices.
        for (int i = 0; i < height(); i++)
        {
            for (int j = 0; j < width(); j++)
            {
                // Change the current cell (i,j) into original(i,j)-matrix(i,j)
                result.setCell(i, j, getCell(i, j) - matrix.getCell(i, j));
            }
        }
        // Return the result matrix.
        return result;
    }

    // * Getters
    int mtm::IntMatrix::height() const
    {
        return rows;
    }

    int mtm::IntMatrix::width() const
    {
        return cols;
    }

    int mtm::IntMatrix::size() const
    {
        return width() * height();
    }

    int mtm::IntMatrix::getCell(int row, int col) const
    {
        return matrix[row][col];
    }

    Dimensions mtm::IntMatrix::getDimensions() const
    {
        Dimensions dims(height(), width());
        return dims;
    }

    // ! Setters
    void mtm::IntMatrix::setCell(int row, int col, int val)
    {
        matrix[row][col] = val;
    }

} // namespace mtm
