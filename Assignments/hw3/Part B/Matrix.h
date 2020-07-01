#ifndef MATRIX_H
#define MATRIX_H

#include "Auxiliaries.h"
namespace mtm
{
    template <class T>
    class Matrix
    {
    private:
        T **matrix;
        int cols, rows;

    public:
        // ! Constructors

        /***********************************************
         * Constructors the matrix according to the given dimensions
         * @param dims Dimensions of the matrix to be built
         * @param value Default values to add, defaults to the type's default
        ***********************************************/
        Matrix<T>(Dimensions dims, T value = T())
        {
            // Get the dimensions of the matrix
            if (dims.getRow() <= 0 || dims.getCol() <= 0)
            {
                throw IllegalInitialization();
            }
            rows = dims.getRow();
            cols = dims.getCol();
            // Construct the rows array
            matrix = new T *[rows];
            // Check if the allocation is not successful
            if (matrix == NULL)
            {
                throw std::bad_alloc();
            }
            // Iterate through and start the columns.
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new T[cols];
                if (matrix[i] == NULL)
                {
                    throw std::bad_alloc();
                }
                // Iterate through and assign the default values
                for (int j = 0; j < cols; j++)
                {
                    matrix[i][j] = value;
                }
            }
        }

        /***********************************************
         * Constructors a copy of the given matrix
         * @param matrix Matrix to be copied
         * @return Copy of the given matrix
        ***********************************************/
        Matrix<T>(const Matrix<T> &copy_matrix)
        {
            // Copy the dimensions from the matrix to copy to the current matrix
            rows = copy_matrix.height();
            cols = copy_matrix.width();
            // Construct a new matrix according to the current matrix's dimensions
            matrix = new T *[rows];
            if (matrix == NULL)
            {
                throw std::bad_alloc();
            }
            // Iterate and create the column arrays
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new T[cols];
                if (matrix[i] == NULL)
                {
                    // Throw bad allocation
                    throw std::bad_alloc();
                }
                for (int j = 0; j < cols; j++)
                {
                    // Set the contents of the cell according to the copy_matrix
                    matrix[i][j] = copy_matrix(i, j);
                }
            }
        }

        // Deconstructor for the matrix
        ~Matrix<T>()
        {
            // Iterate through the matrix and delete the inner arrays
            for (int i = 0; i < rows; i++)
            {
                delete[] matrix[i];
            }
            // Delete parent array.
            delete[] matrix;
        }

        /***********************************************        
        ***********************************************/

        // ! Functions

        /***********************************************
         * Constructs a diagonal matrix with the given value
         * @param dim Dimension of the new diagonal matrix
         * @param value Values of the diagonal in the new matrix
         * @return Diagonal matrix with the value in the primary diagonal
        ***********************************************/
        static Matrix<T> Diagonal(int dim, T value)
        {
            // Create a new matrix according to the given dimensions.
            Matrix<T> matrix(Dimensions(dim, dim));
            // Iterate through the matrix and assign the value into the main diagonal
            for (int i = 0; i < dim; i++)
            {
                // Assign the value into matrix(i,i)
                matrix(i, i) = value;
            }
            // Return the diagonal matrix
            return matrix;
        }

        /***********************************************
         * Creates a transposed matrix of the current matrix
         * @return Transposed version of the current matrix    
        ***********************************************/
        Matrix<T> transpose() const
        {
            // Allocate a new matrix with the required dimensions
            Matrix<T> transposed(Dimensions(cols, rows));
            // Iterate through the current matrix and assign values into the transposed matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Assign the data in current cell (i,j) into transposed cell (j,i)
                    transposed(j, i) = (*this)(i, j);
                }
            }
            // Return the transposed array.
            return transposed;
        }

        // ! Getters
        /***********************************************
         * Gives the number of rows
         * @return Number of rows in the matrix
        ***********************************************/
        int height() const
        {
            return rows;
        }

        /***********************************************
         * Gives the number of columns
         * @return Number of columns in the matrix
        ***********************************************/
        int width() const
        {
            return cols;
        }

        /***********************************************
         * Gives the number of cells in the matrix
         * @return Number of cells in the matrix
        ***********************************************/
        int size() const
        {
            return cols * rows;
        }
        // ! Operator overloads
        /***********************************************
         * Provides a reference to the object in the cell (row, col)
         * @param row Row of cell to look for
         * @param col Column of cell to look for
         * @return Reference to object in cell (row, col)
        ***********************************************/
        T &operator()(int row, int col) const
        {
            if (row >= height() || row < 0 || col >= width() || col < 0)
            {
                throw AccessIllegalElement();
            }
            return matrix[row][col];
        }

        /***********************************************
         * Operator overload for assignment between matrices
         * @param copy Matrix to be copied into the current matrix
         * @return Resultant matrix
        ***********************************************/
        const Matrix<T> &operator=(const Matrix &copy)
        {
            // Check if the dimensions match.
            if (copy.rows != rows || copy.cols != cols)
            {
                // Throw a dimension mismatch.
                throw DimensionMismatch(*this, copy);
            }
            // Create a result matrix according to the current matrix.
            Matrix<T> result(*this);
            // Iterate through the actual matrix and assign values.
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Assign the values into result(i,j) according to copy(i,j)
                    result(i, j) = copy(i, j);
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************    
         * Operator overload for addition between two matrices
         * @param matrix Matrix to be added into the current matrix
         * @return Resultant matrix of the addition    
        ***********************************************/
        Matrix<T> operator+(const Matrix &mat) const
        {
            const Matrix<T> result(*this);
            // Check if the dimensions match for the addition
            if (rows != mat.rows || cols != mat.cols)
            {
                throw DimensionMismatch(*this, mat);
            }
            // Create a result matrix as a copy of the current matrix
            // Iterate through the result matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Add the value of matrix at cell (i,j) into result at cell (i,j)
                    result(i, j) += mat(i, j);
                }
            }
            // Return the result matrix
            return result;
        }

        /***********************************************     
         * Operator overload for object type additions into the matrix (matrix+object)
         * 
         * @param object Object to be added into the matrix cells
         * @return Result matrix of the addition
        ***********************************************/
        const Matrix<T> operator+(const T &object) const
        {
            // Create a result matrix according to the current matrix
            const Matrix<T> result(*this);
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Add the given object to the cell at (i,j)
                    result(i, j) += object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************     
         * Operator overload for object type additions into the matrix (object+matrix)
         * 
         * @param object Object to be added into the matrix
         * @param matrix Matrix to add the objects to
         * @return Result matrix of the addition
        ***********************************************/
        friend Matrix<T> operator+(T object, const Matrix<T> &matrix) const
        {
            // Create a result matrix according to the given matrix.
            Matrix<T> result(matrix);
            // Iterate through the matrix
            for (int i = 0; i < matrix.rows; i++)
            {
                for (int j = 0; j < matrix.cols; j++)
                {
                    // Add the object to cell (i,j)
                    result(i, j) += object;
                }
            }
            // Return the result matrix.
            return result;
        }

        /***********************************************     
         * Operator overload for object type additions into the matrix (matrix+=object)
         * 
         * @param object Object to be added into the matrix
         * @return Result matrix of the addition
        ***********************************************/
        Matrix<T> operator+=(const T &object)
        {
            // Go through the matrix.
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Add the object to the current cell.
                    (*this)(i, j) += object;
                }
            }
            // Return the current matrix.
            return *this;
        }

        /***********************************************      
         * Operator overload for matrices subtraction
         * 
         * @param matrix Matrix to be deducted from current matrix
         * @return Result matrix of the subtraction  
        ***********************************************/
        Matrix<T> operator-(const Matrix<T> &matrix) const
        {
            // Check if the dimensions match.
            if (rows != matrix.rows || cols != matrix.cols)
            {
                throw DimensionMismatch(*this, matrix);
            }
            Matrix<T> result(*this);
            // The dimensions match. Iterate through the matrix.
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Subtract the matrix's value from the current cell.
                    result(i, j) -= matrix(i, j);
                }
            }
            return result;
        }

        /***********************************************      
         * Operator overloading to inverse the sign of the matrix (unary -)
         * 
         * @return Result matrix of sign invertence of the original matrix  
        ***********************************************/
        Matrix<T> operator-() const
        {
            // Create a result matrix according to the current matrix.
            Matrix<T> result(*this);
            // Iterate through the matrix.
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Inverse the sign of the current cell
                    result(i, j) = -result(i, j);
                }
            }
            // Return the result
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (<)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is smaller than object, false otherwise   
        ***********************************************/
        Matrix<bool> operator<(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) < object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (<=)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is smaller or equals to object, false otherwise   
        ***********************************************/
        Matrix<bool> operator<=(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) <= object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (>)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is bigger than object, false otherwise   
        ***********************************************/
        Matrix<bool> operator>(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) > object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (>=)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is bigger or equal to object, false otherwise   
        ***********************************************/
        Matrix<bool> operator>=(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) >= object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (==)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is equal to object, false otherwise   
        ***********************************************/
        Matrix<bool> operator==(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) == object;
                }
            }
            // Return the result.
            return result;
        }

        /***********************************************  
         * Operator overload for comparison between matrix and object (!=)
         * 
         * @param object Object to compare with matrix
         * @return Matrix with cells set to true if cell is not equal to object, false otherwise   
        ***********************************************/
        Matrix<bool> operator!=(const T object) const
        {
            // Create a matrix with the current dimensions
            Matrix<bool> result(Dimensions(rows, cols));
            // Iterate through the matrix
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    // Set the value of the comparison between the current cell (i,j) and the object
                    result(i, j) = (*this)(i, j) != object;
                }
            }
            // Return the result.
            return result;
        }

        // ! Exception classes
        class AccessIllegalElement : public std::exception
        {
        private:
            std::string error;

        public:
            AccessIllegalElement() : error("Mtm matrix error: An attempt to access an illegal element") {}
            ~AccessIllegalElement() = default;
            const char *what() const noexcept
            {
                return error.c_str();
            }
        };

        class IllegalInitialization : public std::exception
        {
        private:
            std::string error;

        public:
            IllegalInitialization() : error("Mtm matrix error: Illegal initialization values") {}
            ~IllegalInitialization() = default;
            const char *what() const noexcept
            {
                return error.c_str();
            }
        };

        class DimensionMismatch : public std::exception
        {
        private:
            std::string error;

        public:
            DimensionMismatch(const Matrix mat_1, const Matrix mat_2)
            {
                error = "Mtm matrix error: Dimension mismatch: (" + std::to_string(mat_1.height()) +
                        "," + std::to_string(mat_1.width()) + ") (" + std::to_string(mat_2.height()) + "," + std::to_string(mat_2.width()) + ")";
            }
            const char *what() const noexcept
            {
                return error.c_str();
            }
        };

        // ! Iterator
        class iterator;
        iterator begin() const
        {
            return iterator(this);
        }
        iterator end() const
        {
            iterator it(this);
            it.row = height();
            return it;
        }
    };

    /***********************************************       
     * Checks if all the cells in the matrix are not equal to 0
     * @param matrix Matrix to be checked
     * @return True if no zeros in matrix, false otherwise 
    ***********************************************/
    template <class T>
    bool all(const Matrix<T> &matrix)
    {
        // Iterate through the matrix.
        for (int i = 0; i < matrix.height(); i++)
        {
            for (int j = 0; j < matrix.width(); j++)
            {
                // Check if the current cell is equals to zero
                if (matrix(i, j) == 0)
                {
                    // Return false.
                    return false;
                }
            }
        }
        // We did not encounter any zeros. We can return true.
        return true;
    }

    /***********************************************       
     * Checks if any of the cells in the matrix are not equal to 0
     * @param matrix Matrix to be checked
     * @return True if at least one non-zero in matrix, false otherwise 
    ***********************************************/
    template <class T>
    bool any(const Matrix<T> &matrix)
    {
        // Iterate through the matrix
        for (int i = 0; i < matrix.height(); i++)
        {
            for (int j = 0; j < matrix.width(); j++)
            {
                // Check if the current cell is not equals to zero
                if (matrix(i, j) != 0)
                {
                    // Not equals to zero. We found our perfect match.
                    return true;
                }
            }
        }
        // We encountered all zeros. Return false.
        return false;
    }

    /***********************************************        
        ***********************************************/
    template <class T>
    std::ostream &operator<<(std::ostream &stream, const Matrix<T> &matrix)
    {
        return mtm::printMatrix(stream, matrix.begin(), matrix.end(), matrix.width());
    }

    /***********************************************        
        ***********************************************/

    template <class T>
    class Matrix<T>::iterator
    {
        int row, col;
        const Matrix<T> *matrix;
        friend class Matrix<T>;

    public:
        /***********************************************  
         * Constructs the iterator for the given matrix
         * Iterator starts at 0,0
         * 
         * @param matrix Matrix that the iterator works on      
        ***********************************************/
        explicit iterator(const Matrix<T> *matrix) : row(0), col(0), matrix(matrix) {}
        ~iterator() = default;

        /***********************************************
         * Operator overload to advance the iterator by one
         * @return Reference to the iterator after it was advanced
        ***********************************************/
        iterator &operator++()
        {
            if (col == (*matrix).width() - 1)
            {
                col = 0;
                row++;
            }
            else
            {
                col++;
            }
            return *this;
        }

        /***********************************************
         * Postfix operator overload to advance the iterator
         * @return Reference to the iterator before it was advanced
        ***********************************************/
        iterator operator++(int num)
        {
            iterator iterator = *this;
            ++*this;
            return iterator;
        }

        /***********************************************
         * Operator overload to assign new values into the iterator
         * @param iterator Iterator to copy the values of into the current iterator
         * @return Reference to the iterator after it was changed
        ***********************************************/
        iterator &operator=(const iterator &iterator)
        {
            // Use the current row and col.
            row = iterator.row;
            col = iterator.col;
            // Change the matrix pointer.
            matrix = iterator.matrix;
            return *this;
        }

        /***********************************************
         * Operator overload to check if the current iterator is not equal to the given iterator
         * @param iterator Iterator to compare with the current iterator
         * @return True if iterators are not equal (not same matrix, row or col), otherwise false
        ***********************************************/
        bool operator!=(const iterator &iterator)
        {
            // Return the opposite of the == operator
            return !((*this) == iterator);
        }

        /***********************************************
         * Operator overload to check if the current iterator is equal to the given iterator
         * 
         * @param iterator Iterator to compare with the current iterator
         * @return True if iterators are equal (same matrix, row and col), otherwise false
        ***********************************************/
        bool operator==(const iterator &iterator)
        {
            // Compare current row, col and matrix
            return row == iterator.row && col == iterator.col && matrix == iterator.matrix;
        }

        /***********************************************
         * Operator overload to retrieve the value that the iterator points to
         * @return Reference to the value that the iterator points to
        ***********************************************/
        T &operator*() const
        {
            if (row >= (*matrix).height() || col >= (*matrix).height())
            {
                throw AccessIllegalElement();
            }
            T &element = (*matrix)(row, col);
            return element;
        }
    };
} // namespace mtm
#endif