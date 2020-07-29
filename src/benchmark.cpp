// Main benchmark function of Gaussian Elimination

#include "benchmark/benchmark.h"

#include <pthread.h>
#include <algorithm>
#include <random>
#include <thread>
#include <vector>

// Function prototype for serial GE
void serial_ge(std::vector<double> &A, std::size_t N);

// Parallel implementation
void parallel_ge(std::vector<double> &A, std::size_t N,
                 pthread_barrier_t &barrier, std::size_t start_row,
                 std::size_t end_row);

static void serial_ge_bench(benchmark::State &s) {
  // Number Dimensions of our matrix
  std::size_t N =  1 << s.range(0);

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

static void parallel_ge_bench(benchmark::State &s) {
  // Number Dimensions of our matrix
  std::size_t N = 1 << s.range(0);

  // Create our random number generators
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_real_distribution<double> dist(-10, 10);

  // Create input matrices
  std::vector<double> A(N * N);

  // Initialize them with random values
  std::generate(begin(A), end(A), [&] { return dist(rng); });

  // Set up threads
  std::size_t num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  
  // Initialize barrier
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, num_threads);
  
  // Number of rows for each thread
  std::size_t n_rows = N / num_threads;

  // Main benchmark loop
  for (auto _ : s) {
    // Launch threads
    std::size_t end_row = 0;
    for (std::size_t i = 0; i < num_threads; i++) {
      auto start_row = i * n_rows;
      end_row = start_row + n_rows;
      threads.emplace_back(
          [&] { parallel_ge(A, N, barrier, start_row, end_row); });
    }

    // Wait for all threads to complete
    for (auto &t : threads) t.join();

    // Clear the threads each iteration of the benchmark
    threads.clear();
  }
}
BENCHMARK(parallel_ge_bench)->DenseRange(8, 10)->UseRealTime();

BENCHMARK_MAIN();
