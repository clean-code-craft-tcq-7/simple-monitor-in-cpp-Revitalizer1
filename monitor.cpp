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

bool checkVitalAndAlert(VitalStatus status, const std::string& vitalName) {
    if (status == VitalStatus::LOW) {
        blinkAlert(vitalName + " is too low!");
        return false;
    }
    if (status == VitalStatus::HIGH) {
        blinkAlert(vitalName + " is out of range!");
        return false;
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    return checkVitalAndAlert(checkTemperature(temperature), "Temperature") &&
           checkVitalAndAlert(checkPulseRate(pulseRate), "Pulse Rate") &&
           checkVitalAndAlert(checkSpO2(spo2), "Oxygen Saturation");
}
