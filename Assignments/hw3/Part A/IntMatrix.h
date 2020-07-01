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

        /***********************************************
         * Performs transposing of the given matrix.
         * 
         * @param this Implicit IntMatrix from the call.
         * @return Transposed matrix copy
        ***********************************************/
        IntMatrix transpose() const;

        // ! Operator overloads
        /***********************************************
         * Operator overload for matrices addition
         * 
         * @param matrix Matrix to add to the current matrix
         * @return Result of the addition of matrices
        ***********************************************/
        IntMatrix operator+(const IntMatrix &);

        /***********************************************
         * Operator overload for matrix and scalar addition (matrix+scalar)
         * 
         * @param num Number to add into matrix
         * @return Result of the scalar addition into the matrix
        ***********************************************/
        IntMatrix operator+(const int &);

        /***********************************************
         * Operator overload for matrix and scalar addition (scalar+matrix)
         * @param matrix Matrix to add the scalar into
         * @return Result matrix of the scalar and matrix addition
        ***********************************************/
        friend IntMatrix operator+(int, const IntMatrix &);

        /***********************************************
         * Operator overload for scalar addition into matrix using +=
         * 
         * @param num Number to add into the matrix
         * @return Reference to the resultant matrix
        ***********************************************/
        IntMatrix &operator+=(const int &);

        /***********************************************
         * Operator overload for matrix substraction
         * 
         * @param matrix Matrix to subtract from the current matrix
         * @return Result of the matrices subtraction
        ***********************************************/
        IntMatrix operator-(const IntMatrix &);

        /***********************************************
         * Operator overload to inverse the sign of values inside the matrix
         * 
         * @return Matrix with the inversed sign of the current matrix
        ***********************************************/
        IntMatrix operator-() const;

        /***********************************************
         * Operator overload for printing out a matrix
         * 
         * @param stream Current string output stream to add the matrix print to
         * @param matrix Matrix to print
         * 
         * @return Reference to stream that's used for the output
        ***********************************************/
        friend std::ostream &operator<<(std::ostream &, const IntMatrix &);

        /***********************************************
         * Operator overload for retrieving the cell given
         * 
         * @param row Row of cell to retrieve
         * @param col Column of cell to retrieve
         * @return Reference to the number at cell (row, col) in the matrix
        ***********************************************/
        int &operator()(int, int) const;

        // Assignment operator overload
        /***********************************************
         * Assignment operator overload to change contents of an IntMatrix
         * 
         * @param matrix Matrix to assign into the current matrix
         * @return Reference to the current matrix after it was changed
        ***********************************************/
        IntMatrix &operator=(const IntMatrix &);

        // Logical operators overload

        /***********************************************
         * Operator overload to compare if cells within matrix are smaller than a number
         * 
         * @param num Number to compare with the matrix
         * @return Matrix of 0 and 1 denoting if the cell (i,j) is smaller than the given number
        ***********************************************/
        IntMatrix operator<(const int);

        /***********************************************
         * Operator overload to compare if cells within matrix are smaller or equal to given number
         * 
         * @param num Number to compare with the matrix
         * @return Matrix containing 0 and 1 denoting if cell (i,j) is smaller or equal to the given number
        ***********************************************/
        IntMatrix operator<=(const int);

        /***********************************************
         * Operator overload to compare if cells within matrix are bigger than a number
         * 
         * @param num Number to compare with the matrix
         * @return Matrix of 0 and 1 denoting if the cell (i,j) is bigger than the given number
        ***********************************************/
        IntMatrix operator>(const int);

        /***********************************************
         * Operator overload to compare if cells within matrix are bigger or equal to given number
         * 
         * @param num Number to compare with the matrix
         * @return Matrix containing 0 and 1 denoting if cell (i,j) is bigger or equal to the given number
        ***********************************************/
        IntMatrix operator>=(const int);

        /***********************************************
         * Operator overload to compare if cells within matrix are equal to given number
         * 
         * @param num Number to compare with matrix
         * @return Matrix containing 0 or 1 denoting if cell (i,j) is equal to the given number
        ***********************************************/
        IntMatrix operator==(const int);

        /***********************************************
         * Operator overload to compare if cells within matrix are not equal to given number
         * 
         * @param num Number to compare with matrix
         * @return Matrix containing 0 or 1 denoting if cell (i,j) is not equal to the given number
        ***********************************************/
        IntMatrix operator!=(const int);

        // ! Getters
        /***********************************************
         * Getter to retrieve the amount of rows in the matrix
         * @return Number of rows in the matrix
        ***********************************************/
        int height() const;

        /***********************************************
         * Getter to retrieve the amount of columns in the matrix
         * @return Number of columns in the matrix
        ***********************************************/
        int width() const;

        /***********************************************
         * Getter to retrieve the amount of cells in the matrix
         * @return Number of cells in the matrix
        ***********************************************/
        int size() const;

        /***********************************************
         * Getter to retrieve the dimensions of the matrix
         * @return Dimensions of the matrix
        ***********************************************/
        Dimensions getDimensions() const;

        // ! Iterator
        class iterator;
        /***********************************************
         * Retrieves an iterator denoting the beginning of the matrix
         * @return Iterator that points to the beginning of the matrix
        ***********************************************/
        iterator begin();

        /***********************************************
         * Retrieves a pointer denoting the end of the matrix
         * @return Iterator that points to the end of the matrix
        ***********************************************/
        iterator end();

        // ! const_iterator
        class const_iterator;

        /***********************************************
         * Retrieves an iterator denoting the beginning of a const matrix
         * @return Iterator that points to the beginning of a const matrix
        ***********************************************/
        const_iterator begin() const;

        /***********************************************
         * Retrieves a pointer denoting the end of a const matrix
         * @return Iterator that points to the end of a const matrix
        ***********************************************/
        const_iterator end() const;
    };

    /***********************************************
     * Checks if all cells in the given matrix are not equal to 0
     * @param matrix Matrix to check the cells of
     * @return True if all the cells in the matrix are not equal to zero, false otherwise
    ***********************************************/
    bool all(const IntMatrix);

    /***********************************************
     * Checks if at least one of the cells in the given matrix are not equal to 0
     * @param matrix Matrix to check the cells of
     * @return True if at least one of the cells in the matrix is not equal to 0, false otherwise
    ***********************************************/
    bool any(const IntMatrix);

    class IntMatrix::iterator
    {
        int row, col;
        const IntMatrix *matrix;
        friend class IntMatrix;

    public:
        /***********************************************
         * Constructors the iterator according to the given matrix
         * The iterator begins at 0,0 in the matrix.
         * @param matrix Pointer to the IntMatrix the constructor iterate on
        ***********************************************/
        explicit iterator(const IntMatrix *matrix) : row(0), col(0), matrix(matrix) {}

        ~iterator() = default;

        /***********************************************
         * Operator overload to retrieve the value that the iterator points to
         * @return Reference to the value that the iterator points to
        ***********************************************/
        int &operator*() const;

        /***********************************************
         * Operator overload to advance the iterator by one
         * @return Reference to the iterator after it was advanced
        ***********************************************/
        iterator &operator++();

        /***********************************************
         * Postfix operator overload to advance the iterator
         * @return Reference to the iterator before it was advanced
        ***********************************************/
        iterator operator++(int);

        /***********************************************
         * Operator overload to assign new values into the iterator
         * @param iterator Iterator to copy the values of into the current iterator
         * @return Reference to the iterator after it was changed
        ***********************************************/
        iterator &operator=(const iterator &);

        /***********************************************
         * Operator overload to check if the current iterator is not equal to the given iterator
         * @param iterator Iterator to compare with the current iterator
         * @return True if iterators are not equal (not same matrix, row or col), otherwise false
        ***********************************************/
        bool operator!=(const iterator &);

        /***********************************************
         * Operator overload to check if the current iterator is equal to the given iterator
         * 
         * @param iterator Iterator to compare with the current iterator
         * @return True if iterators are equal (same matrix, row and col), otherwise false
        ***********************************************/
        bool operator==(const iterator &);
    };

    class IntMatrix::const_iterator
    {
        int row, col;
        const IntMatrix *matrix;

        /***********************************************
         * Constructor for a const iterator that uses a const IntMatrix
         * The iterator begins at (0,0)
         * 
         * @param matrix Const IntMatrix that the iterator should work on
        ***********************************************/
        explicit const_iterator(const IntMatrix *matrix) : row(0), col(0), matrix(matrix) {}
        friend class IntMatrix;

    public:
        ~const_iterator() = default;

        /***********************************************
         * Operator overload to retrieve the value that the const iterator points to
         * @return Reference to the value that the const iterator points to
        ***********************************************/
        const int &operator*() const;

        /***********************************************
         * Operator overload to advance the const iterator by one
         * @return Reference to the const iterator after it was advanced
        ***********************************************/
        const_iterator &operator++();

        /***********************************************
         * Postfix operator overload to advance the const iterator
         * @return Reference to the const iterator before it was advanced
        ***********************************************/
        const_iterator operator++(int);

        /***********************************************
         * Operator overload to assign new values into the const iterator
         * @param iterator Iterator to copy the values of into the current iterator
         * @return Reference to the const iterator after it was changed
        ***********************************************/
        const_iterator &operator=(const const_iterator &);

        /***********************************************
         * Operator overload to check if the current const iterator is not equal to the given const iterator
         * @param iterator Const iterator to compare with the current const iterator
         * @return True if iterators are not equal (not same matrix, row or col), otherwise false
        ***********************************************/
        bool operator!=(const const_iterator &);

        /***********************************************
         * Operator overload to check if the current const iterator is equal to the given const iterator
         * 
         * @param iterator Const iterator to compare with the current const iterator
         * @return True if iterators are equal (same matrix, row and col), otherwise false
        ***********************************************/
        bool operator==(const const_iterator &);
    };
} // namespace mtm
#endif