#include <Arduino.h>
#include "MotionDetect.h"

namespace MotionDetect {
    void setup() {
        pinMode(MOTION_DETECT_PIN, INPUT);
    }

    boolean current() {
        return digitalRead(MOTION_DETECT_PIN);
    }
}
