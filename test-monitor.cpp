#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}

TEST(Monitor, TemperatureLow) {
    ASSERT_FALSE(vitalsOk(94.9, 80, 98));
}

TEST(Monitor, TemperatureHigh) {
    ASSERT_FALSE(vitalsOk(102.1, 80, 98));
}

TEST(Monitor, TemperatureEdge) {
    ASSERT_TRUE(vitalsOk(95.0, 80, 98));
    ASSERT_TRUE(vitalsOk(102.0, 80, 98));
}

TEST(Monitor, PulseRateLow) {
    ASSERT_FALSE(vitalsOk(98, 59.9, 98));
}

TEST(Monitor, PulseRateHigh) {
    ASSERT_FALSE(vitalsOk(98, 100.1, 98));
}

TEST(Monitor, PulseRateEdge) {
    ASSERT_TRUE(vitalsOk(98, 60.0, 98));
    ASSERT_TRUE(vitalsOk(98, 100.0, 98));
}

TEST(Monitor, SpO2Low) {
    ASSERT_FALSE(vitalsOk(98, 80, 89.9));
}

TEST(Monitor, SpO2Edge) {
    ASSERT_TRUE(vitalsOk(98, 80, 90.0));
    ASSERT_TRUE(vitalsOk(98, 80, 150.0));
}

TEST(Monitor, SpO2High) {
    ASSERT_FALSE(vitalsOk(98, 80, 151.0));
}

TEST(Monitor, AllVitalsNormal) {
    ASSERT_TRUE(vitalsOk(98.6, 72, 98));
}

TEST(Monitor, MultipleAbnormal) {
    ASSERT_FALSE(vitalsOk(94.0, 59.0, 80.0));
}
