#include "cspin/udp_receiver.hpp"

using namespace cspin;

int main(int argc, char** argv)
{
  UDPReceiver receiver("127.0.0.1", 12345);
  receiver.start();

  return 0;
}
