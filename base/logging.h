// Copyright 2017, Beeri 15.  All rights reserved.
// Author: Roman Gershman (romange@gmail.com)
//

#pragma once

#include <string>
#include <glog/logging.h>

namespace base {

class ConsoleLogSink : public google::LogSink {
public:
  virtual void send(google::LogSeverity severity, const char* full_filename,
                    const char* base_filename, int line,
                    const struct ::tm* tm_time,
                    const char* message, size_t message_len) override;

  static ConsoleLogSink* instance();
};

}  // namespace base

#define CONSOLE_INFO LOG_TO_SINK(base::ConsoleLogSink::instance(), INFO)
