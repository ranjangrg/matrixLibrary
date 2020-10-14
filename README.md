# matrixLibrary
Simple C++ matrix library with a matrix struct and methods for matrix operations.

## Enable library
For each datatype, enable the following:
```c++
#define USE_S_INT_MATRIX	// for signed int 
#define USE_U_INT_MATRIX
#define USE_U_CHAR_MATRIX
```
Example, for a Matrix holding `unsigned char` type data, enable `#define USE_U_CHAR_MATRIX`.

Use namespace `Matrix::` to access all the methods and struct.
Make sure `matrix.cpp` has access to `matrix.hpp` via `include` path within `matrix.cpp`.
And also, compile `matrix.cpp` while compiling your project. Example:
```bash
g++ --std=c++14 matrix.cpp myfile.cpp -g -o exec;
```

## MatrixStruct
A typical MatrixStruct has following definition.
```c++
template <typename T>
struct MatrixStruct{
	std::size_t nRows, nCols;
	std::vector<T> elements;
	...
};
```

## Basic Matrix Constructor
```c++
// specify dimensions only
Matrix::MatrixStruct<T> matA = Matrix::createMatrix<T> matrix(numberOfRows, numberOfCols);
// specify dimensions and provide values as initializer_list
Matrix::MatrixStruct<T> matB = Matrix::createMatrix<T> matrix(2, 3, { 1,2,3,4,5,6});
// specify dimensions and provide values as vector
Matrix::MatrixStruct<T> matC = Matrix::createMatrix<T> matrix(2, 3, vector<T>(10));
```
> `T` is the data type that of the values that the Matrix will hold.


## Supported Operator operations
Currently supports following operations (using operators)
1. Matrix Addition/Subtraction (+/-)
1. Scalar multiplication with Matrix (*)
1. Matrix multiplication with Matrix (*)
1. Matrix comparison (==)

## Supported Matrix methods
### Transpose matrix
```c++
Matrix::MatrixStruct<int> transposed = Matrix::transposeMatrix(mainMatrix);
```
Returns the transposed matrix.
### Convolute matrix using a kernel matrix
```c++
Matrix::MatrixStruct<signed int> convolutedMatrix = Matrix::convoluteMatrixUsingKernel(mainMatrix, kernelMatrix);
```
Returns the convoluted matrix.
> note: out of range values are ignored during convolution 

## Useful methods
### dumpMatrixInfo(matrix)
Pretty prints all the matrix values into respective rows and columns.
### getRow(matrix, rowIndex)
Returns specified row from the given matrix as a vector.
### getCol(matrix, columnIndex)
Returns specified column from the given matrix as a vector.

## Overflow detection
The library supports mainly two overflow detection:
### Addition:
checkAdditionOverflow(num1, num2)
### Multiplication:
checkMultiplicationOverflow(num1, num2)
> Better to have the first number (argument) as the bigger data-type. That is, (long int, int) is better than (int, long int). Overflow detection is based upon the min and max value of the first argument data-type.

## Exceptions
### dimensionAndElementsMismatchException
Condition: number of rows * number of columns != total number of elements.
### dimensionMismatchException
Condition: Dimensions do not match among the matrices.
### dataOverflowDuringAdditionException
Condition: Data value overflow/underflow detected during addition.
### dataOverflowDuringMultiplicationException
Condition: Data value overflow/underflow detected during multiplication.
### dimensionMismatchForMultiplicationException
Condition: Matrix dimensions not suitable for multiplication.
