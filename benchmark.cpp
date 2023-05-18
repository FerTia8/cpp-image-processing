/**
	benchmark.cpp
	Purpose: Times the execution of the provided tests and
  appends log results to 'benchmarks.txt'
*/

#include <iostream>
#include <chrono>
#include <fstream>

int main()
{
  // Gets clock with the smallest tick period.
  auto start = std::chrono::high_resolution_clock::now();

  // Runs the ./test executable and redirects its outputs to a discardable file.
  std::system("./test > /dev/null 2>&1");

  // Marks the end of the program execution and registers time duration.
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "> Execution time: " << duration.count() << " milliseconds" << std::endl;

  // Gets current time (to be added to benchmarks.txt).
  auto time_n = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  // Opens benchmarks.txt in append mode.
  std::ofstream benchmarkTxtFile;
  benchmarkTxtFile.open("benchmarks.txt", std::ios_base::app);

  // Appends current time and test execution duration to benchmarks.txt.
  benchmarkTxtFile << '\n' << ctime(&time_n) << "    " << duration.count() << " ms"; 
  return 0;
}