#include "../include/TCPTransport.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include <memory>

namespace network {

TCPTransport::TCPTransport(TCPTransportOpts opts) : opts_(std::move(opts)), listen_socket_(-1), running_(false) {}

TCPTransport::~TCPTransport() {
  this->close();
}

std::string TCPTransport::addr() const {
  return opts_.listen_addr;
}

bool TCPTransport::dial(const std::string& addr) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Failed to create socket\n";
    return false;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8008);
  int err = inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr);
  if (err <= 0) {
    std::cerr << "Invalid address\n";
    ::close(sock);
    return false;
  }

  err = connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (err < 0) {
    std::cerr << "Connection failed\n";
    ::close(sock);
    return false;
  }

  this->handleConnection(sock, true);

  return false;
}

bool TCPTransport::listenAndAccept() {
  listen_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_socket_  < 0) {
    std::cerr << "Failed to create socket\n";
    return false;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8008);
  int err = bind(listen_socket_, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (err < 0) {
    std::cerr << "Bind failed\n";
    ::close(listen_socket_);
    return false;
  }

  err = listen(listen_socket_, 3);
  if (err < 0) {
    std::cerr << "Listen failed\n";
    ::close(listen_socket_);
    return false;
  }

  running_ = true;
  accept_thread_ = std::thread(&TCPTransport::startAcceptLoop, this);
  return true;
}

std::shared_ptr<Peer> TCPTransport::consume() {
  // TODO
  return nullptr;
}

void TCPTransport::close() {
  running_ = false;

  if (accept_thread_.joinable()) {
    accept_thread_.join();
  }

  if (listen_socket_ >= 0) {
    ::close(listen_socket_);
    listen_socket_ = -1;
  }
}

void TCPTransport::startAcceptLoop() {
  while (running_) {
    int client = accept(listen_socket_, nullptr, nullptr);
    if (client >= 0) {
      this->handleConnection(client, false);
    } else if (running_) {
      std::cerr << "Failed accept\n";
    }
  }
}

void TCPTransport::handleConnection(int conn, bool out_bound) {
  if (!handshake_) {
    handshake_ = HandshakeFactory::createHandshake(HandshakeType::BASIC);
  }

  bool success;
  if (out_bound) {
    success = handshake_->performClientHandshake(conn);
  } else {
    success = handshake_->performServerHandshake(conn);
  }

  if (!success) {
    std::cerr << "Handshake failed\n";
    ::close(conn);
    return;
  }

  // TODO
}

} // namespace network
