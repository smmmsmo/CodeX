#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.2: MULTI-DIMENSIONAL ARRAYS
 * =====================================================================
 *
 * WHAT ARE MULTI-DIMENSIONAL ARRAYS?
 * Multi-dimensional arrays are arrays of arrays, used to represent
 * matrices, tables, grids, and higher-dimensional data structures.
 * They are essential for graph problems, dynamic programming, and
 * grid-based competitive programming problems.
 *
 * KEY CONCEPTS COVERED:
 * 1. 2D array declaration and initialization
 * 2. Row-major vs column-major storage
 * 3. Accessing and modifying 2D arrays
 * 4. Passing 2D arrays to functions
 * 5. Matrix operations (add, multiply, transpose)
 * 6. Matrix traversal patterns
 * 7. Spiral matrix traversal
 * 8. Diagonal traversal
 * 9. 3D arrays and higher dimensions
 * 10. Jagged arrays (arrays of different sizes)
 * 11. Dynamic 2D arrays using vectors
 * 12. Common matrix algorithms
 *
 * =====================================================================
 * 2D ARRAY BASICS
 * =====================================================================
 *
 * DECLARATION:
 *    data_type array_name[rows][cols];
 *
 * INITIALIZATION:
 *    int matrix[3][4] = {
 *        {1, 2, 3, 4},
 *        {5, 6, 7, 8},
 *        {9, 10, 11, 12}
 *    };
 *
 * MEMORY LAYOUT (Row-major order in C++):
 *    Row 0: [1][2][3][4]  Row 1: [5][6][7][8]  Row 2: [9][10][11][12]
 *    Stored contiguously in memory
 *
 * ACCESSING:
 *    matrix[row][col]  // 0-indexed
 *
 * TIME COMPLEXITIES:
 *    Access: O(1)
 *    Traversal: O(rows * cols)
 *    Search (unsorted): O(rows * cols)
 *    Search (row/col sorted): O(rows + cols) or O(log(rows*cols))
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: 2D ARRAY DECLARATION AND INITIALIZATION
// ==============
void example1_2d_declaration() {
  cout << "\n============== EXAMPLE 1: 2D ARRAY DECLARATION =============="
       << endl;
  cout << "Different ways to create and initialize 2D arrays\n" << endl;

  // Method 1: Full initialization
  int matrix1[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  cout << "Method 1 - Full initialization:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cout << matrix1[i][j] << "\t";
    }
    cout << endl;
  }

  // Method 2: Partial initialization (rest = 0)
  int matrix2[3][3] = {{1, 2}, {3}, {4, 5, 6}};

  cout << "\nMethod 2 - Partial initialization:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix2[i][j] << "\t";
    }
    cout << endl;
  }

  // Method 3: Initialize all to zero
  int matrix3[2][3] = {0};

  cout << "\nMethod 3 - All zeros:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix3[i][j] << "\t";
    }
    cout << endl;
  }

  // Method 4: Manual initialization
  int matrix4[2][2];
  matrix4[0][0] = 10;
  matrix4[0][1] = 20;
  matrix4[1][0] = 30;
  matrix4[1][1] = 40;

  cout << "\nMethod 4 - Manual:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << matrix4[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nNote: First dimension can be omitted, second cannot!" << endl;
}

