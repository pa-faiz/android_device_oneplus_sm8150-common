/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/biometrics/fingerprint/BnFingerprint.h>
#include <vendor/oneplus/fingerprint/extension/1.0/IVendorFingerprintExtensions.h>
#include <vendor/oneplus/hardware/display/1.0/IOneplusDisplay.h>

#include "LockoutTracker.h"
#include "Session.h"

using ::android::sp;
using ::aidl::android::hardware::biometrics::fingerprint::ISession;
using ::aidl::android::hardware::biometrics::fingerprint::ISessionCallback;
using ::aidl::android::hardware::biometrics::fingerprint::SensorProps;
using ::aidl::android::hardware::biometrics::fingerprint::FingerprintSensorType;
using ::vendor::oneplus::fingerprint::extension::V1_0::IVendorFingerprintExtensions;
using ::vendor::oneplus::hardware::display::V1_0::IOneplusDisplay;

namespace aidl {
namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {

class Fingerprint : public BnFingerprint {
public:
    Fingerprint();
    ~Fingerprint();

    ndk::ScopedAStatus getSensorProps(std::vector<SensorProps>* _aidl_return) override;
    ndk::ScopedAStatus createSession(int32_t sensorId, int32_t userId,
                                     const std::shared_ptr<ISessionCallback>& cb,
                                     std::shared_ptr<ISession>* out) override;

private:
    static const char* getModuleId();
    static fingerprint_device_t* openHal();
    static void notify(const fingerprint_msg_t* msg);

    std::shared_ptr<Session> mSession;
    LockoutTracker mLockoutTracker;
    FingerprintSensorType mSensorType;
    int mMaxEnrollmentsPerUser;
    bool mSupportsGestures;

    fingerprint_device_t* mDevice;
    sp<IOneplusDisplay> mVendorDisplayService;
    sp<IVendorFingerprintExtensions> mVendorFpService;
};

} // namespace fingerprint
} // namespace biometrics
} // namespace hardware
} // namespace android
} // namespace aidl
