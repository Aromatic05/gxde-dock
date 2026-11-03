/*
 * Copyright (C) CharOfString <root@charofstring.cc>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 */

#ifndef FRAME_UTIL_SERVICERESTARTTRACKER_H_
#define FRAME_UTIL_SERVICERESTARTTRACKER_H_

class ServiceRestartTracker {
  public:
    explicit ServiceRestartTracker(bool ownerAlreadyPresent = false)
        : m_ownerSeen(ownerAlreadyPresent) {}

    bool ownerChanged(bool oldOwnerPresent, bool newOwnerPresent) {
        // A non-empty old owner proves that this service has run even if its
        // initial registration raced with watcher setup.
        if (oldOwnerPresent) {
            m_ownerSeen = true;
        }

        if (!newOwnerPresent) {
            return false;
        }

        if (!m_ownerSeen) {
            m_ownerSeen = true;
            return false;
        }

        return true;
    }

  private:
    bool m_ownerSeen;
};

#endif  // FRAME_UTIL_SERVICERESTARTTRACKER_H_
