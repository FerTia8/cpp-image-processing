#include <iostream>
#include <chrono>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  std::system("./test > /dev/null 2>&1");

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

  return 0;
}