#pragma once

#include <cstdint>
#include <memory>
namespace network {

class Handshake {
public:
  virtual ~Handshake() = default;

  virtual bool performClientHandshake(int socket) = 0;
  virtual bool performServerHandshake(int socket) = 0;

  virtual uint32_t getNegotiatedVersion() const = 0;
  virtual uint32_t getNegotiatedCapabilities() const = 0;
};

} // namespace network
