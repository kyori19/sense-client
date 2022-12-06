#include <Arduino.h>
#include "Beep.h"

namespace Beep {
    bool current = false;
    unsigned long until = 0;

    void offer(unsigned long length) {
        until = millis() + length;
        if (!current) {
            current = true;
            digitalWrite(BEEP_PIN, HIGH);
        }
    }

    void setup() {
        pinMode(BEEP_PIN, OUTPUT);
        digitalWrite(BEEP_PIN, LOW);
    }

    void loop() {
        if (current && until < millis()) {
            current = false;
            digitalWrite(BEEP_PIN, LOW);
        }
    }
}
