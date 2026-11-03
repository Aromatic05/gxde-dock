#include "util/servicerestarttracker.h"

#include <iostream>

namespace {

bool expect(bool actual, bool expected, const char *scenario)
{
    if (actual == expected) {
        return true;
    }

    std::cerr << scenario << ": expected " << expected
              << ", got " << actual << '\n';
    return false;
}

} // namespace

int main()
{
    bool passed = true;

    ServiceRestartTracker lateInitialOwner;
    passed &= expect(lateInitialOwner.ownerChanged(false, true), false,
                     "first registration after dock startup");
    passed &= expect(lateInitialOwner.ownerChanged(true, false), false,
                     "service disappearance");
    passed &= expect(lateInitialOwner.ownerChanged(false, true), true,
                     "registration after disappearance");

    ServiceRestartTracker ownerPresentAtStartup(true);
    passed &= expect(ownerPresentAtStartup.ownerChanged(true, false), false,
                     "existing service disappearance");
    passed &= expect(ownerPresentAtStartup.ownerChanged(false, true), true,
                     "existing service restart");

    ServiceRestartTracker directReplacement;
    passed &= expect(directReplacement.ownerChanged(true, true), true,
                     "direct owner replacement");

    ServiceRestartTracker noOwner;
    passed &= expect(noOwner.ownerChanged(false, false), false,
                     "no owner transition");

    return passed ? 0 : 1;
}
