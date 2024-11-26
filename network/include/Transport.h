#pragma once

#include "Handshake.h"
#include "HandshakeFactory.h"
#include "Peer.h"

#include <memory>
#include <string>
#include <utility>

namespace network {

class Transport {
public:
  Transport();
  virtual ~Transport() = default;

  // Handshake funcs
  inline void setHandshake(HandshakeType type) {
    this->handshake_ = HandshakeFactory::createHandshake(type);
  }

  inline void setHandshake(std::shared_ptr<Handshake> custom_func) {
    this->handshake_ = std::move(custom_func);
  }

  // Funcs implemented by children
  virtual std::string addr() const = 0;
  virtual bool dial(const std::string& address) = 0;
  virtual bool listenAndAccept() = 0;
  virtual std::shared_ptr<Peer> consume() = 0;
  virtual void close() = 0;

protected:
  // Hanshake protocol between client and server
  std::shared_ptr<Handshake> handshake_;
};

} // namespace network
