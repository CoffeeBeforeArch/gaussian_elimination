// Implementation of serial GE function

#include <vector>

// Serial implementation
void serial_ge(std::vector<double> &A, std::vector<double> &b, std::size_t N) {
  // For each row in the matrix
  for (std::size_t pivot_row = 0; pivot_row < N; pivot_row++) {
    // Save the pivot value
    double scale = A[N * pivot_row * pivot_row];

    // Set the pivot equal to 1
    A[N * pivot_row + pivot_row] = 1.0;

    // Divide the remaining elements in the vector
    for (std::size_t col = pivot_row + 1; col < N; col++) {
      A[N * pivot_row + col] /= scale;
    }

    // Scale "b"
    b[pivot_row] /= scale;

    // Eliminate this column from the rest of the matrix
    // For each remaining row in the matrix
    for (std::size_t sub_row = pivot_row + 1; sub_row < N; sub_row++) {
      // Scale factor for eliminating pivot element from later rows
      double elim_scale = A[sub_row * N + pivot_row];

      // Eliminate the pivot element
      A[N * sub_row + pivot_row] = 0.0;

      // Apply changes to "b"
      b[sub_row] -= b[pivot_row] * elim_scale;

      // Finish the remainder of the row
      for (std::size_t col = pivot_row + 1; col < N; col++) {
        A[N * sub_row + col] -= A[N * pivot_row + col] * elim_scale;
      }
    }
  }
}
