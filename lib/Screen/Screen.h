#ifndef SENSE_CLIENT_SCREEN_H
#define SENSE_CLIENT_SCREEN_H

#include "Adafruit_SSD1306.h"

// The display has 21x8 chars to display
// _____________________
// _____________________
// _____________________
// _____________________
// _____________________
// _____________________
// _____________________
// ____________________.

#define POS_GENERATE(x, y) y][x
#define POS_DOT POS_GENERATE(20, 7)

namespace Screen {
    void setup();
    void loop();
}

#endif //SENSE_CLIENT_SCREEN_H
