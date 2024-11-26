#pragma once

#include <string>
#include <vector>

namespace network {

const int IncomingMessage = 0x1;
const int IncomingStream = 0x2;

struct RPC {
  std::string from;
  std::vector<uint8_t> payload;
  bool stream;
};

} // namespace network
