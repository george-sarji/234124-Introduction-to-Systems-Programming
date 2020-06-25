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
    IntMatrix mtm::IntMatrix::operator+(const IntMatrix &matrix)
    {
        // Get the matrices dimensions. (We assume they're the same dimensions)
        Dimensions dims = getDimensions();
        // Create a new matrix according to the given dimensions.
        IntMatrix result(dims);
        // Iterate through the matrices and start assigning the proper values.
        for (int i = 0; i < dims.getRow(); i++)
        {
            for (int j = 0; j < dims.getCol(); j++)
            {
                // Set the current cell into the result of original(i,j) + matrix(i,j).
                result.setCell(i, j, getCell(i, j) + matrix.getCell(i, j));
            }
        }
        // Return the result.
        return result;
    }

    IntMatrix mtm::IntMatrix::operator-(const IntMatrix &matrix)
    {
        // Get the dimensions of the matrices. (Assume same dimensions)
        Dimensions dims = getDimensions();
        // Create the result matrix.
        IntMatrix result(dims);
        // Iterate through the matrices.
        for (int i = 0; i < dims.getRow(); i++)
        {
            for (int j = 0; j < dims.getCol(); j++)
            {
                // Change the current cell (i,j) into original(i,j)-matrix(i,j)
                result.setCell(i, j, getCell(i, j) - matrix.getCell(i, j));
            }
        }
        // Return the result matrix.
        return result;
    }

    IntMatrix mtm::IntMatrix::operator+(const int &number)
    {
        // Get the dimensions of our current matrix.
        Dimensions dims = getDimensions();
        // Create the result matrix.
        IntMatrix result(dims);
        // Iterate through the current matrix.
        for (int i = 0; i < dims.getRow(); i++)
        {
            for (int j = 0; j < dims.getCol(); j++)
            {
                // Add the scalar to the current cell (i,j)
                result.setCell(i, j, getCell(i, j) + number);
            }
        }
        // Return the result.
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
