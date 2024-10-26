// NaiveMatrices.h
#ifndef NAIVEMATRICES_H
#define NAIVEMATRICES_H

#include <stdbool.h>

/*
 * Struct:  Matrix 
 * --------------------
 * Defines a matrix by its dimensions and data
 * All of the elements in the matrices in my implementation are doubles
 *
 *  rows (int): number of rows
 * 
 *  cols (int): number of columns
 *
 *  data (double): pointer to the first element of the matrix.
 *               the data is flattened from a 2D array
 */

typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;

// Function declarations
bool checkDimensions(const Matrix *matrix_a, const Matrix *matrix_b);
bool isSquare(const Matrix *mat);
double norm(const Matrix *vector);
bool sumMatrices(const Matrix *matrix_a, const Matrix *matrix_b, bool subtraction, Matrix *result);
void printMatrix(const Matrix *matrix);
bool scalarMultiply(Matrix *matrix, double scalar);
bool transposeMatrix(const Matrix *matrix, Matrix *result);
bool multiplyMatrices(const Matrix *matrix_a, const Matrix *matrix_b, Matrix *result);
double boxMullerDraw();
Matrix initMatrixZeros(int rows, int cols);
Matrix initMatrixRandomNorm(int rows, int cols);
double oneIterGradientDescent(const Matrix *X, Matrix *Theta,const Matrix *Y,double lr);
double linearRegression(const Matrix *X, Matrix *Theta,const Matrix *Y,double lr,int epochs, double loss_tolerance, bool verbose);
#endif
