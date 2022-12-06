#include <Arduino.h>
#include "BrightSense.h"

namespace BrightSense {
    int current() {
        return analogRead(BRIGHT_SENSE_PIN) * 3 * 1000 / 1024;
    }

    void setup() {
        pinMode(BRIGHT_SENSE_PIN, INPUT);
    }
}
