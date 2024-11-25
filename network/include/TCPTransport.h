#ifndef TCPTRANSPORT_H
#define TCPTRANSPORT_H

#include "Peer.h"
#include "Transport.h"
#include "RPC.h"

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <queue>
#include <functional>

namespace network {

struct TCPTransportOpts {
  std::string listen_addr;
} ;

class TCPTransport : public Transport {
public:
  TCPTransport(TCPTransportOpts opts);
  ~TCPTransport();

  std::string addr() const override;
  bool dial(const std::string& addr) override;
  bool listenAndAccept() override;
  std::shared_ptr<Peer> consume() override;
  void close() override;

private:
  void startAcceptLoop();
  void handleConnection(int conn, bool out_bound);

  TCPTransportOpts opts_;
  int listen_socket_;
  std::atomic<bool> running_;
  std::thread accept_thread_;
  std::queue<std::shared_ptr<RPC> > rpc_queue_;
  std::mutex queue_mutex_;
  std::condition_variable queue_cond_var_;
};

}

#endif // TCPTRANSPORT_H