// ============== EXAMPLE 2: 2D ARRAY TRAVERSAL PATTERNS ==============
void example2_traversal_patterns() {
  cout << "\n============== EXAMPLE 2: TRAVERSAL PATTERNS =============="
       << endl;
  cout << "Different ways to traverse 2D arrays\n" << endl;

  int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  int rows = 3, cols = 4;

  // Row-wise traversal
  cout << "Row-wise traversal:" << endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << " ";
    }
  }
  cout << endl;

  // Column-wise traversal
  cout << "\nColumn-wise traversal:" << endl;
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      cout << matrix[i][j] << " ";
    }
  }
  cout << endl;

  // Diagonal traversal (primary diagonal)
  cout << "\nPrimary diagonal:" << endl;
  int n = min(rows, cols);
  for (int i = 0; i < n; i++) {
    cout << matrix[i][i] << " ";
  }
  cout << endl;

  // Anti-diagonal
  cout << "\nAnti-diagonal (for square matrix):" << endl;
  for (int i = 0; i < n; i++) {
    cout << matrix[i][n - 1 - i] << " ";
  }
  cout << endl;

  // Zigzag pattern
  cout << "\nZigzag pattern:" << endl;
  for (int i = 0; i < rows; i++) {
    if (i % 2 == 0) {
      // Left to right
      for (int j = 0; j < cols; j++) {
        cout << matrix[i][j] << " ";
      }
    } else {
      // Right to left
      for (int j = cols - 1; j >= 0; j--) {
        cout << matrix[i][j] << " ";
      }
    }
  }
  cout << endl;
}

// ============== EXAMPLE 3: SPIRAL MATRIX TRAVERSAL ==============
void spiral_traversal(int matrix[][4], int rows, int cols) {
  int top = 0, bottom = rows - 1;
  int left = 0, right = cols - 1;

  while (top <= bottom && left <= right) {
    // Traverse right
    for (int j = left; j <= right; j++) {
      cout << matrix[top][j] << " ";
    }
    top++;

    // Traverse down
    for (int i = top; i <= bottom; i++) {
      cout << matrix[i][right] << " ";
    }
    right--;

    // Traverse left (if row remains)
    if (top <= bottom) {
      for (int j = right; j >= left; j--) {
        cout << matrix[bottom][j] << " ";
      }
      bottom--;
    }

    // Traverse up (if column remains)
    if (left <= right) {
      for (int i = bottom; i >= top; i--) {
        cout << matrix[i][left] << " ";
      }
      left++;
    }
  }
}

void example3_spiral_traversal() {
  cout << "\n============== EXAMPLE 3: SPIRAL TRAVERSAL ==============" << endl;
  cout << "Traverse matrix in spiral order - Classic interview problem\n"
       << endl;

  int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  cout << "Matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nSpiral order: ";
  spiral_traversal(matrix, 3, 4);
  cout << endl;

  cout << "\nAlgorithm: Use four pointers (top, bottom, left, right)" << endl;
  cout << "Time Complexity: O(rows * cols)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 4: MATRIX TRANSPOSE ==============
void transpose_square(int matrix[][3], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      swap(matrix[i][j], matrix[j][i]);
    }
  }
}

void example4_matrix_transpose() {
  cout << "\n============== EXAMPLE 4: MATRIX TRANSPOSE ==============" << endl;
  cout << "Swap rows and columns - O(n²)\n" << endl;

  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  cout << "Original matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  transpose_square(matrix, 3);

  cout << "\nTransposed matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nIn-place swap: matrix[i][j] <-> matrix[j][i]" << endl;
  cout << "Time Complexity: O(n²)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 5: MATRIX ROTATION ==============
void rotate_90_clockwise(int matrix[][3], int n) {
  // Step 1: Transpose
  transpose_square(matrix, n);

  // Step 2: Reverse each row
  for (int i = 0; i < n; i++) {
    reverse(matrix[i], matrix[i] + n);
  }
}

void example5_matrix_rotation() {
  cout << "\n============== EXAMPLE 5: MATRIX ROTATION ==============" << endl;
  cout << "Rotate matrix 90° clockwise - O(n²)\n" << endl;

  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  cout << "Original matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  rotate_90_clockwise(matrix, 3);

  cout << "\nRotated 90° clockwise:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nAlgorithm: Transpose + Reverse each row" << endl;
  cout << "For anti-clockwise: Reverse each row + Transpose" << endl;
  cout << "Time Complexity: O(n²)" << endl;
}

// ============== EXAMPLE 6: MATRIX ADDITION ==============
void matrix_add(int a[][3], int b[][3], int result[][3], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[i][j] = a[i][j] + b[i][j];
    }
  }
}

