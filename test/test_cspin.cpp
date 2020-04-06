#include <iostream>
#include <string>

#include "cspin/shared_memory.hpp"

using namespace cspin;

int main(int argc, char** argv)
{
  SharedMemory<double> shm = SharedMemory<double>("shm", true);
  std::cout << "Hello, cspin." << std::endl;

  double a = 40.0;
  shm.write(a);
  double b = 20.0;
  std::cout << b << std::endl;
  shm.read(b);
  std::cout << b << std::endl;

  return 0;
}
