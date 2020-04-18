// Copyright 2020, Beeri 15.  All rights reserved.
// Author: Roman Gershman (romange@gmail.com)
//
#pragma once

#include <boost/intrusive/slist.hpp>
#include <functional>
#include "util/uring/fiber_socket.h"

namespace util {
namespace uring {

class Proactor;
class AcceptServer;

class Connection {
  using connection_hook_t = ::boost::intrusive::slist_member_hook<
      ::boost::intrusive::link_mode<::boost::intrusive::auto_unlink>>;
  connection_hook_t hook_;


  void SetSocket(FiberSocket&& s) { socket_ = std::move(s); }
  using member_hook_t =
      ::boost::intrusive::member_hook<Connection, connection_hook_t, &Connection::hook_>;

  auto native_handle() const { return socket_.native_handle(); }

 public:
  virtual ~Connection() {}

 protected:

  // The main loop for a connection. Runs in the same proactor thread as of socket_.
  virtual void HandleRequests() = 0;

  FiberSocket socket_;
  friend class AcceptServer;
};

}  // namespace uring
}  // namespace util
