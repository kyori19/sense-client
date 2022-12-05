#ifndef SENSE_CLIENT_SCREEN_H
#define SENSE_CLIENT_SCREEN_H

#include "Adafruit_SSD1306.h"

// The display has 21x8 chars to display
// __________MM/dd_hh:mm
// _____________________
// _____________________
// _____________________
// _____________________
// _____________________
// _____________________
// ____________________.

#define POS_CLOCK 10, 0
#define POS_DOT 20, 7

namespace Screen {
    void setup();
    void loop();
}

#endif //SENSE_CLIENT_SCREEN_H
