// Main benchmark function of Gaussian Elimination

#include "benchmark/benchmark.h"

#include <algorithm>
#include <random>
#include <vector>

// Function prototype for serial GE
void serial_ge(std::vector<double> &A, std::size_t N);

static void serial_ge_bench(benchmark::State &s) {
  // Number Dimensions of our matrix
  std::size_t N = s.range(0);

  // Create our random number generators
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_real_distribution<double> dist(-10, 10);

  // Create input matrices
  std::vector<double> A(N * N);

  // Initialize them with random values
  std::generate(begin(A), end(A), [&] { return dist(rng); });

  // Main benchmark loop
  for (auto _ : s) {
    serial_ge(A, N);
  }
}
BENCHMARK(serial_ge_bench)->DenseRange(8, 10);

BENCHMARK_MAIN();
