/*
 * Copyright (C) 2021 The Android Open Source Project
 * Copyright (C) 2024 The halogenOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CancellationSignal.h"

namespace aidl {
namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {


CancellationSignal::CancellationSignal(Session* session)
    : mSession(session) {}

ndk::ScopedAStatus CancellationSignal::cancel() {
    return mSession->cancel();
}

} // namespace fingerprint
} // namespace biometrics
} // namespace hardware
} // namespace android
} // namespace aidl
