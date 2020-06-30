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

        /***********************************************
         * Initializes the IntMatrix with a default value of 0
         * 
         * @param dims (Dimensions) Dimensions of the required matrix
         * @param value (int) Required default value for the matrix
        ***********************************************/
        IntMatrix(Dimensions dims, int value = 0);

        /***********************************************
         * Initializes the IntMatrix according to another matrix (copy constructor)
         * 
         * @param IntMatrix Reference of the matrix to copy values from
         * @return IntMatrix copy
        ***********************************************/
        IntMatrix(const IntMatrix &);

        //  Deconstructs the given IntMatrix and frees the data.
        ~IntMatrix();

        // ! Functions


        /***********************************************
         * Creates an identity matrix according to the given dimensions
         * 
         * @param dims Required dimensions for the identity matrix
         * @return Identity matrix of size (dims * dims)
        ***********************************************/
        static IntMatrix Identity(int dim);
        // Function to perform transpose on matrices.

        /***********************************************
         * Performs transposing of the given matrix.
         * 
         * @param this Implicit IntMatrix from the call.
         * @return Transposed matrix copy
        ***********************************************/
        IntMatrix transpose() const;

        // ! Operator overloads
        // Operator + overload for matrices addition
        IntMatrix operator+(const IntMatrix &);
        // operator + overload for scalar addition (matrix+scalar)
        IntMatrix operator+(const int &);
        // Operator + overload for scalar addition (scalar + matrix)
        friend IntMatrix operator+(int, const IntMatrix &);
        // operator += overload for scalar addition (matrix+=scalar)
        IntMatrix operator+=(const int &);

        // Operator - overload for matrices subtraction
        IntMatrix operator-(const IntMatrix &);
        // Operator - overload for matrix value inversion (-matrix)
        IntMatrix operator-() const;

        // Operator << overload for output
        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);

        // Operator () overload for cell usage
        int &operator()(int, int) const;

        // Assignment operator overload
        IntMatrix &operator=(const IntMatrix &);

        // Logical operators overload
        // <
        IntMatrix operator<(const int);
        // <=
        IntMatrix operator<=(const int);
        // >
        IntMatrix operator>(const int);
        // >=
        IntMatrix operator>=(const int);
        // ==
        IntMatrix operator==(const int);
        // !=
        IntMatrix operator!=(const int);

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
        int setCols();
        void setCell(int row, int col, int val);

        // ! Iterator
        class Iterator;
        Iterator begin() const;
        Iterator end() const;
    };
    bool all(const IntMatrix);
    bool any(const IntMatrix);

    class IntMatrix::Iterator
    {
        int row, col;
        IntMatrix *matrix;
        friend class IntMatrix;
        Iterator(const IntMatrix *matrix, int row, int col);

    public:
        // Operator overload for value retrieval
        const int &operator*() const;
        // Operator overload for advancing the iterator
        Iterator &operator++();
        // Operator overload for assignment
        Iterator &operator=(const Iterator &);
        // Operator overload for going backwards in the iterator
        Iterator &operator--();
    };
} // namespace mtm
#endif