#ifndef SENSE_CLIENT_SCREEN_H
#define SENSE_CLIENT_SCREEN_H

#include "Adafruit_SSD1306.h"

// The display has 21x8 chars to display
// [3]_____MM/dd_hh:mm O
// _____________________
// _____________________
// MD:<stat>____________
// _____________________
// _____________________
// O____________________
// O <-----SSID----->__.

#define POS_ID 0, 0
#define POS_CLOCK 8, 0
#define POS_MD 0, 3
#define POS_SERVER 0, 6
#define POS_WIFI 0, 7
#define POS_DOT 20, 7

namespace Screen {
    void setup();
    void loop();
}

#endif //SENSE_CLIENT_SCREEN_H
