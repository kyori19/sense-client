#include <Arduino.h>
#include "IDSwitch.h"

namespace IDSwitch {
    void setup() {
        pinMode(ID_SWITCH_HIGH_PIN, INPUT);
        pinMode(ID_SWITCH_LOW_PIN, INPUT);
    }

    int current() {
        return !digitalRead(ID_SWITCH_HIGH_PIN) << 1 | !digitalRead(ID_SWITCH_LOW_PIN);
    }
}
