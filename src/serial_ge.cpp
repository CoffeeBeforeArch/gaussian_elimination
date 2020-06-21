// Implementation of serial GE function

#include <vector>

// Serial implementation
void serial_ge(std::vector<double> &A, std::vector<double> &b, std::size_t N) {
  // For each row in the matrix
  for (std::size_t pivot_row = 0; pivot_row < N; pivot_row++) {
    // Save the pivot value
    double scale = A[N * pivot_row * pivot_row];

    // Divide the remaining elements in the vector
    for (std::size_t col = pivot_row; col < N; col++) {
      A[N * pivot_row + col] /= scale;
    }

    // Scale "b"
    b[pivot_row] /= scale;

    // Eliminate this column from the rest of the matrix
    // For each remaining row in the matrix
    for (std::size_t sub_row = pivot_row + 1; sub_row < N; sub_row++) {
      // Scale factor for eliminating for elemenating this column
      double elim_scale = A[sub_row * N + pivot_row];

      // Finish the remainder of the row
      for (std::size_t col = pivot_row; col < N; col++) {
        A[N * sub_row + col] -= A[N * pivot_row + col] * elim_scale;
      }
      
      // Apply changes to "b"
      b[sub_row] -= b[pivot_row] * elim_scale;
    }
  }
}
