/*
================================================================================
TOPIC 6: ARRAYS AND STRINGS - PART 2: MULTI-DIMENSIONAL ARRAYS
================================================================================

2D ARRAYS (MATRICES):
- Array of arrays
- Two indices: row and column
- Stored in row-major order in memory

SYNTAX:
data_type array_name[rows][cols];
data_type array_name[rows][cols] = { {values}, {values} };

MEMORY:
- 2x3 matrix of ints: 2*3*4 = 24 bytes (on 32-bit system)
- Contiguous memory, row by row

================================================================================
*/

#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  cout << "=== MULTI-DIMENSIONAL ARRAYS (2D ARRAYS / MATRICES) ===" << endl
       << endl;

  // ======================= 2D ARRAY DECLARATION =======================
  cout << "1. 2D ARRAY DECLARATION AND INITIALIZATION:" << endl;

  // Method 1: Without initialization
  int matrix1[2][3];

  // Method 2: With initialization
  int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  cout << "Matrix (2x3):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  // ======================= ACCESSING 2D ARRAY ELEMENTS =======================
  cout << endl << "2. ACCESSING 2D ARRAY ELEMENTS:" << endl;

  cout << "Element at [0][0]: " << matrix[0][0] << endl;
  cout << "Element at [0][2]: " << matrix[0][2] << endl;
  cout << "Element at [1][1]: " << matrix[1][1] << endl;

  // ======================= MODIFYING 2D ARRAY ELEMENTS =======================
  cout << endl << "3. MODIFYING 2D ARRAY ELEMENTS:" << endl;

  matrix[0][0] = 10;
  matrix[1][2] = 60;

  cout << "After modification:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  // ======================= 3D ARRAYS =======================
  cout << endl << "4. 3D ARRAY EXAMPLE (3D MATRIX):" << endl;

  int cube[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};

  cout << "3D Array (2x2x2):" << endl;
  for (int i = 0; i < 2; i++) {
    cout << "Layer " << i << ":" << endl;
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        cout << cube[i][j][k] << " ";
      }
      cout << endl;
    }
  }

  // ======================= SUM OF MATRIX ELEMENTS =======================
  cout << endl << "5. SUM OF ALL MATRIX ELEMENTS:" << endl;

  int sum_matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  int total = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      total += sum_matrix[i][j];
    }
  }

  cout << "Matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << sum_matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Sum: " << total << endl;

  // ======================= ROW SUM =======================
  cout << endl << "6. SUM OF EACH ROW:" << endl;

  int row_sum[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  for (int i = 0; i < 3; i++) {
    int row_total = 0;
    for (int j = 0; j < 3; j++) {
      row_total += row_sum[i][j];
    }
    cout << "Row " << i << " sum: " << row_total << endl;
  }

  // ======================= COLUMN SUM =======================
  cout << endl << "7. SUM OF EACH COLUMN:" << endl;

  int col_sum[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  for (int j = 0; j < 3; j++) {
    int col_total = 0;
    for (int i = 0; i < 3; i++) {
      col_total += col_sum[i][j];
    }
    cout << "Column " << j << " sum: " << col_total << endl;
  }

  // ======================= DIAGONAL SUM =======================
  cout << endl << "8. DIAGONAL SUM (Primary Diagonal):" << endl;

  int diag_sum[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  int diagonal = 0;
  for (int i = 0; i < 3; i++) {
    diagonal += diag_sum[i][i];
  }
  cout << "Primary diagonal sum: " << diagonal << endl;

  // ======================= MATRIX TRANSPOSE =======================
  cout << endl << "9. MATRIX TRANSPOSE:" << endl;

  int original[2][3] = {{1, 2, 3}, {4, 5, 6}};

  int transposed[3][2];

  cout << "Original (2x3):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << original[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      transposed[j][i] = original[i][j];
    }
  }

  cout << "Transposed (3x2):" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      cout << transposed[i][j] << " ";
    }
    cout << endl;
  }

  // ======================= MATRIX ADDITION =======================
  cout << endl << "10. MATRIX ADDITION:" << endl;

  int matA[2][2] = {{1, 2}, {3, 4}};
  int matB[2][2] = {{5, 6}, {7, 8}};
  int matSum[2][2];

  cout << "Matrix A:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << matA[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Matrix B:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << matB[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matSum[i][j] = matA[i][j] + matB[i][j];
    }
  }

  cout << "A + B:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << matSum[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}

/*
OUTPUT:
=== MULTI-DIMENSIONAL ARRAYS (2D ARRAYS / MATRICES) ===

1. 2D ARRAY DECLARATION AND INITIALIZATION:
Matrix (2x3):
1 2 3
4 5 6

2. ACCESSING 2D ARRAY ELEMENTS:
Element at [0][0]: 1
Element at [0][2]: 3
Element at [1][1]: 5

3. MODIFYING 2D ARRAY ELEMENTS:
After modification:
10 2 3
4 5 60

4. 3D ARRAY EXAMPLE (3D MATRIX):
3D Array (2x2x2):
Layer 0:
1 2
3 4
Layer 1:
5 6
7 8

5. SUM OF ALL MATRIX ELEMENTS:
Matrix:
1 2 3
4 5 6
7 8 9
Sum: 45

6. SUM OF EACH ROW:
Row 0 sum: 6
Row 1 sum: 15
Row 2 sum: 24

7. SUM OF EACH COLUMN:
Column 0 sum: 12
Column 1 sum: 15
Column 2 sum: 18

8. DIAGONAL SUM (Primary Diagonal):
Primary diagonal sum: 15

9. MATRIX TRANSPOSE:
Original (2x3):
1 2 3
4 5 6
Transposed (3x2):
1 4
2 5
3 6

10. MATRIX ADDITION:
Matrix A:
1 2
3 4
Matrix B:
5 6
7 8
A + B:
6 8
10 12

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create matrix multiplication program

2. Check if matrix is symmetric

3. Find largest element in matrix

4. Print boundary elements of matrix

5. Rotate matrix 90 degrees clockwise

6. Perform spiral traversal of matrix

================================================================================
*/
