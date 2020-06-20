// Main benchmark function of Gaussian Elimination

#include "benchmark/benchmark.h"

#include <algorithm>
#include <random>

// Function prototype for serial GE
void serial_ge(double *A, double *b, std::size_t N);

static void serial_ge_bench(benchmark::State &s) {
  // Number Dimensions of our matrix
  std::size_t N = s.range(0);

  // Create our random number generators
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_real_distribution<double> dist(-10, 10);

  // Create input matrices
  double *A = new double[N * N];
  double *b = new double[N];

  // Initialize them with random values
  std::generate(A, A + (N * N), [&] { return dist(rng); });
  std::generate(b, A + N, [&] { return dist(rng); });

  // Main benchmark loop
  for (auto _ : s) {
    serial_ge(A, b, N);
  }

  // Free memory
  delete[] A;
  delete[] b;
}
BENCHMARK(serial_ge_bench)->DenseRange(8, 10)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
