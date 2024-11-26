#pragma once

#include "Handshake.h"
#include "BasicHandshake.h"

namespace network {

enum class HandshakeType {
  BASIC,
  SECURE,
  CUSTOM
};

class HandshakeFactory {
public:
  inline static std::shared_ptr<Handshake> createHandshake(HandshakeType type) {
    switch (type) {
    case HandshakeType::BASIC:
      return std::make_shared<BasicHandshake>();
    default:
      throw std::runtime_error("Unknown handshake type");
    }
  }
};

} // namespace network
