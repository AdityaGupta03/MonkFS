#include "network/include/TCPTransport.h"

#include <iostream>

int main() {
  std::cout << "Starting distributed file server...\n\n";

  network::TCPTransport tcp_transport(network::TCPTransportOpts{
    .listen_addr = ""
  });

  bool status = tcp_transport.listenAndAccept();
  if (!status) {
    std::cerr << "Failed listenAndAccept()";
    return -1;
  }
}
