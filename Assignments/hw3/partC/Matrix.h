#ifndef MATRIX_H
#define MATRIX_H

#include "Auxiliaries.h"
#include "Exceptions.h"
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
                throw IllegalArgument();
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
        Matrix<T> &operator=(const Matrix &copy)
        {
            // Delete the current matrix
            for (int i = 0; i < rows; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
            rows = copy.rows;
            cols = copy.cols;
            // Create a new matrix according to the new dimensions
            matrix = new T *[rows];
            if (matrix == NULL)
            {
                throw std::bad_alloc();
            }
            // Iterate through the actual matrix and assign values.
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new T[cols];
                if (matrix[i] == NULL)
                {
                    throw std::bad_alloc();
                }
                for (int j = 0; j < cols; j++)
                {
                    // Assign the values into result(i,j) according to copy(i,j)
                    (*this)(i, j) = copy(i, j);
                }
            }
            // Return the result.
            return *this;
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
    };
} // namespace mtm
#endif