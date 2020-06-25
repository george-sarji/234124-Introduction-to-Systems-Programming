#ifndef INT_MATRIX_H
#define INT_MATIX_H

#include "Auxiliaries.h"

namespace mtm
{
    class IntMatrix
    {
        int rows;
        int cols;
        int **matrix;

    public:
        // ! Constructors

        // Constructor, defaults values to 0
        IntMatrix(Dimensions dims, int value = 0);
        // Copy constructor
        IntMatrix(const IntMatrix&);

        // ! Functions
        // Function to create identity matrices.
        static IntMatrix Identity(int dim);
        // Function to perform transpose on matrices.
        IntMatrix transpose();

        // ! Operator overloads
        // Operator + overload for matrix addition
        IntMatrix operator+(const IntMatrix& matrix);
        // Operator - overload for matrix subtraction
        IntMatrix operator-(const IntMatrix& matrix);
        // operator + overload for scalar addition
        IntMatrix operator+(const int& number);

        // ! Getters
        // Getter to get the cell at (row, col)
        int getCell(int row, int col) const;
        // Getter to get the row numbers (height)
        int height() const;
        // Getter to get the col numbers (width)
        int width() const;
        // Getter to get the number of cells in the matrix
        int size() const;
        // Getter to get the dimensions object according to rows and cols.
        Dimensions getDimensions() const;

        // Setters
        int setRows();
        int setCols();
        void setCell(int row, int col, int val);
    };
} // namespace mtm
#endif