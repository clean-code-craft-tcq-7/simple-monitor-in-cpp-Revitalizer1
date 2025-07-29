#include "./monitor.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>
#include <string>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

enum class VitalStatus { OK, LOW, HIGH };

struct VitalRange {
    float low;
    float high;
    std::string name;
};

VitalStatus checkRange(float value, const VitalRange& range) {
    if (value < range.low) return VitalStatus::LOW;
    if (value > range.high) return VitalStatus::HIGH;
    return VitalStatus::OK;
}

// Separate functions for each vital check
VitalStatus checkTemperature(float temperature) {
    const VitalRange tempRange{95.0f, 102.0f, "Temperature"};
    return checkRange(temperature, tempRange);
}

VitalStatus checkPulseRate(float pulseRate) {
    const VitalRange pulseRange{60.0f, 100.0f, "Pulse Rate"};
    return checkRange(pulseRate, pulseRange);
}

VitalStatus checkSpO2(float spo2) {
    const VitalRange spo2Range{90.0f, 150.0f, "Oxygen Saturation"};
    return checkRange(spo2, spo2Range);
}

void blinkAlert(const std::string& message, int blinks = 6) {
    cout << message << "\n";
    for (int i = 0; i < blinks; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << "\n";
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalStatus tempStatus = checkTemperature(temperature);
    if (tempStatus == VitalStatus::LOW) {
        blinkAlert("Temperature is too low!");
        return 0;
    }
    if (tempStatus == VitalStatus::HIGH) {
        blinkAlert("Temperature is critical!");
        return 0;
    }

    VitalStatus pulseStatus = checkPulseRate(pulseRate);
    if (pulseStatus == VitalStatus::LOW) {
        blinkAlert("Pulse Rate is too low!");
        return 0;
    }
    if (pulseStatus == VitalStatus::HIGH) {
        blinkAlert("Pulse Rate is out of range!");
        return 0;
    }

    VitalStatus spo2Status = checkSpO2(spo2);
    if (spo2Status == VitalStatus::LOW) {
        blinkAlert("Oxygen Saturation out of range!");
        return 0;
    }

    return 1;
}
