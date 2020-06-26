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
        // Destructor
        ~IntMatrix();

        // ! Functions
        // Function to create identity matrices.
        static IntMatrix Identity(int dim);
        // Function to perform transpose on matrices.
        IntMatrix transpose() const;

        // ! Operator overloads
        // Operator + overload for matrices addition
        IntMatrix operator+(const IntMatrix&);
        // operator + overload for scalar addition (matrix+scalar)
        IntMatrix operator+(const int&);
        // Operator + overload for scalar addition (scalar + matrix)
        friend IntMatrix operator+(int number, const IntMatrix&);
        // operator += overload for scalar addition (matrix+=scalar)
        IntMatrix operator+=(const int&);

        // Operator - overload for matrices subtraction
        IntMatrix operator-(const IntMatrix&);
        // Operator - overload for matrix value inversion (-matrix)
        IntMatrix operator-() const;

        // Operator << overload for output
        friend std::ostream& operator<<(std::ostream&, const IntMatrix&);

        // Operator () overload for cell usage
        int& operator()(int row, int col) const;

        // Assignment operator overload
        IntMatrix& operator=(const IntMatrix&);



        
        // ! Getters
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