#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "Peer.h"

#include <memory>
#include <string>

namespace network {

class Transport {
public:
  virtual std::string addr() const = 0;
  virtual bool dial(const std::string& address) = 0;
  virtual bool listenAndAccept() = 0;
  virtual std::shared_ptr<Peer> consume() = 0;
  virtual void close() = 0;
};

} // namespace network

#endif // TRANSPORT_H
