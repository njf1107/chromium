// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/renderer/devtools_agent_filter.h"

#include "base/bind.h"
#include "base/message_loop.h"
#include "content/common/devtools_messages.h"
#include "content/renderer/devtools_agent.h"
#include "content/renderer/plugin_channel_host.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/WebDevToolsAgent.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/platform/WebString.h"

using WebKit::WebDevToolsAgent;
using WebKit::WebString;

namespace {

class MessageImpl : public WebDevToolsAgent::MessageDescriptor {
 public:
  MessageImpl(const std::string& message, int host_id)
      : msg(message),
        host_id(host_id) {
  }
  virtual ~MessageImpl() {}
  virtual WebDevToolsAgent* agent() {
    DevToolsAgent* agent = DevToolsAgent::FromHostId(host_id);
    if (!agent)
      return 0;
    return agent->GetWebAgent();
  }
  virtual WebString message() { return WebString::fromUTF8(msg); }
 private:
  std::string msg;
  int host_id;
};

// Made static to allow DevToolsAgent to use it for replying directly
// from IO thread.
int g_current_routing_id = 0;

}  // namespace

DevToolsAgentFilter::DevToolsAgentFilter()
    : message_handled_(false),
      render_thread_loop_(MessageLoop::current()) {
}

bool DevToolsAgentFilter::OnMessageReceived(const IPC::Message& message) {
  // Dispatch debugger commands directly from IO.
  message_handled_ = true;
  g_current_routing_id = message.routing_id();
  IPC_BEGIN_MESSAGE_MAP(DevToolsAgentFilter, message)
    IPC_MESSAGE_HANDLER(DevToolsAgentMsg_DispatchOnInspectorBackend,
                        OnDispatchOnInspectorBackend)
    IPC_MESSAGE_UNHANDLED(message_handled_ = false)
  IPC_END_MESSAGE_MAP()
  return message_handled_;
}

DevToolsAgentFilter::~DevToolsAgentFilter() {}

void DevToolsAgentFilter::OnDispatchOnInspectorBackend(
    const std::string& message) {
  if (!WebDevToolsAgent::shouldInterruptForMessage(
          WebString::fromUTF8(message))) {
      message_handled_ = false;
      return;
  }
  WebDevToolsAgent::interruptAndDispatch(
      new MessageImpl(message, g_current_routing_id));

  render_thread_loop_->PostTask(
      FROM_HERE, base::Bind(&WebDevToolsAgent::processPendingMessages));
}
