// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/notifications/notification.h"

#include "chrome/browser/notifications/desktop_notification_service.h"

Notification::Notification(const GURL& origin_url,
                           const GURL& content_url,
                           const string16& display_source,
                           const string16& replace_id,
                           NotificationDelegate* delegate)
    : origin_url_(origin_url),
      is_html_(true),
      content_url_(content_url),
      display_source_(display_source),
      replace_id_(replace_id),
      delegate_(delegate) {
}

Notification::Notification(const GURL& origin_url,
                           const GURL& icon_url,
                           const string16& title,
                           const string16& body,
                           WebKit::WebTextDirection dir,
                           const string16& display_source,
                           const string16& replace_id,
                           NotificationDelegate* delegate)
    : origin_url_(origin_url),
      is_html_(false),
      title_(title),
      body_(body),
      display_source_(display_source),
      replace_id_(replace_id),
      delegate_(delegate) {
  // "Upconvert" the string parameters to a data: URL.
  content_url_ = GURL(DesktopNotificationService::CreateDataUrl(
      icon_url, title, body, dir));
}

Notification::Notification(const Notification& notification)
    : origin_url_(notification.origin_url()),
      is_html_(notification.is_html()),
      content_url_(notification.content_url()),
      title_(notification.title()),
      body_(notification.body()),
      display_source_(notification.display_source()),
      replace_id_(notification.replace_id()),
      delegate_(notification.delegate()) {
}

Notification::~Notification() {}

Notification& Notification::operator=(const Notification& notification) {
  origin_url_ = notification.origin_url();
  is_html_ = notification.is_html();
  content_url_ = notification.content_url();
  title_ = notification.title();
  body_ = notification.body();
  display_source_ = notification.display_source();
  replace_id_ = notification.replace_id();
  delegate_ = notification.delegate();
  return *this;
}
