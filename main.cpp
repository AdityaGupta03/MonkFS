#include "network/include/TCPTransport.h"

int main() {
  network::TCPTransport tcp_transport(network::TCPTransportOpts{
    .listen_addr = ""
  });
  tcp_transport.listenAndAccept();
}