void example6_matrix_addition() {
  cout << "\n============== EXAMPLE 6: MATRIX ADDITION ==============" << endl;
  cout << "Add two matrices - O(rows * cols)\n" << endl;

  int a[2][3] = {{1, 2, 3}, {4, 5, 6}};

  int b[2][3] = {{7, 8, 9}, {10, 11, 12}};

  int result[2][3];

  matrix_add(a, b, result, 2, 3);

  cout << "Matrix A:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << a[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nMatrix B:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << b[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nResult (A + B):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << result[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nElement-wise operation: result[i][j] = a[i][j] + b[i][j]" << endl;
}

// ============== EXAMPLE 7: MATRIX MULTIPLICATION ==============
void matrix_multiply(int a[][2], int b[][3], int result[][3], int r1, int c1,
                     int c2) {
  // Initialize result to 0
  for (int i = 0; i < r1; i++) {
    for (int j = 0; j < c2; j++) {
      result[i][j] = 0;
    }
  }

  // Multiply
  for (int i = 0; i < r1; i++) {
    for (int j = 0; j < c2; j++) {
      for (int k = 0; k < c1; k++) {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void example7_matrix_multiplication() {
  cout << "\n============== EXAMPLE 7: MATRIX MULTIPLICATION =============="
       << endl;
  cout << "Multiply two matrices - O(r1 * c1 * c2)\n" << endl;

  int a[2][2] = {{1, 2}, {3, 4}};

  int b[2][3] = {{5, 6, 7}, {8, 9, 10}};

  int result[2][3];

  matrix_multiply(a, b, result, 2, 2, 3);

  cout << "Matrix A (2x2):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << a[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nMatrix B (2x3):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << b[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nResult (A × B) (2x3):" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      cout << result[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nFormula: result[i][j] = Σ(a[i][k] * b[k][j]) for k = 0 to c1-1"
       << endl;
  cout << "Note: Number of columns in A must equal number of rows in B" << endl;
}

// ============== EXAMPLE 8: SEARCH IN ROW-COLUMN SORTED MATRIX ==============
bool search_sorted_matrix(int matrix[][4], int rows, int cols, int target) {
  int row = 0, col = cols - 1; // Start from top-right corner

  while (row < rows && col >= 0) {
    if (matrix[row][col] == target) {
      cout << "Found at (" << row << ", " << col << ")" << endl;
      return true;
    } else if (matrix[row][col] > target) {
      col--; // Move left
    } else {
      row++; // Move down
    }
  }
  return false;
}

void example8_search_sorted_matrix() {
  cout << "\n============== EXAMPLE 8: SEARCH IN SORTED MATRIX =============="
       << endl;
  cout << "Search in row-wise and column-wise sorted matrix - O(rows + cols)\n"
       << endl;

  int matrix[4][4] = {
      {10, 20, 30, 40}, {15, 25, 35, 45}, {27, 29, 37, 48}, {32, 33, 39, 50}};

  cout << "Matrix (sorted row-wise and column-wise):" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  int targets[] = {29, 100, 10, 50};
  for (int target : targets) {
    cout << "\nSearching for " << target << ": ";
    if (!search_sorted_matrix(matrix, 4, 4, target)) {
      cout << "Not found" << endl;
    }
  }

  cout << "\nAlgorithm: Start from top-right, move left or down" << endl;
  cout << "Time Complexity: O(rows + cols)" << endl;
}

// ============== EXAMPLE 9: BOUNDARY ELEMENTS ==============
void print_boundary(int matrix[][4], int rows, int cols) {
  // Print first row
  for (int j = 0; j < cols; j++) {
    cout << matrix[0][j] << " ";
  }

  // Print last column (excluding corners)
  for (int i = 1; i < rows; i++) {
    cout << matrix[i][cols - 1] << " ";
  }

  // Print last row in reverse (excluding corners, if rows > 1)
  if (rows > 1) {
    for (int j = cols - 2; j >= 0; j--) {
      cout << matrix[rows - 1][j] << " ";
    }
  }

  // Print first column in reverse (excluding corners, if cols > 1)
  if (cols > 1) {
    for (int i = rows - 2; i > 0; i--) {
      cout << matrix[i][0] << " ";
    }
  }
}

void example9_boundary_elements() {
  cout << "\n============== EXAMPLE 9: BOUNDARY ELEMENTS =============="
       << endl;
  cout << "Print boundary of matrix in clockwise order\n" << endl;

  int matrix[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  cout << "Matrix:" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nBoundary elements (clockwise): ";
  print_boundary(matrix, 4, 4);
  cout << endl;

  cout << "\nTime Complexity: O(rows + cols)" << endl;
}

// ============== EXAMPLE 10: WAVE PRINT ==============
void wave_print(int matrix[][4], int rows, int cols) {
  for (int j = 0; j < cols; j++) {
    if (j % 2 == 0) {
      // Top to bottom
      for (int i = 0; i < rows; i++) {
        cout << matrix[i][j] << " ";
      }
    } else {
      // Bottom to top
      for (int i = rows - 1; i >= 0; i--) {
        cout << matrix[i][j] << " ";
      }
    }
  }
}

void example10_wave_print() {
  cout << "\n============== EXAMPLE 10: WAVE PRINT ==============" << endl;
  cout << "Print matrix in wave form (column-wise alternating)\n" << endl;

  int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  cout << "Matrix:" << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\nWave print: ";
  wave_print(matrix, 3, 4);
  cout << endl;

  cout << "\nPattern: Column 0 (↓), Column 1 (↑), Column 2 (↓), ..." << endl;
}

// ============== EXAMPLE 11: DYNAMIC 2D ARRAYS USING VECTORS ==============
void example11_vector_2d() {
  cout << "\n============== EXAMPLE 11: DYNAMIC 2D ARRAYS (VECTORS) "
          "=============="
       << endl;
  cout << "Using vector<vector<int>> for flexible 2D arrays\n" << endl;

  // Create 3x4 matrix
  vector<vector<int>> matrix(3, vector<int>(4));

  // Fill with values
  int value = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = value++;
    }
  }

  cout << "Vector-based 2D array:" << endl;
  for (const auto &row : matrix) {
    for (int val : row) {
      cout << val << "\t";
    }
    cout << endl;
  }

  // Jagged array (rows of different sizes)
  vector<vector<int>> jagged = {{1, 2}, {3, 4, 5, 6}, {7}};

  cout << "\nJagged array (different row sizes):" << endl;
  for (size_t i = 0; i < jagged.size(); i++) {
    cout << "Row " << i << " (size " << jagged[i].size() << "): ";
    for (int val : jagged[i]) {
      cout << val << " ";
    }
    cout << endl;
  }

  cout << "\nAdvantages: Dynamic sizing, no size limit, easy resizing" << endl;
  cout << "Use .size() to get dimensions" << endl;
}

// ============== EXAMPLE 12: 3D ARRAYS ==============
void example12_3d_arrays() {
  cout << "\n============== EXAMPLE 12: 3D ARRAYS ==============" << endl;
  cout << "Three-dimensional arrays for cube/volume data\n" << endl;

  int cube[2][3][4] = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
                       {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}};

  cout << "3D Array [2][3][4]:" << endl;
  for (int i = 0; i < 2; i++) {
    cout << "Layer " << i << ":" << endl;
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        cout << cube[i][j][k] << "\t";
      }
      cout << endl;
    }
    cout << endl;
  }

  cout << "Access: cube[layer][row][col]" << endl;
  cout << "Example: cube[1][2][3] = " << cube[1][2][3] << endl;

  cout << "\nUse cases: 3D graphics, volume data, DP with 3 states" << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. 2D ARRAY BASICS:
 *    - Declaration: type arr[rows][cols]
 *    - Access: arr[i][j], both 0-indexed
 *    - Stored in row-major order in memory
 *
 * 2. COMMON OPERATIONS:
 *    - Traversal: row-wise O(r*c), column-wise O(r*c)
 *    - Transpose: swap arr[i][j] with arr[j][i] - O(n²)
 *    - Rotation: transpose + reverse rows - O(n²)
 *
 * 3. IMPORTANT ALGORITHMS:
 *    - Spiral traversal: O(r*c) using 4 pointers
 *    - Search in sorted matrix: O(r+c) from top-right
 *    - Matrix multiplication: O(r1*c1*c2)
 *
 * 4. MATRIX PATTERNS:
 *    - Boundary, Wave, Zigzag, Diagonal
 *    - Each has specific traversal order
 *
 * 5. DYNAMIC 2D ARRAYS:
 *    - Use vector<vector<int>> for flexibility
 *    - Supports jagged arrays (different row sizes)
 *    - Better than raw pointers for most cases
 *
 * 6. PASSING TO FUNCTIONS:
 *    - Must specify column size: func(int arr[][COLS])
 *    - Or use pointers/vectors for flexibility
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. Always check matrix bounds in all directions
 * 2. For sorted matrices, think about starting position
 * 3. Spiral traversal: use 4 pointers and careful bounds
 * 4. Matrix rotation = transpose + reverse (learn both directions)
 * 5. Use vectors for dynamic/unknown sizes
 * 6. DP problems often use 2D arrays - initialize properly
 * 7. Graph adjacency matrix is a 2D array
 * 8. Grid-based problems: treat as matrix, use BFS/DFS
 * 9. Learn all traversal patterns - they appear frequently
 * 10. Practice matrix problems on LeetCode/Codeforces
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Confusing rows and columns (i for rows, j for cols)
 * 2. Off-by-one errors in spiral/boundary traversal
 * 3. Not checking bounds before accessing elements
 * 4. Wrong multiplication dimensions (A: m×n, B: n×p → Result: m×p)
 * 5. Forgetting to initialize result matrix to 0
 * 6. Not specifying column size when passing to function
 * 7. Assuming square matrix when it's rectangular
 * 8. Cache inefficiency (column-wise access slower than row-wise)
 * 9. Stack overflow with large static arrays (use vectors/dynamic)
 * 10. Comparing 2D arrays with == (doesn't work)
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "     MULTI-DIMENSIONAL ARRAYS - COMPREHENSIVE GUIDE       " << endl;
  cout << "=========================================================" << endl;

  example1_2d_declaration();
  example2_traversal_patterns();
  example3_spiral_traversal();
  example4_matrix_transpose();
  example5_matrix_rotation();
  example6_matrix_addition();
  example7_matrix_multiplication();
  example8_search_sorted_matrix();
  example9_boundary_elements();
  example10_wave_print();
  example11_vector_2d();
  example12_3d_arrays();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Set matrix zeros (if element is 0, set entire row/col to 0)"
       << endl;
  cout << "2. Rotate matrix 180 degrees" << endl;
  cout << "3. Find saddle point (min in row, max in column)" << endl;
  cout << "4. Print matrix in diagonal order" << endl;
  cout << "5. Find the kth smallest element in row-col sorted matrix" << endl;
  cout << "6. Count islands in binary matrix (1=land, 0=water)" << endl;
  cout << "7. Find if path exists from top-left to bottom-right" << endl;
  cout << "8. Maximum sum rectangle in matrix" << endl;
  cout << "9. Print all paths from top-left to bottom-right" << endl;
  cout << "10. Median in row-wise sorted matrix" << endl;

  return 0;
}
