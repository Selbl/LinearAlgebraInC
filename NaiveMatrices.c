#include <stdio.h>
#include <stdlib.h>
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
 * Function: (bool) transposeMatrix
 * --------------------
 * Transposes a matrix. If the matrix is square, it transposes in place.
 * If the matrix is rectangular, it creates a new matrix for the result.
 *
 *  matrix (pointer): the original matrix
 *  result (pointer): the transposed matrix, allocated if not square
 *
 *  Returns true if successful, false on failure (e.g., memory allocation issues)
 */
bool transposeMatrix(const Matrix *matrix, Matrix *result) {
    // Check if the matrix is square
    if (isSquare(matrix)) {
        // In-place transpose for square matrix
        for (int i = 0; i < matrix->rows; i++) {
            for (int j = i + 1; j < matrix->cols; j++) {
                // Swap elements at (i, j) and (j, i)
                double temp = *(matrix->data + i * matrix->cols + j);
                *(matrix->data + i * matrix->cols + j) = *(matrix->data + j * matrix->cols + i);
                *(matrix->data + j * matrix->cols + i) = temp;
            }
        }
        // If the matrix is square, the dimensions of the result are the same as the original
        result->rows = matrix->rows;
        result->cols = matrix->cols;
        result->data = matrix->data;
    } else {
        // Allocate memory for the result if the matrix is not square
        result->rows = matrix->cols;
        result->cols = matrix->rows;
        result->data = (double *)malloc(result->rows * result->cols * sizeof(double));
        if (result->data == NULL) {
            printf("Memory allocation failed for transposed matrix.\n");
            return false;
        }

        // Transpose the matrix into the result matrix
        for (int i = 0; i < matrix->rows; i++) {
            for (int j = 0; j < matrix->cols; j++) {
                *(result->data + j * result->cols + i) = *(matrix->data + i * matrix->cols + j);
            }
        }
    }
    return true;
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
 * Function: (bool) multiplymMatrices
 * --------------------
 * Multiplies two matrices and returns whether the multiplication was successful
 * Fails if both matrices have dimensions that do not match
 * This implementation requires that the number of columns of the first matrix
 * Equals the number of rows of the second matrix
 * 
 * The multiplication process is as follows:
 * result_{r,c} = sum^{columns_A - 1}_{k=0} A_{r,k} B_{k,c}
 *
 *  matrix_a (pointer): a pointer to the first matrix struct that you want to sum
 *  matrix_b (pointer): a pointer to the second matrix struct that you want to sum
 * *result_matrix (pointer): a pointer to the result (a Matrix struct)
*/

bool multiplyMatrices(const Matrix *matrix_a, const Matrix *matrix_b, Matrix *result){
    /* Check compatible dimensions*/
    if (matrix_a->cols!= matrix_b->rows){
        printf("Incompatible dimensions in matrix multiplication");
        return false;
    }
    /* Enforce dimensions for result matrix */
    result->rows = matrix_a->cols;
    result->cols = matrix_b->cols;
    /* Multiply */
    int r;
    int c;
    int k;
    for(r = 0; r < matrix_a->rows;r++){
        for(c=0;c<matrix_b->cols;c++){
            /* Initialize element at (r,c)*/
            /* Summing flattened array so have to adjust for dimensions*/
            *(result->data + r * result->cols + c) = 0;
            for(k = 0; k < matrix_a->cols; k++){
                *(result->data + r * result->cols + c) += 
                    (*(matrix_a->data + r * matrix_a->cols + k)) * 
                    (*(matrix_b->data + k * matrix_b->cols + c));
            }
        }
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
    double matrixCData[3][2] = {{1.3,4.3},{5.2,0.0},{6.7,8.8}};
    /* Initialize result matrix */
    double resultData[2][3];
    double resultMultData[2][2];
    /* Generate matrix structs */
    Matrix matrixA = {2,3, (double *)matrixAData};
    Matrix matrixB = {2,3, (double *)matrixBData};
    Matrix matrixC = {3,2, (double *)matrixCData};
    Matrix resultSum = {2,3, (double *)resultData};
    Matrix resultMinus = {2,3, (double *)resultData};
    Matrix resultMult = {2,2, (double *)resultMultData};
    /* Perform sum */
    if (sumMatrices(&matrixA, &matrixB, false, &resultSum)) {
        printf("Sum of matrices:\n");
        printMatrix(&resultSum);
    }
    if (sumMatrices(&matrixA, &matrixB, true, &resultMinus)) {
        printf("Subtraction of matrices:\n");
        printMatrix(&resultMinus);
    }
    /* Perform multiplication */
    if (multiplyMatrices(&matrixA, &matrixC, &resultMult)) {
        printf("Multiplication of matrices:\n");
        printMatrix(&resultMinus);
    }
    /* Test cases for transposing */
    // Define a result matrix for the transpose
    double vectorData[1][3] = {1.1,2.2,3.3};
    Matrix vector = {1,3,(double *)vectorData};
    Matrix resultTrans;
    Matrix vectorTrans;

    // Transpose the matrix
    if (transposeMatrix(&matrixA, &resultTrans)) {
        printf("Original matrix:\n");
        printMatrix(&matrixA);
        printf("Transposed matrix:\n");
        printMatrix(&resultTrans);
        
        // Free memory if the transpose was out-of-place (rectangular)
        if (matrixA.data != resultTrans.data) {
            free(resultTrans.data);
        }
    }
    
    // Transpose the vector
    if (transposeMatrix(&vector, &vectorTrans)) {
        printf("Original vectpr:\n");
        printMatrix(&vector);
        printf("Transposed vector:\n");
        printMatrix(&vectorTrans);
        
        // Free memory if the transpose was out-of-place (rectangular)
        if (vector.data != vectorTrans.data) {
            free(vectorTrans.data);
        }
    }
    return 0;
}



