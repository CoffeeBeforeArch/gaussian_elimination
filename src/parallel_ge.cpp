// Implementation of parallel GE function

#include <pthread.h>
#include <vector>

// Parallel implementation
void parallel_ge(std::vector<double> &A, std::size_t N,
                 pthread_barrier_t &barrier, std::size_t start_row,
                 std::size_t end_row) {
  // For each row in the matrix
  for (std::size_t pivot_row = 0; pivot_row < N; pivot_row++) {
    if (pivot_row >= start_row && pivot_row < end_row) {
      // Save the pivot value
      double scale = A[N * pivot_row * pivot_row];

      // Divide the remaining elements in the vector
      for (std::size_t col = pivot_row; col < N; col++) {
        A[N * pivot_row + col] /= scale;
      }

      // This will signal the other threads to continue
      pthread_barrier_wait(&barrier);

      // Eliminate this column from the rest of the matrix
      // For each remaining row in the matrix
      for (std::size_t sub_row = pivot_row + 1; sub_row < N; sub_row++) {
        // Scale factor for eliminating for elemenating this column
        double elim_scale = A[sub_row * N + pivot_row];

        // Finish the remainder of the row
        for (std::size_t col = pivot_row; col < N; col++) {
          A[N * sub_row + col] -= A[N * pivot_row + col] * elim_scale;
        }
      }
    } else {
      // Wait for the signal to continue
      pthread_barrier_wait(&barrier);
      
      // Eliminate this column from the rest of the matrix
      // For each remaining row in the matrix
      for (std::size_t sub_row = start_row; sub_row < end_row; sub_row++) {
        // Scale factor for eliminating for elemenating this column
        double elim_scale = A[sub_row * N + pivot_row];

        // Finish the remainder of the row
        for (std::size_t col = pivot_row; col < N; col++) {
          A[N * sub_row + col] -= A[N * pivot_row + col] * elim_scale;
        }
      }
    }
  }
}
