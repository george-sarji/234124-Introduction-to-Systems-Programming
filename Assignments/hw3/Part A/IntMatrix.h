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
        class iterator;
        iterator begin();
        iterator end();

        // ! const_iterator
        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;
    };
    bool all(const IntMatrix);
    bool any(const IntMatrix);

    class IntMatrix::iterator
    {
        int row, col;
        const IntMatrix *matrix;
        iterator(const IntMatrix *matrix) : row(0), col(0), matrix(matrix) {}
        friend class IntMatrix;

    public:
        ~iterator() = default;
        // Operator overload for value retrieval
        int &operator*() const;
        // Operator overload for advancing the iterator
        iterator &operator++();
        // Postfix iterator advancement operator
        iterator operator++(int);
        // Operator overload for assignment
        iterator &operator=(const iterator &);
        // Operator overload for comparison (!=)
        bool operator!=(const iterator &);
        // Operator overload for comparison (==)
        bool operator==(const iterator &);
    };

    class IntMatrix::const_iterator
    {
        int row, col;
        const IntMatrix *matrix;
        const_iterator(const IntMatrix *matrix) : row(0), col(0), matrix(matrix) {}
        friend class IntMatrix;

    public:
        ~const_iterator() = default;
        // Operator overload for value retrieval (returns const)
        const int &operator*() const;
        // Operator overload for advancing the iterator
        const_iterator &operator++();
        // Postfix operator overload for advancing the iterator
        const_iterator operator++(int);
        // Operator overload for assignment
        const_iterator &operator=(const const_iterator &);
        // Operator overload for comparison
        bool operator!=(const const_iterator &);
        // Operator overload for comparison
        bool operator==(const const_iterator &);
    };
} // namespace mtm
#endif