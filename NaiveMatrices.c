#include <stdio.h>
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

typedef struct{
    int rows;
    int cols;
    double *data;
} Matrix;

/*
 * Function:  (bool) checkDimensions
 * --------------------
 * Verifies that two matrices have the same dimensions
 * This is crucial when doing certain operations such as sums
 *
 *  *matrix_a (pointer): a pointer to a matrix struct
 * 
 *  *matrix_b (pointer): a pointer to a matrix struct
 */

bool checkDimensions(const Matrix *matrix_a, const Matrix *matrix_b) {
    return (matrix_a->rows == matrix_b->rows && matrix_a->cols == matrix_b->cols);
}

/*
 * Function:  (bool) isSquare
 * --------------------
 * Verifies that a matrix is square
 * This is crucial when doing certain operations such as inversions
 *
 *  *mat (pointer): a pointer to a matrix struct
*/
bool isSquare(const Matrix *mat){
    return (mat->rows == mat->cols);
}

/*
 * Function:  (void) multiplyScalar
 * --------------------
 * Multiplies a matrix by a scalar
 *
 *  *mat (pointer): a pointer to a matrix struct
 *  scalar (double): a scalar value
*/
void multiplyScalar(const Matrix *matrix, double scalar){
    int i;
    for(i = 0; i < matrix->rows + matrix->cols; i++){
        *(matrix->data + i) *= scalar;
    }
}

/*
 * Function: (bool) sumMatrices
 * --------------------
 * Sums two matrices and returns whether the sum was successful
 * Fails if both matrices have different dimensions
 * Can handle subtraction as well and it operates as matrix_a - matrix_b
 *
 *  matrix_a (pointer): a pointer to the first matrix struct that you want to sum
 *  matrix_b (pointer): a pointer to the second matrix struct that you want to sum
 *  subtraction (bool): a boolean that indicates whether it is a subtraction instead
 * *result_matrix (pointer): a pointer to the result (a Matrix struct)
*/

bool sumMatrices(const Matrix *matrix_a, const Matrix *matrix_b, bool subtraction, Matrix *result){
    /* Check same dimensions*/
    if(!checkDimensions(matrix_a,matrix_b)){
        printf("Mismatch in the dimensions when summing");
        return false;
    }
    /* Enforce dimensions for result matrix */
    result->rows = matrix_a->rows;
    result->cols = matrix_a->cols;
    /* If it is a subtraction then change every element in matrix_b to its negative */
    if(subtraction){
        multiplyScalar(matrix_b, -1.0);
    }
    /*If it works, then sum the matrices in a flattened fashion*/
    int i;
    for(i = 0;i < matrix_a->rows*matrix_a->cols;i++){
        *(result->data+i) = *(matrix_a->data + i) + *(matrix_b->data + i);
    }
    /*After the routine is over, return success*/
    return true;
}

/*
 * Function: (void) printMatrix
 * --------------------
 *  Prints a matrix in a 2D fashion
 *  Useful for debugging
 *
 *  matrix (pointer): a pointer to a Matrix struct
*/
void printMatrix(const Matrix *matrix){
    int r;
    int c;
    for(r = 0; r < matrix->rows;r++){
        for(c=0;c < matrix->cols;c++){
            /*Print corresponding element*/
            printf("%f ", *(matrix->data + r * matrix->cols + c));
        }
        /*Skip a line*/
        printf("\n");
    }
}

/*
 * Function: (int) main
 * --------------------
 *  Executes the routine of summing two matrices
 *  Placeholder values for now
 *
 *  No arguments
*/
int main(){
    /* Define data for example */
    double matrixAData[2][3] = {{1.1,2.2,3.3},{4.3,5.2,6.1}};
    double matrixBData[2][3] = {{0.4,3.7,8.9},{4.5,2.7,6.9}};
    /* Initialize result matrix */
    double resultData[2][3];
    /* Generate matrix structs */
    Matrix matrixA = {2,3, (double *)matrixAData};
    Matrix matrixB = {2,3, (double *)matrixBData};
    Matrix resultSum = {2,3, (double *)resultData};
    Matrix resultMinus = {2,3, (double *)resultData};
    /* Perform sum */
    if (sumMatrices(&matrixA, &matrixB, false, &resultSum)) {
        printf("Sum of matrices:\n");
        printMatrix(&resultSum);
    }
    if (sumMatrices(&matrixA, &matrixB, true, &resultMinus)) {
        printf("Subtraction of matrices:\n");
        printMatrix(&resultMinus);
    }
    return 0;
}



